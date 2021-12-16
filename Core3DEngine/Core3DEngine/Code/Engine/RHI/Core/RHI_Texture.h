/*****************************************************************//**
 * \file   RHI_Texture.h
 * \brief  テクスチャ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_TEXTURE_
#define _RHI_TEXTURE_

#include <cstdint>
#include <string>
#include <RHI\Core\RHI_CommonState.h>

namespace Core::RHI
{
	/// @struct TextureData
	/// @brief テクスチャ初期化データ
	struct TextureData
	{
		const void* pInitData = nullptr;
		std::size_t size = 0;
	};

	/// @struct TextureDesc
	/// @brief テクスチャDesc
	struct TextureDesc
	{
		std::string			name;										///< テクスチャ名orファイルパス
		std::uint32_t		width = 0;						///< 横幅(px)
		std::uint32_t		height = 0;						///< 縦幅(px)
		std::uint32_t		depth = 4;						///< フォーマットの数(RGBA:4)
		std::uint32_t		mipLevels = 1;						///< ミップマップレベル(0:自動生成)
		std::uint32_t		arraySize = 1;						///< 配列サイズ
		TextureFormat		format = TextureFormat::UNKNOWN;	///< フォーマット
		SampleDesc			sampleDesc = SampleDesc();				///< マルチサンプル指定
		Usage				usage = Usage::DEFAULT;			///< リソース使用識別
		std::uint32_t		bindFlags = 0 | BindFlags::UNKNOWN;	///< バインドフラグ
		std::uint32_t		cpuAccessFlags = 0 | CPUAccessFlags::NONE;	///< CPUアクセスフラグ
		std::uint32_t		miscFlags = 0 | MiscFlags::UNKNONE;	///< バッファ指定フラグ
	};

	/// @class Texture
	/// @brief テクスチャ
	class Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		Texture() : m_desc() {}

		/// @brief デストラクタ
		virtual ~Texture() noexcept = default;

		/// @brief テクスチャ情報取得
		/// @return テクスチャDesc
		TextureDesc GetDesc() { return m_desc; }

		/// @brief リソースポインタの取得
		/// @return リソース型
		virtual void* GetResource() = 0;

		/// @brief SRVポインタの取得
		/// @return SRV型
		virtual void* GetSRV() = 0;

		/// @brief UAVポインタの取得
		/// @return UAV型
		virtual void* GetUAV() = 0;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		TextureDesc		m_desc;		///< テクスチャDesc
	};
}

#endif // !_RHI_TEXTURE_
