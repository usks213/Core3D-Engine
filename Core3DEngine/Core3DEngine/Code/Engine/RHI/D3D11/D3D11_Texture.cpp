/*****************************************************************//**
 * \file   D3D11_Texture.h
 * \brief  DirectX11テクスチャ
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_Texture.h"
#include "D3D11_CommonState.h"

using namespace Core::RHI::D3D11;


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

/// @brief ファイルからテクスチャを作成
/// @param filepath ファイルパス
/// @return 成功 TURE / 失敗 FALSE
bool D3D11Texture::CreateFormFile(ID3D11Device1* pDevice, const std::string& filepath)
{

}

/// @brief Descからテクスチャを作成
/// @param desc テクスチャ情報
/// @param pData 初期化データ
/// @return 成功 TURE / 失敗 FALSE
bool D3D11Texture::CreateFromDesc(ID3D11Device1* pDevice, ResourceDesc& desc, const ResourceData* pData = nullptr)
{
    // Descコピー
    m_desc = desc;

    // テクスチャ
    DXGI_SAMPLE_DESC d3d11SampleDesc = { desc.texture.sampleDesc.count, desc.texture.sampleDesc.quality };
    D3D11_TEXTURE2D_DESC d3d11Desc = {
        desc.texture.width,
        desc.texture.height,
        desc.texture.mipLevels,
        desc.texture.arraySize,
        GetDXGIFormat(desc.texture.format),
        d3d11SampleDesc,
        GetD3D11Usage(desc.usage),
        desc.bindFlags,
        desc.cpuAccessFlags,
        desc.miscFlags,
    };

    // ミップマップ自動生成指定
    if (desc.texture.mipLevels == 0 &&
        desc.bindFlags & BindFlags::RENDER_TARGET &&
        desc.bindFlags & BindFlags::SHADER_RESOURCE &&
        desc.miscFlags & MiscFlags::GENERATE_MIPS
        )
    {
        d3d11Desc.MipLevels = desc.texture.mipLevels = numMipmapLevels(desc.texture.width, desc.texture.height);
    }

    // 初期値なし
    if (pData == nullptr) {
        if (desc.texture.width <= 0 && desc.texture.height <= 0) {
            // 生成不可
            return;
        }
        if (desc.usage == Usage::STATIC) {
            // エラー 初期値なし、書き換え不可
            return;
        }

        CHECK_FAILED(pDevice->CreateTexture2D(&d3d11Desc, nullptr, m_tex.GetAddressOf()));
    }
    else {
        D3D11_SUBRESOURCE_DATA d3d11SubresourceData = {};
        d3d11SubresourceData.pSysMem = pData->pInitData;
        d3d11SubresourceData.SysMemPitch = desc.texture.width * desc.texture.depth;
        d3d11SubresourceData.SysMemSlicePitch = desc.texture.width * desc.texture.height * desc.texture.depth;

        CHECK_FAILED(pDevice->CreateTexture2D(&d3d11Desc, &d3d11SubresourceData, m_tex.GetAddressOf()));
    }

    // ビューの作成
    if (desc.bindFlags & BindFlags::SHADER_RESOURCE)
    {
        // シェーダーリソースビュー
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = D3D11::getTypeLessToSRVFormat(desc.texture.format);
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = d3d11Desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        // MSAA
        if (desc.texture.sampleDesc.isUse) srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;

        CHECK_FAILED(pDevice->CreateShaderResourceView(m_tex.Get(), &srvDesc, m_srv.GetAddressOf()));
    }
    if (desc.bindFlags & BindFlags::UNORDERED_ACCESS)
    {
        // 順不同アクセスビュー
        D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = d3d11Desc.Format;
        uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
        uavDesc.Texture2D.MipSlice = 0;

        CHECK_FAILED(pDevice->CreateUnorderedAccessView(m_tex.Get(), &uavDesc, m_uav.GetAddressOf()));
    }
}
