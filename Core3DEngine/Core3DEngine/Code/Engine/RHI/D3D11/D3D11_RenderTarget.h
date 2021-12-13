/*****************************************************************//**
 * \file   D3D11_RenderTarget.h
 * \brief  DirectX11�����_�[�^�[�Q�b�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_RENDER_TARGET_
#define _D3D11_RENDER_TARGET_

#include <RHI/Core/RHI_RenderTarget.h>
#include "D3D11_Texture.h"


namespace Core::RHI::D3D11
{
	/// @class D3D11RenderTarget
	/// @brief DirectX11�����_�[�^�[�Q�b�g
	class D3D11RenderTarget final : public RenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param pDevice �f�o�C�X
		/// @param desc �e�N�X�`�����
		/// @param pData �������f�[�^
		explicit D3D11RenderTarget(ID3D11Device1* pDevice, TextureDesc& desc, const TextureData* pData = nullptr);

		/// @brief �f�X�g���N�^
		~D3D11RenderTarget() noexcept = default;

		/// @brief ���\�[�X�|�C���^�̎擾
		/// @return ���\�[�X�^
		void* GetResource() override { return m_tex.GetResource(); }

		/// @brief SRV�|�C���^�̎擾
		/// @return SRV�^
		void* GetSRV() override { return m_tex.GetSRV(); }

		/// @brief UAV�|�C���^�̎擾
		/// @return UAV�^
		void* GetUAV() override { return m_tex.GetUAV(); }

		/// @brief �����_�[�^�[�Q�b�g�r���[�̎擾
		/// @return �ėp�|�C���^
		void* GetRTV() override { return m_rtv.Get(); }

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief D3D11�e�N�X�`��
		D3D11Texture						m_tex;

		/// @brief D3D11�����_�[�^�[�Q�b�g�r���[
		ComPtr<ID3D11RenderTargetView>		m_rtv;
	};
}

#endif // !_D3D11_RENDER_TARGET_