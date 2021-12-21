/*****************************************************************//**
 * \file   RHI_GPUBuffer.h
 * \brief  �o�b�t�@
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
		/// @brief �o�b�t�@�^�C�v
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

		/// @brief �R���X�g���N�^
		/// @param id �o�b�t�@ID
		/// @param desc �o�b�t�@Desc
		GPUBuffer(const GPUBufferDesc& desc) :
			m_desc(desc), m_type(BufferType::MAX),
			m_isDirty(true), m_aData()
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
			m_isDirty = true;
		}

		/// @brief �o�b�t�@���擾
		/// @return �o�b�t�@Desc
		GPUBufferDesc GetDesc() { return m_desc; }

		/// @brief ���\�[�X�|�C���^�̎擾
		/// @return ���\�[�X�^
		virtual void* GetResource() = 0;

		/// @brief CBV�|�C���^�̎擾
		/// @return CBV�^
		virtual void* GetCBV() = 0;

		/// @brief SRV�|�C���^�̎擾
		/// @return SRV�^
		virtual void* GetSRV() = 0;

		/// @brief UAV�|�C���^�̎擾
		/// @return UAV�^
		virtual void* GetUAV() = 0;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		GPUBufferDesc				m_desc;		///< �o�b�t�@Desc
		BufferType					m_type;		///< �o�b�t�@�^�C�v

		bool							m_isDirty;	///< �o�b�t�@�X�V�t���O
		std::vector<std::byte>		m_aData;		///< CPU���̃f�[�^

	};
}

#endif // !_RHI_GPU_BUFFER_
