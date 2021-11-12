/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11�f�v�X�X�e���V��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_DEPTH_STENCIL_
#define _D3D11_DEPTH_STENCIL_

#include <CoreRenderer/Core/Core_DepthStencil.h>
#include "D3D11_Texture.h"

namespace d3d11
{
	/// @class D3D11DepthStencil
	/// @brief DreictX11�[�x�X�e���V��
	class D3D11DepthStencil final : public core::CoreDepthStencil
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param id �f�v�X�X�e���V��ID
		/// @param d3dTex d3d�e�N�X�`��
		explicit D3D11DepthStencil(ID3D11Device1* device, const core::DepthStencilID& id, D3D11Texture& d3dTex);

		/// @brief �f�X�g���N�^
		~D3D11DepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief D3D11�[�x�X�e���V���r���[
		ComPtr<ID3D11DepthStencilView>		m_dsv;
	};
}

#endif // !_D3D11_DEPTH_STENCIL_
