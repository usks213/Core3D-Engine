/*****************************************************************//**
 * \file   RHI_Resource.h
 * \brief  リソース
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_RESOURCE_
#define _RHI_RESOURCE_

#include "RHI_CommonState.h"
#include <numeric>
#include <string>
#include <vector>


namespace Core::RHI
{
	/// @struct ResourceData
	/// @brief リソース初期化データ
	struct ResourceData
	{
		const void* pInitData = nullptr;
		std::size_t size = 0;
	};

	/// @brief UAVフラグ
	enum class UAVFlag : std::uint8_t
	{
		RAW,		///< バイトアドレス
		APPEND,		///< スタック操作
		COUNTER,	///< カウンター追加
	};

	/// @struct ResourceDesc
	/// @brief リソースDesc
	struct ResourceDesc
	{
		ResourceDesc() {}

		union 
		{
			struct Buffer
			{
				std::uint32_t		count = 0;
				std::uint32_t		size = 0;
			} buffer;
			struct Texture
			{
				std::uint32_t		width = 0;						///< 横幅(px)
				std::uint32_t		height = 0;						///< 縦幅(px)
				std::uint32_t		depth = 4;						///< フォーマットの数(RGBA:4)
				std::uint32_t		mipLevels = 1;						///< ミップマップレベル(0:自動生成)
				std::uint32_t		arraySize = 1;						///< 配列サイズ
				TextureFormat		format = TextureFormat::UNKNOWN;	///< フォーマット
				SampleDesc			sampleDesc = SampleDesc();				///< マルチサンプル指定
			} texture;
		};
		Usage				usage = Usage::DEFAULT;
		std::uint32_t		bindFlags = 0 | BindFlags::UNKNOWN;
		std::uint32_t		cpuAccessFlags = 0 | CPUAccessFlags::NONE;
		std::uint32_t		miscFlags = 0 | MiscFlags::UNKNONE;
		UAVFlag				uavFlag = UAVFlag::RAW;
	};

	/// @class Resource
	/// @brief リソース
	class Resource
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		Resource() :
			m_desc(), m_isDirty(false), m_aData()
		{
		}

		/// @brief コンストラクタ
		/// @param desc リソースDesc
		Resource(const ResourceDesc& desc) :
			m_desc(desc), m_isDirty(false), m_aData()
		{
		}

		/// @brief デストラクタ
		virtual ~Resource() noexcept = default;

		/// @brief リソース更新
		/// @param pData 更新データ
		/// @param size 更新サイズ
		void UpdateResource(void* pData, std::size_t size)
		{
			std::memcpy(m_aData.data(), pData, size);
			m_isDirty = true;
		}

		/// @brief リソース情報取得
		/// @return リソースDesc
		ResourceDesc GetDesc() { return m_desc; }

		/// @brief CPUデータの取得
		/// @return 汎用ポイント
		void* GetData() { return m_aData.data(); }

		/// @brief CPUデータサイズの取得
		/// @return データサイズ
		std::size_t GetDataSize() { return m_aData.size(); }

		/// @brief 更新フラグ取得
		/// @return TRUE 更新済み / FALSE 未更新
		bool GetDirty() { return m_isDirty; }

		/// @brief 更新フラグを元に戻す
		void ResetDirty() { m_isDirty = false; }

		/// @brief リソースポインタの取得
		/// @return リソース型
		virtual void* GetResource() = 0;

		/// @brief CBVポインタの取得
		/// @return CBV型
		virtual void* GetCBV() = 0;

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

		ResourceDesc				m_desc;		///< リソースDesc
		bool						m_isDirty;	///< リソース更新フラグ
		std::vector<std::byte>		m_aData;	///< CPU側のデータ

	};
}

#endif // !_RHI_RESOURCE_
