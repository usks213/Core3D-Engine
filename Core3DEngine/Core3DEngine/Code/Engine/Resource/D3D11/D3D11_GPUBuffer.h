/*****************************************************************//**
 * \file   D3D11_GPUBuffer.h
 * \brief  DirectX11バッファー
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_Buffer_
#define _D3D11_Buffer_

#include <Resource/Core/GPUBuffer.h>
#include <Renderer/D3D11/D3D11_Defines.h>

namespace Core::D3D11
{
	/// @class D3D11GPUBuffer
	/// @brief DirectX11バッファ-
	class D3D11GPUBuffer final : public GPUBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id バッファID
		/// @param desc バッファDesc
		/// @param data 初期化データ
		explicit D3D11GPUBuffer(ID3D11Device1* device, const Core::GPUBufferID& id, 
			const Core::GPUBufferDesc& desc, const Core::GPUBufferData* pData = nullptr);

		/// @brief デストラクタ
		~D3D11GPUBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief バッファ
		ComPtr<ID3D11Buffer>				m_pBuffer;

		/// @brief シェーダーリソースビュー
		ComPtr<ID3D11ShaderResourceView>	m_pSRV;

		/// @brief 順不同アクセスビュー
		ComPtr<ID3D11UnorderedAccessView>	m_pUAV;
	};
}

#endif // !_D3D11_Buffer_
