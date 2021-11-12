/*****************************************************************//**
 * \file   D3D11_RenderTarget.h
 * \brief  DirectX11�����_�[�^�[�Q�b�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_RENDER_TARGET_
#define _D3D11_RENDER_TARGET_

#include <CoreRenderer/Core/Core_RenderTarget.h>
#include "D3D11_Texture.h"


namespace d3d11
{
	/// @class D3D11RenderTarget
	/// @brief DirectX11�����_�[�^�[�Q�b�g
	class D3D11RenderTarget final : public core::CoreRenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param id �����_�[�^�[�Q�b�gID
		/// @param d3dTex d3d�e�N�X�`��
		explicit D3D11RenderTarget(ID3D11Device1* device, const core::RenderTargetID& id, D3D11Texture& d3dTex);

		/// @brief �f�X�g���N�^
		~D3D11RenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief D3D11�����_�[�^�[�Q�b�g�r���[
		ComPtr<ID3D11RenderTargetView>		m_rtv;
	};
}

#endif // !_D3D11_RENDER_TARGET_
