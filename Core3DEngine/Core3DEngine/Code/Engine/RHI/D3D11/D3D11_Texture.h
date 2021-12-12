/*****************************************************************//**
 * \file   D3D11_Texture.h
 * \brief  DirectX11�e�N�X�`��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_TEXTURE_
#define _D3D11_TEXTURE_

#include <RHI/Core/RHI_Texture.h>
#include "D3D11_Defines.h"

namespace Core::RHI::D3D11
{
	/// @class D3D11Texture
	/// @brief DirectX11�e�N�X�`��
	class D3D11Texture : public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------
		
		/// @brief �R���X�g���N�^
		D3D11Texture() :
			m_srv(nullptr), m_tex(nullptr), m_uav(nullptr)
		{}

		/// @brief �f�X�g���N�^
		~D3D11Texture() noexcept = default;

		/// @brief �t�@�C������e�N�X�`�����쐬
		/// @param filepath �t�@�C���p�X
		/// @return ���� TURE / ���s FALSE
		bool CreateFormFile(ID3D11Device1* pDevice, const std::string& filepath);

		/// @brief Desc����e�N�X�`�����쐬
		/// @param desc �e�N�X�`�����
		/// @param pData �������f�[�^
		/// @return ���� TURE / ���s FALSE
		bool CreateFromDesc(ID3D11Device1* pDevice, TextureDesc& desc, const TextureData* pData = nullptr);

		
		/// @brief ���\�[�X�|�C���^�̎擾
		/// @return ���\�[�X�^
		void* GetResource() override { return m_tex.Get(); }

		/// @brief SRV�|�C���^�̎擾
		/// @return SRV�^
		void* GetSRV() override { return m_srv.Get(); }

		/// @brief UAV�|�C���^�̎擾
		/// @return UAV�^
		void* GetUAV() override { return m_uav.Get(); }

	protected:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		ComPtr<ID3D11Texture2D>				m_tex; ///< �e�N�X�`��
		ComPtr<ID3D11ShaderResourceView>	m_srv; ///< �V�F�[�_���\�[�X�r���[
		ComPtr<ID3D11UnorderedAccessView>	m_uav; ///< ���s���A�N�Z�X�r���[

	};
}

#endif // !_D3D11_TEXTURE_
