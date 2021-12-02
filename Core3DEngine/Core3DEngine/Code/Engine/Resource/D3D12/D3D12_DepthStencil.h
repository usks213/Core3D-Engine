/*****************************************************************//**
 * \file   D3D12_DepthStencil.h
 * \brief  DirectX12�f�v�X�X�e���V��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/
#ifndef _D3D12_DEPTH_STENCIL_
#define _D3D12_DEPTH_STENCIL_

#include <Resource/Core/DepthStencil.h>
#include "D3D12_Texture.h"

namespace Core::D3D12
{
	/// @class D3D12DepthStencil
	/// @brief DreictX12�[�x�X�e���V��
	class D3D12DepthStencil final : public Core::CoreDepthStencil
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param device �f�o�C�X
		/// @param id �f�v�X�X�e���V��ID
		/// @param d3dTex Core::D3D12�e�N�X�`��
		explicit D3D12DepthStencil(ID3D12Device* device, const Core::DepthStencilID& id, D3D12Texture& d3dTex);

		/// @brief �f�X�g���N�^
		~D3D12DepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief D3D12�[�x�X�e���V���q�[�v
		ComPtr<ID3D12DescriptorHeap>		m_pHeapDSV;

	};
}

#endif // !_D3D12_DEPTH_STENCIL_
