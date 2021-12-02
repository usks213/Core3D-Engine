/*****************************************************************//**
 * \file   D3D12_Texture.h
 * \brief  DirectX12テクスチャ
 *
 * \author USAMI KOSHI
 * \date   2021/10/14
 *********************************************************************/

#include "D3D12_Texture.h"
#include <Renderer\D3D12\D3D12_CommonState.h>
using namespace Core::D3D12;


//------------------------------------------------------------------------------
// local methods
//------------------------------------------------------------------------------
namespace
{
    /// @brief ミップマップレベルを計算
    /// @return ミップマップレベル
    template<typename T> static constexpr T numMipmapLevels(T width, T height)
    {
        T levels = 1;
        while ((width | height) >> levels) {
            ++levels;
        }
        return levels;
    }
}

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief コンストラクタ(ファイル読み込み)
/// @param id テクスチャID
/// @param filepath ファイルパス
D3D12Texture::D3D12Texture(ID3D12Device* pDevice, D3D12DescriptorPool* pDescriptorPool,
    const Core::TextureID& id, const std::string& filepath) :
	Core::CoreTexture(id, filepath),
    //m_pTexHeap(nullptr),
    m_pTex(nullptr)
{

}

/// @brief コンストラクタ(Descから生成)
/// @param id テクスチャID
/// @param desc テクスチャDesc
D3D12Texture::D3D12Texture(ID3D12Device* pDevice, D3D12DescriptorPool* pDescriptorPool,
    const Core::TextureID& id, Core::TextureDesc& desc, 
    const Core::TextureData* pData, const D3D12_CLEAR_VALUE* pClear) :
	Core::CoreTexture(id, desc),
	//m_pTexHeap(nullptr),
	m_pTex(nullptr),
    m_eState(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
{
    DXGI_SAMPLE_DESC d3dSampleDesc = { desc.sampleDesc.count, desc.sampleDesc.quality };

    // リソース
    D3D12_RESOURCE_DESC resDesc = {};
    resDesc.Format = Core::D3D12::getDXGIFormat(desc.format);
    resDesc.Width = desc.width;
    resDesc.Height = desc.height;
    resDesc.DepthOrArraySize = desc.arraySize;
    resDesc.SampleDesc = d3dSampleDesc;
    resDesc.MipLevels = 1;//desc.mipLevels;
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resDesc.Flags = Core::D3D12::getD3D12ResourceFlags(desc.bindFlags);

    // リソースステート
    if (resDesc.Flags == D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
    {
        m_eState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    }
    else if (resDesc.Flags == D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
    {
        m_eState = D3D12_RESOURCE_STATE_RENDER_TARGET;
    }
    else if (resDesc.Flags == D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS)
    {
        m_eState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    }

    // 初期値なし
    if (pData == nullptr) 
    {
        if (desc.width <= 0 && desc.height <= 0) {
            // 生成不可
            return;
        }
        //if (desc.usage == Core::Usage::STATIC) {
        //    // エラー 初期値なし、書き換え不可
        //    return;
        //}

        // ヒープ設定
        D3D12_HEAP_PROPERTIES texHeapProp = {};
        texHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
        texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        texHeapProp.CreationNodeMask = 0;
        texHeapProp.VisibleNodeMask = 0;

        // リソース生成
        CHECK_FAILED(pDevice->CreateCommittedResource(
            &texHeapProp,
            D3D12_HEAP_FLAG_NONE,//特に指定なし
            &resDesc,
            m_eState,   // 初期のリソース状態
            pClear,
            IID_PPV_ARGS(m_pTex.ReleaseAndGetAddressOf())
        ));
    }
    else 
    {
        // ヒープ設定
        D3D12_HEAP_PROPERTIES texHeapProp = {};
        texHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;  // 特別
        texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
        texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;    // CPUから
        texHeapProp.CreationNodeMask = 0;
        texHeapProp.VisibleNodeMask = 0;

        // リソース生成
        CHECK_FAILED(pDevice->CreateCommittedResource(
            &texHeapProp,
            D3D12_HEAP_FLAG_NONE,//特に指定なし
            &resDesc,
            m_eState,   // 初期のリソース状態
            pClear,
            IID_PPV_ARGS(m_pTex.ReleaseAndGetAddressOf())
        ));
        // データ格納
        CHECK_FAILED(m_pTex->WriteToSubresource(0,
            nullptr,//全領域へコピー
            pData->pInitData,//元データアドレス
            static_cast<UINT>(desc.width * desc.depth),//1ラインサイズ
            static_cast<UINT>(desc.width * desc.height * desc.depth)//全サイズ
        ));
    }

    //// ヒープ生成
    //D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    //descHeapDesc.Flags = Core::D3D12::getD3D12HeapFlags(desc.bindFlags);//シェーダから見えるように
    //descHeapDesc.NodeMask = 0;//マスクは0
    //descHeapDesc.NumDescriptors = 1;//ビューは今のところ１つだけ
    //descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//シェーダリソースビュー(および定数、UAVも)

    //CHECK_FAILED(pDevice->CreateDescriptorHeap(&descHeapDesc,
    //    IID_PPV_ARGS(m_pTexHeap.ReleaseAndGetAddressOf())));//生成
    m_handle = pDescriptorPool->Allocate();


    // シェーダーリソース
    if (desc.bindFlags & Core::BindFlags::SHADER_RESOURCE)
    {
        //通常テクスチャビュー作成
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = getTypeLessToSRVFormat(desc.format);//DXGI_FORMAT_R8G8B8A8_UNORM;//RGBA(0.0f～1.0fに正規化)
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//後述
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
        srvDesc.Texture2D.MipLevels = 1;//ミップマップは使用しないので1

        // MSAA 
        if (desc.sampleDesc.isUse) srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;

        pDevice->CreateShaderResourceView(m_pTex.Get(), //ビューと関連付けるバッファ
            &srvDesc, //先ほど設定したテクスチャ設定情報
            m_handle.CPUHandle//ヒープのどこに割り当てるか
        );
    }

    // 順不同アクセスビュー
    if (desc.bindFlags & Core::BindFlags::UNORDERED_ACCESS)
    {
        // 順不同アクセスビューの作成
        D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = getTypeLessToSRVFormat(desc.format);
        uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
        uavDesc.Texture2D.MipSlice = 0;     // ??
        uavDesc.Texture2D.PlaneSlice = 0;   // ??

        // カウンター？？？
        if (true)
        {
            pDevice->CreateUnorderedAccessView(m_pTex.Get(), nullptr, &uavDesc,
                m_handle.CPUHandle);
        }
        else
        {
            pDevice->CreateUnorderedAccessView(m_pTex.Get(), nullptr, &uavDesc,
                m_handle.CPUHandle);
        }
    }
}

