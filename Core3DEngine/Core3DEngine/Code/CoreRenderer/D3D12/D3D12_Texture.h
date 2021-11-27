/*****************************************************************//**
 * \file   D3D12_Texture.h
 * \brief  DirectX12�e�N�X�`��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/14
 *********************************************************************/
#ifndef _D3D12_TEXTURE_
#define _D3D12_TEXTURE_

#include <CoreRenderer/Core/Core_Texture.h>
#include "D3D12_Defines.h"

namespace d3d12
{
	/// @class D3D12Texture
	/// @brief DirectX12�e�N�X�`��
	class D3D12Texture final : public core::CoreTexture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^(�t�@�C���ǂݍ���)
		/// @param id �e�N�X�`��ID
		/// @param filepath �t�@�C���p�X
		explicit D3D12Texture(ID3D12Device* pDevice, const core::TextureID& id, const std::string& filepath);

		/// @brief �R���X�g���N�^(Desc���琶��)
		/// @param id �e�N�X�`��ID
		/// @param desc �e�N�X�`��Desc
		explicit D3D12Texture(ID3D12Device* pDevice, const core::TextureID& id, core::TextureDesc& desc,
			const core::TextureData* pData = nullptr, const D3D12_CLEAR_VALUE* pClear = nullptr);

		/// @brief �f�X�g���N�^
		~D3D12Texture() noexcept = default;
		
		/// @brief ���\�[�X�|�C���^�̎擾
		/// @return ���\�[�X�^
		void* GetResource() override { return m_pTex.Get(); }

		/// @brief SRV�|�C���^�̎擾
		/// @return SRV�^
		void* GetSRV() override { return (void*)m_GPUHandle.ptr; }

		/// @brief UAV�|�C���^�̎擾
		/// @return UAV�^
		void* GetUAV() override { return (void*)m_GPUHandle.ptr; }

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		ComPtr<ID3D12DescriptorHeap>		m_pTexHeap;	///< �q�[�v
		ComPtr<ID3D12Resource>				m_pTex;		///< �e�N�X�`��
		D3D12_RESOURCE_STATES				m_eState;	///< ���\�[�X�̏��
		D3D12_CPU_DESCRIPTOR_HANDLE			m_CPUHandle;	///< CPU�n���h��
		D3D12_GPU_DESCRIPTOR_HANDLE			m_GPUHandle;	///< GPU�n���h��
	};
}

#endif // !_D3D12_TEXTURE_
