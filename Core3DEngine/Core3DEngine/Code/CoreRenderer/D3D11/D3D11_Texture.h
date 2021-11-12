/*****************************************************************//**
 * \file   D3D11_Texture.h
 * \brief  DirectX11�e�N�X�`��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_TEXTURE_
#define _D3D11_TEXTURE_

#include <CoreRenderer/Core/Core_Texture.h>
#include "D3D11_Defines.h"

namespace d3d11
{
	/// @class D3D11Texture
	/// @brief DirectX11�e�N�X�`��
	class D3D11Texture final : public core::CoreTexture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^(�t�@�C���ǂݍ���)
		/// @param id �e�N�X�`��ID
		/// @param filepath �t�@�C���p�X
		explicit D3D11Texture(ID3D11Device1* pDevice, const core::TextureID& id, const std::string& filepath);

		/// @brief �R���X�g���N�^(Desc���琶��)
		/// @param id �e�N�X�`��ID
		/// @param desc �e�N�X�`��Desc
		explicit D3D11Texture(ID3D11Device1* pDevice, const core::TextureID& id, core::TextureDesc& desc,
			const core::TextureData* pData = nullptr);

		/// @brief �f�X�g���N�^
		~D3D11Texture() noexcept = default;
		
	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		ComPtr<ID3D11Texture2D>			m_tex; ///< �e�N�X�`��
		ComPtr<ID3D11ShaderResourceView>	m_srv; ///< �V�F�[�_���\�[�X�r���[
		ComPtr<ID3D11UnorderedAccessView>	m_uav; ///< ���s���A�N�Z�X�r���[

	};
}

#endif // !_D3D11_TEXTURE_
