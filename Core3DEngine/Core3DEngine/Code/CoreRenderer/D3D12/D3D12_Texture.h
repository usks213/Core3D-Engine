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
		
	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		ComPtr<ID3D12DescriptorHeap>		m_pTexHeap;	///< �q�[�v
		ComPtr<ID3D12Resource>			m_pTex;		///< �e�N�X�`��
		D3D12_RESOURCE_STATES				m_eState;	///< ���\�[�X�̏��
	};
}

#endif // !_D3D12_TEXTURE_
