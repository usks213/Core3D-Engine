/*****************************************************************//**
 * \file   D3D12_DepthStencil.h
 * \brief  DirectX12デプスステンシル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/
#ifndef _D3D12_DEPTH_STENCIL_
#define _D3D12_DEPTH_STENCIL_

#include <CoreRenderer/Core/Core_DepthStencil.h>
#include "D3D12_Texture.h"

namespace d3d12
{
	/// @class D3D12DepthStencil
	/// @brief DreictX12深度ステンシル
	class D3D12DepthStencil final : public core::CoreDepthStencil
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id デプスステンシルID
		/// @param d3dTex d3d12テクスチャ
		explicit D3D12DepthStencil(ID3D12Device* device, const core::DepthStencilID& id, D3D12Texture& d3dTex);

		/// @brief デストラクタ
		~D3D12DepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief D3D12深度ステンシルヒープ
		ComPtr<ID3D12DescriptorHeap>		m_pHeapDSV;

	};
}

#endif // !_D3D12_DEPTH_STENCIL_
