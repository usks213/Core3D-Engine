/*****************************************************************//**
 * \file   Core_Buffer.h
 * \brief  バッファ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_BUFFER_
#define _CORE_BUFFER_

#include "Core_CommonState.h"
#include <numeric>
#include <string>
#include <vector>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


namespace core
{
	/// @brief バッファID
	enum class BufferID : std::uint32_t {};
	/// @brief 存在しないバッファID
	constexpr BufferID NONE_BUFFER_ID = std::numeric_limits<BufferID>::max();

	/// @struct BufferData
	/// @brief バッファ初期化データ
	struct BufferData
	{
		const void* pInitData = nullptr;
		std::size_t size = 0;
	};

	/// @brief UAVフラグ
	enum class BufferUAVFlag : std::uint8_t
	{
		RAW,			///< バイトアドレス
		APPEND,		///< スタック操作
		COUNTER,		///< カウンター追加
	};

	/// @struct BufferDesc
	/// @brief バッファDesc
	struct BufferDesc
	{
		std::string		name;
		std::uint32_t	count			= 0;
		std::uint32_t	size				= 0;
		Usage			usage			= Usage::DEFAULT;
		std::uint32_t	bindFlags		= 0 | BindFlags::UNKNOWN;
		std::uint32_t	cpuAccessFlags	= 0 | CPUAccessFlags::NONE;
		std::uint32_t	miscFlags		= 0 | MiscFlags::UNKNONE;
		BufferUAVFlag	uavFlag			= BufferUAVFlag::RAW;
	};

	/// @class CoreBuffer
	/// @brief バッファ
	class CoreBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param id バッファID
		/// @param desc バッファDesc
		CoreBuffer(const BufferID& id, const BufferDesc& desc) :
			m_id(id), m_desc(desc), m_type(BufferType::MAX),
			m_isUpdate(true), m_aData()
		{
		}

		/// @brief デストラクタ
		virtual ~CoreBuffer() noexcept = default;

		/// @brief バッファ更新
		/// @param pData 更新データ
		/// @param size 更新サイズ
		void UpdateBuffer(void* pData, std::size_t size)
		{
			std::memcpy(m_aData.data(), pData, size);
			m_isUpdate = true;
		}

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief バッファタイプ
		enum class BufferType : std::uint8_t
		{
			CBV,
			SRV,
			UAV,
			MAX,
		};

		BufferID						m_id;		///< バッファID
		BufferDesc					m_desc;		///< バッファDesc
		BufferType					m_type;		///< バッファタイプ

		bool							m_isUpdate;	///< バッファ更新フラグ
		std::vector<std::byte>		m_aData;		///< CPU側のデータ

	};
}

#endif // !_CORE_BUFFER_
