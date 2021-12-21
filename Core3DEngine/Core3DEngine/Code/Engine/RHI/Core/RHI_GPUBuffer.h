/*****************************************************************//**
 * \file   RHI_GPUBuffer.h
 * \brief  バッファ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_GPU_BUFFER_
#define _RHI_GPU_BUFFER_

#include "RHI_CommonState.h"
#include <numeric>
#include <string>
#include <vector>


namespace Core::RHI
{
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
		/// @brief バッファタイプ
		enum class BufferType : std::uint8_t
		{
			VBV,
			IBV,
			CBV,
			SRV,
			UAV,
			MAX,
		};
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param id バッファID
		/// @param desc バッファDesc
		GPUBuffer(const GPUBufferDesc& desc) :
			m_desc(desc), m_type(BufferType::MAX),
			m_isDirty(true), m_aData()
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
			m_isDirty = true;
		}

		/// @brief バッファ情報取得
		/// @return バッファDesc
		GPUBufferDesc GetDesc() { return m_desc; }

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

		GPUBufferDesc				m_desc;		///< バッファDesc
		BufferType					m_type;		///< バッファタイプ

		bool							m_isDirty;	///< バッファ更新フラグ
		std::vector<std::byte>		m_aData;		///< CPU側のデータ

	};
}

#endif // !_RHI_GPU_BUFFER_
