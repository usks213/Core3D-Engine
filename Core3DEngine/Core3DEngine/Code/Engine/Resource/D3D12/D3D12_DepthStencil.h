/*****************************************************************//**
 * \file   D3D12_DepthStencil.h
 * \brief  DirectX12デプスステンシル
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
	/// @brief DreictX12深度ステンシル
	class D3D12DepthStencil final : public Core::CoreDepthStencil
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id デプスステンシルID
		/// @param d3dTex Core::D3D12テクスチャ
		explicit D3D12DepthStencil(ID3D12Device* device, const Core::DepthStencilID& id, D3D12Texture& d3dTex);

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
