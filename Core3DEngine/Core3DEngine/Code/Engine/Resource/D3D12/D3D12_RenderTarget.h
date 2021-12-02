/*****************************************************************//**
 * \file   D3D12_RenderTarget.h
 * \brief  DierectX12�����_�[�^�[�Q�b�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/
#ifndef _D3D12_RENDER_TARGET_
#define _D3D12_RENDER_TARGET_

#include <Resource/Core/RenderTarget.h>
#include "D3D12_Texture.h"


namespace Core::D3D12
{
	/// @class D3D12RenderTarget
	/// @brief DirectX12�����_�[�^�[�Q�b�g
	class D3D12RenderTarget final : public Core::CoreRenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param id �����_�[�^�[�Q�b�gID
		/// @param d3dTex d3d�e�N�X�`��
		explicit D3D12RenderTarget(ID3D12Device* device, const Core::RenderTargetID& id, D3D12Texture& d3dTex);

		/// @brief �f�X�g���N�^
		~D3D12RenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief D3D12�����_�[�^�[�Q�b�g�q�[�v
		ComPtr<ID3D12DescriptorHeap>		m_pHeapRTV;
	};
}

#endif // !_D3D12_RENDER_TARGET_
