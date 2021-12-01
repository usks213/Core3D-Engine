/*****************************************************************//**
 * \file   D3D11_Buffer.h
 * \brief  DirectX11バッファー
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_Buffer_
#define _D3D11_Buffer_

#include <CoreRenderer/Core/Core_Buffer.h>
#include <CoreRenderer/D3D11/D3D11_Defines.h>

namespace d3d11
{
	/// @class D3D11Buffer
	/// @brief DirectX11バッファ-
	class D3D11Buffer final : public core::CoreBuffer
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
		explicit D3D11Buffer(ID3D11Device1* device, const core::BufferID& id, 
			const core::BufferDesc& desc, const core::BufferData* pData = nullptr);

		/// @brief デストラクタ
		~D3D11Buffer() noexcept = default;

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
