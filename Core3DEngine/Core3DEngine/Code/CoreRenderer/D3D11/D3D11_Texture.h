/*****************************************************************//**
 * \file   D3D11_Texture.h
 * \brief  DirectX11テクスチャ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_TEXTURE_
#define _D3D11_TEXTURE_

#include <CoreRenderer/Core/Core_Texture.h>
#include "D3D11_Defines.h"

namespace d3d11
{
	/// @class D3D11Texture
	/// @brief DirectX11テクスチャ
	class D3D11Texture final : public core::CoreTexture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ(ファイル読み込み)
		/// @param id テクスチャID
		/// @param filepath ファイルパス
		explicit D3D11Texture(ID3D11Device1* pDevice, const core::TextureID& id, const std::string& filepath);

		/// @brief コンストラクタ(Descから生成)
		/// @param id テクスチャID
		/// @param desc テクスチャDesc
		explicit D3D11Texture(ID3D11Device1* pDevice, const core::TextureID& id, core::TextureDesc& desc,
			const core::TextureData* pData = nullptr);

		/// @brief デストラクタ
		~D3D11Texture() noexcept = default;
		
	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		ComPtr<ID3D11Texture2D>			m_tex; ///< テクスチャ
		ComPtr<ID3D11ShaderResourceView>	m_srv; ///< シェーダリソースビュー
		ComPtr<ID3D11UnorderedAccessView>	m_uav; ///< 順不同アクセスビュー

	};
}

#endif // !_D3D11_TEXTURE_
