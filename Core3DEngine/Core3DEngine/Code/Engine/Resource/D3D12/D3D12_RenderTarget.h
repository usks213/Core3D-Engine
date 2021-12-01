/*****************************************************************//**
 * \file   D3D12_RenderTarget.h
 * \brief  DierectX12レンダーターゲット
 * 
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/
#ifndef _D3D12_RENDER_TARGET_
#define _D3D12_RENDER_TARGET_

#include <CoreRenderer/Core/Core_RenderTarget.h>
#include "D3D12_Texture.h"


namespace d3d12
{
	/// @class D3D12RenderTarget
	/// @brief DirectX12レンダーターゲット
	class D3D12RenderTarget final : public core::CoreRenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id レンダーターゲットID
		/// @param d3dTex d3dテクスチャ
		explicit D3D12RenderTarget(ID3D12Device* device, const core::RenderTargetID& id, D3D12Texture& d3dTex);

		/// @brief デストラクタ
		~D3D12RenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief D3D12レンダーターゲットヒープ
		ComPtr<ID3D12DescriptorHeap>		m_pHeapRTV;
	};
}

#endif // !_D3D12_RENDER_TARGET_
