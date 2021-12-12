/*****************************************************************//**
 * \file   D3D11_Texture.h
 * \brief  DirectX11テクスチャ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_TEXTURE_
#define _D3D11_TEXTURE_

#include <RHI/Core/RHI_Texture.h>
#include "D3D11_Defines.h"

namespace Core::RHI::D3D11
{
	/// @class D3D11Texture
	/// @brief DirectX11テクスチャ
	class D3D11Texture : public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------
		
		/// @brief コンストラクタ
		D3D11Texture() :
			m_srv(nullptr), m_tex(nullptr), m_uav(nullptr)
		{}

		/// @brief デストラクタ
		~D3D11Texture() noexcept = default;

		/// @brief ファイルからテクスチャを作成
		/// @param filepath ファイルパス
		/// @return 成功 TURE / 失敗 FALSE
		bool CreateFormFile(ID3D11Device1* pDevice, const std::string& filepath);

		/// @brief Descからテクスチャを作成
		/// @param desc テクスチャ情報
		/// @param pData 初期化データ
		/// @return 成功 TURE / 失敗 FALSE
		bool CreateFromDesc(ID3D11Device1* pDevice, TextureDesc& desc, const TextureData* pData = nullptr);

		
		/// @brief リソースポインタの取得
		/// @return リソース型
		void* GetResource() override { return m_tex.Get(); }

		/// @brief SRVポインタの取得
		/// @return SRV型
		void* GetSRV() override { return m_srv.Get(); }

		/// @brief UAVポインタの取得
		/// @return UAV型
		void* GetUAV() override { return m_uav.Get(); }

	protected:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		ComPtr<ID3D11Texture2D>				m_tex; ///< テクスチャ
		ComPtr<ID3D11ShaderResourceView>	m_srv; ///< シェーダリソースビュー
		ComPtr<ID3D11UnorderedAccessView>	m_uav; ///< 順不同アクセスビュー

	};
}

#endif // !_D3D11_TEXTURE_
