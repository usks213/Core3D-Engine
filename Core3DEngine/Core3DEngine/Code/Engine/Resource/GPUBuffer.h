/*****************************************************************//**
 * \file   GPUBuffer.h
 * \brief  バッファ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_BUFFER_
#define _CORE_BUFFER_

#include <RHI\Core\CommonState.h>
#include <numeric>
#include <string>
#include <vector>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


namespace Core
{
	/// @brief バッファID
	enum class GPUBufferID : std::uint32_t {};
	/// @brief 存在しないバッファID
	constexpr GPUBufferID NONE_BUFFER_ID = std::numeric_limits<GPUBufferID>::max();

	/// @struct GPUBufferData
	/// @brief バッファ初期化データ
	struct GPUBufferData
	{
		const void* pInitData = nullptr;
		std::size_t size = 0;
	};

	/// @brief UAVフラグ
	enum class GPUBufferUAVFlag : std::uint8_t
	{
		RAW,			///< バイトアドレス
		APPEND,		///< スタック操作
		COUNTER,		///< カウンター追加
	};

	/// @struct GPUBufferDesc
	/// @brief バッファDesc
	struct GPUBufferDesc
	{
		std::string		name;
		std::uint32_t	count			= 0;
		std::uint32_t	size				= 0;
		Usage			usage			= Usage::DEFAULT;
		std::uint32_t	bindFlags		= 0 | BindFlags::UNKNOWN;
		std::uint32_t	cpuAccessFlags	= 0 | CPUAccessFlags::NONE;
		std::uint32_t	miscFlags		= 0 | MiscFlags::UNKNONE;
		GPUBufferUAVFlag	uavFlag			= GPUBufferUAVFlag::RAW;
	};

	/// @class GPUBuffer
	/// @brief バッファ
	class GPUBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param id バッファID
		/// @param desc バッファDesc
		GPUBuffer(const GPUBufferID& id, const GPUBufferDesc& desc) :
			m_id(id), m_desc(desc), m_type(BufferType::MAX),
			m_isUpdate(true), m_aData()
		{
		}

		/// @brief デストラクタ
		virtual ~GPUBuffer() noexcept = default;

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

		GPUBufferID						m_id;		///< バッファID
		GPUBufferDesc					m_desc;		///< バッファDesc
		BufferType					m_type;		///< バッファタイプ

		bool							m_isUpdate;	///< バッファ更新フラグ
		std::vector<std::byte>		m_aData;		///< CPU側のデータ

	};
}

#endif // !_CORE_BUFFER_
