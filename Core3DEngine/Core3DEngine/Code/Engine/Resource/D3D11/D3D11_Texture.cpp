/*****************************************************************//**
 * \file   D3D11_Texture.h
 * \brief  DirectX11�e�N�X�`��
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_Texture.h"
#include "D3D11_CommonState.h"
using namespace d3d11;


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
D3D11Texture::D3D11Texture(ID3D11Device1* pDevice, const core::TextureID& id, const std::string& filepath) :
	core::CoreTexture(id, filepath),
	m_tex(nullptr),
	m_srv(nullptr),
    m_uav(nullptr)
{

}

/// @brief �R���X�g���N�^(Desc���琶��)
/// @param id �e�N�X�`��ID
/// @param desc �e�N�X�`��Desc
D3D11Texture::D3D11Texture(ID3D11Device1* pDevice, const core::TextureID& id, 
    core::TextureDesc& desc, const core::TextureData* pData) :
	core::CoreTexture(id, desc),
	m_tex(nullptr),
	m_srv(nullptr),
    m_uav(nullptr)
{
    // �e�N�X�`��
    DXGI_SAMPLE_DESC d3d11SampleDesc = { desc.sampleDesc.count, desc.sampleDesc.quality };
    D3D11_TEXTURE2D_DESC d3d11Desc = {
        desc.width,
        desc.height,
        desc.mipLevels,
        desc.arraySize,
        getDXGIFormat(desc.format),
        d3d11SampleDesc,
        getD3D11Usage(desc.usage),
        desc.bindFlags,
        desc.cpuAccessFlags,
        desc.miscFlags,
    };

    // �~�b�v�}�b�v���������w��
    if (desc.mipLevels == 0 && 
        desc.bindFlags & core::BindFlags::RENDER_TARGET && 
        desc.bindFlags & core::BindFlags::SHADER_RESOURCE && 
        desc.miscFlags & core::MiscFlags::GENERATE_MIPS 
        )
    {
        d3d11Desc.MipLevels = desc.mipLevels = numMipmapLevels(desc.width, desc.height);
    }

    // �����l�Ȃ�
    if (pData == nullptr) {
        if (desc.width <= 0 && desc.height <= 0) {
            // �����s��
            return;
        }
        if (desc.usage == core::Usage::STATIC) {
            // �G���[ �����l�Ȃ��A���������s��
            return;
        }

        CHECK_FAILED(pDevice->CreateTexture2D(&d3d11Desc, nullptr, m_tex.GetAddressOf()));
    }
    else {
        D3D11_SUBRESOURCE_DATA d3d11SubresourceData = {};
        d3d11SubresourceData.pSysMem = pData->pInitData;
        d3d11SubresourceData.SysMemPitch = desc.width * desc.depth;
        d3d11SubresourceData.SysMemSlicePitch = desc.width * desc.height * desc.depth;

        CHECK_FAILED(pDevice->CreateTexture2D(&d3d11Desc, &d3d11SubresourceData, m_tex.GetAddressOf()));
    }

    // �r���[�̍쐬
    if (desc.bindFlags & core::BindFlags::SHADER_RESOURCE)
    {
        // �V�F�[�_�[���\�[�X�r���[
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = d3d11::getTypeLessToSRVFormat(desc.format);
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = d3d11Desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        // MSAA
        if (desc.sampleDesc.isUse) srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;

        CHECK_FAILED(pDevice->CreateShaderResourceView(m_tex.Get(), &srvDesc, m_srv.GetAddressOf()));
    }
    if (desc.bindFlags & core::BindFlags::UNORDERED_ACCESS)
    {
        // ���s���A�N�Z�X�r���[
        D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
        uavDesc.Format = d3d11Desc.Format;
        uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
        uavDesc.Texture2D.MipSlice = 0;
      
        CHECK_FAILED(pDevice->CreateUnorderedAccessView(m_tex.Get(), &uavDesc, m_uav.GetAddressOf()));
    }
}

