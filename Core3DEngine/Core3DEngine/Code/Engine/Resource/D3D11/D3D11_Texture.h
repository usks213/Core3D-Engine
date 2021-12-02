/*****************************************************************//**
 * \file   D3D11_Texture.h
 * \brief  DirectX11�e�N�X�`��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_TEXTURE_
#define _D3D11_TEXTURE_

#include <Resource/Core/Texture.h>
#include <Renderer\D3D11\D3D11_Defines.h>

namespace Core::D3D11
{
	/// @class D3D11Texture
	/// @brief DirectX11�e�N�X�`��
	class D3D11Texture final : public Core::CoreTexture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^(�t�@�C���ǂݍ���)
		/// @param id �e�N�X�`��ID
		/// @param filepath �t�@�C���p�X
		explicit D3D11Texture(ID3D11Device1* pDevice, const Core::TextureID& id, const std::string& filepath);

		/// @brief �R���X�g���N�^(Desc���琶��)
		/// @param id �e�N�X�`��ID
		/// @param desc �e�N�X�`��Desc
		explicit D3D11Texture(ID3D11Device1* pDevice, const Core::TextureID& id, Core::TextureDesc& desc,
			const Core::TextureData* pData = nullptr);

		/// @brief �f�X�g���N�^
		~D3D11Texture() noexcept = default;
		
		/// @brief ���\�[�X�|�C���^�̎擾
		/// @return ���\�[�X�^
		void* GetResource() override { return m_tex.Get(); }

		/// @brief SRV�|�C���^�̎擾
		/// @return SRV�^
		void* GetSRV() override { return m_srv.Get(); }

		/// @brief UAV�|�C���^�̎擾
		/// @return UAV�^
		void* GetUAV() override { return m_uav.Get(); }

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
