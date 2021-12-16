/*****************************************************************//**
 * \file   GPUBuffer.h
 * \brief  �o�b�t�@
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
	/// @brief �o�b�t�@ID
	enum class GPUBufferID : std::uint32_t {};
	/// @brief ���݂��Ȃ��o�b�t�@ID
	constexpr GPUBufferID NONE_BUFFER_ID = std::numeric_limits<GPUBufferID>::max();

	/// @struct GPUBufferData
	/// @brief �o�b�t�@�������f�[�^
	struct GPUBufferData
	{
		const void* pInitData = nullptr;
		std::size_t size = 0;
	};

	/// @brief UAV�t���O
	enum class GPUBufferUAVFlag : std::uint8_t
	{
		RAW,			///< �o�C�g�A�h���X
		APPEND,		///< �X�^�b�N����
		COUNTER,		///< �J�E���^�[�ǉ�
	};

	/// @struct GPUBufferDesc
	/// @brief �o�b�t�@Desc
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
	/// @brief �o�b�t�@
	class GPUBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param id �o�b�t�@ID
		/// @param desc �o�b�t�@Desc
		GPUBuffer(const GPUBufferID& id, const GPUBufferDesc& desc) :
			m_id(id), m_desc(desc), m_type(BufferType::MAX),
			m_isUpdate(true), m_aData()
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~GPUBuffer() noexcept = default;

		/// @brief �o�b�t�@�X�V
		/// @param pData �X�V�f�[�^
		/// @param size �X�V�T�C�Y
		void UpdateBuffer(void* pData, std::size_t size)
		{
			std::memcpy(m_aData.data(), pData, size);
			m_isUpdate = true;
		}

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �o�b�t�@�^�C�v
		enum class BufferType : std::uint8_t
		{
			CBV,
			SRV,
			UAV,
			MAX,
		};

		GPUBufferID						m_id;		///< �o�b�t�@ID
		GPUBufferDesc					m_desc;		///< �o�b�t�@Desc
		BufferType					m_type;		///< �o�b�t�@�^�C�v

		bool							m_isUpdate;	///< �o�b�t�@�X�V�t���O
		std::vector<std::byte>		m_aData;		///< CPU���̃f�[�^

	};
}

#endif // !_CORE_BUFFER_
