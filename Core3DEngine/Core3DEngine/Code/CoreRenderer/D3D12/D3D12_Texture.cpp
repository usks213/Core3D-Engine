/*****************************************************************//**
 * \file   D3D12_Texture.h
 * \brief  DirectX12�e�N�X�`��
 *
 * \author USAMI KOSHI
 * \date   2021/10/14
 *********************************************************************/

#include "D3D12_Texture.h"
#include "D3D12_CommonState.h"
using namespace d3d12;


//------------------------------------------------------------------------------
// local methods
//------------------------------------------------------------------------------
namespace
{
    /// @brief �~�b�v�}�b�v���x�����v�Z
    /// @return �~�b�v�}�b�v���x��
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

/// @brief �R���X�g���N�^(�t�@�C���ǂݍ���)
/// @param id �e�N�X�`��ID
/// @param filepath �t�@�C���p�X
D3D12Texture::D3D12Texture(ID3D12Device* pDevice, const core::TextureID& id, const std::string& filepath) :
	core::CoreTexture(id, filepath),
    m_pTexHeap(nullptr),
    m_pTex(nullptr)
{

}

/// @brief �R���X�g���N�^(Desc���琶��)
/// @param id �e�N�X�`��ID
/// @param desc �e�N�X�`��Desc
D3D12Texture::D3D12Texture(ID3D12Device* pDevice, const core::TextureID& id, 
    core::TextureDesc& desc, const core::TextureData* pData, const D3D12_CLEAR_VALUE* pClear) :
	core::CoreTexture(id, desc),
	m_pTexHeap(nullptr),
	m_pTex(nullptr),
    m_eState(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
{
    DXGI_SAMPLE_DESC d3dSampleDesc = { desc.sampleDesc.count, desc.sampleDesc.quality };

    // ���\�[�X
    D3D12_RESOURCE_DESC resDesc = {};
    resDesc.Format = d3d12::getDXGIFormat(desc.format);
    resDesc.Width = desc.width;
    resDesc.Height = desc.height;
    resDesc.DepthOrArraySize = desc.arraySize;
    resDesc.SampleDesc = d3dSampleDesc;
    resDesc.MipLevels = 1;//desc.mipLevels;
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resDesc.Flags = d3d12::getD3D12ResourceFlags(desc.bindFlags);

    // ���\�[�X�X�e�[�g
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

    // �����l�Ȃ�
    if (pData == nullptr) 
    {
        if (desc.width <= 0 && desc.height <= 0) {
            // �����s��
            return;
        }
        //if (desc.usage == core::Usage::STATIC) {
        //    // �G���[ �����l�Ȃ��A���������s��
        //    return;
        //}

        // �q�[�v�ݒ�
        D3D12_HEAP_PROPERTIES texHeapProp = {};
        texHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
        texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        texHeapProp.CreationNodeMask = 0;
        texHeapProp.VisibleNodeMask = 0;

        // ���\�[�X����
        CHECK_FAILED(pDevice->CreateCommittedResource(
            &texHeapProp,
            D3D12_HEAP_FLAG_NONE,//���Ɏw��Ȃ�
            &resDesc,
            m_eState,   // �����̃��\�[�X���
            pClear,
            IID_PPV_ARGS(m_pTex.ReleaseAndGetAddressOf())
        ));
    }
    else 
    {
        // �q�[�v�ݒ�
        D3D12_HEAP_PROPERTIES texHeapProp = {};
        texHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;  // ����
        texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
        texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;    // CPU����
        texHeapProp.CreationNodeMask = 0;
        texHeapProp.VisibleNodeMask = 0;

        // ���\�[�X����
        CHECK_FAILED(pDevice->CreateCommittedResource(
            &texHeapProp,
            D3D12_HEAP_FLAG_NONE,//���Ɏw��Ȃ�
            &resDesc,
            m_eState,   // �����̃��\�[�X���
            pClear,
            IID_PPV_ARGS(m_pTex.ReleaseAndGetAddressOf())
        ));
        // �f�[�^�i�[
        CHECK_FAILED(m_pTex->WriteToSubresource(0,
            nullptr,//�S�̈�փR�s�[
            pData->pInitData,//���f�[�^�A�h���X
            static_cast<UINT>(desc.width * desc.depth),//1���C���T�C�Y
            static_cast<UINT>(desc.width * desc.height * desc.depth)//�S�T�C�Y
        ));
    }

    // �q�[�v����
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    descHeapDesc.Flags = d3d12::getD3D12HeapFlags(desc.bindFlags);//�V�F�[�_���猩����悤��
    descHeapDesc.NodeMask = 0;//�}�X�N��0
    descHeapDesc.NumDescriptors = 1;//�r���[�͍��̂Ƃ���P����
    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;//�V�F�[�_���\�[�X�r���[(����ђ萔�AUAV��)

    CHECK_FAILED(pDevice->CreateDescriptorHeap(&descHeapDesc,
        IID_PPV_ARGS(m_pTexHeap.ReleaseAndGetAddressOf())));//����

    // �V�F�[�_�[���\�[�X
    if (desc.bindFlags & core::BindFlags::SHADER_RESOURCE)
    {
        //�ʏ�e�N�X�`���r���[�쐬
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = getTypeLessToSRVFormat(desc.format);//DXGI_FORMAT_R8G8B8A8_UNORM;//RGBA(0.0f�`1.0f�ɐ��K��)
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;//��q
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
        srvDesc.Texture2D.MipLevels = 1;//�~�b�v�}�b�v�͎g�p���Ȃ��̂�1

        // MSAA 
        if (desc.sampleDesc.isUse) srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;

        pDevice->CreateShaderResourceView(m_pTex.Get(), //�r���[�Ɗ֘A�t����o�b�t�@
            &srvDesc, //��قǐݒ肵���e�N�X�`���ݒ���
            m_pTexHeap->GetCPUDescriptorHandleForHeapStart()//�q�[�v�̂ǂ��Ɋ��蓖�Ă邩
        );
    }

    // ���s���A�N�Z�X�r���[
    if (desc.bindFlags & core::BindFlags::UNORDERED_ACCESS)
    {
        // ���s���A�N�Z�X�r���[�̍쐬
        D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = getTypeLessToSRVFormat(desc.format);
        uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
        uavDesc.Texture2D.MipSlice = 0;     // ??
        uavDesc.Texture2D.PlaneSlice = 0;   // ??

        // �J�E���^�[�H�H�H
        if (true)
        {
            pDevice->CreateUnorderedAccessView(m_pTex.Get(), nullptr, &uavDesc,
                m_pTexHeap->GetCPUDescriptorHandleForHeapStart());
        }
        else
        {
            pDevice->CreateUnorderedAccessView(m_pTex.Get(), nullptr, &uavDesc,
                m_pTexHeap->GetCPUDescriptorHandleForHeapStart());
        }
    }
}

