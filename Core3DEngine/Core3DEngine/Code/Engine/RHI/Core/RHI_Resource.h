/*****************************************************************//**
 * \file   RHI_Resource.h
 * \brief  ���\�[�X
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
	/// @brief ���\�[�X�������f�[�^
	struct ResourceData
	{
		const void* pInitData = nullptr;
		std::size_t size = 0;
	};

	/// @brief UAV�t���O
	enum class UAVFlag : std::uint8_t
	{
		RAW,		///< �o�C�g�A�h���X
		APPEND,		///< �X�^�b�N����
		COUNTER,	///< �J�E���^�[�ǉ�
	};

	/// @struct ResourceDesc
	/// @brief ���\�[�XDesc
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
				std::uint32_t		width = 0;						///< ����(px)
				std::uint32_t		height = 0;						///< �c��(px)
				std::uint32_t		depth = 4;						///< �t�H�[�}�b�g�̐�(RGBA:4)
				std::uint32_t		mipLevels = 1;						///< �~�b�v�}�b�v���x��(0:��������)
				std::uint32_t		arraySize = 1;						///< �z��T�C�Y
				TextureFormat		format = TextureFormat::UNKNOWN;	///< �t�H�[�}�b�g
				SampleDesc			sampleDesc = SampleDesc();				///< �}���`�T���v���w��
			} texture;
		};
		Usage				usage = Usage::DEFAULT;
		std::uint32_t		bindFlags = 0 | BindFlags::UNKNOWN;
		std::uint32_t		cpuAccessFlags = 0 | CPUAccessFlags::NONE;
		std::uint32_t		miscFlags = 0 | MiscFlags::UNKNONE;
		UAVFlag				uavFlag = UAVFlag::RAW;
	};

	/// @class Resource
	/// @brief ���\�[�X
	class Resource
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		Resource() :
			m_desc(), m_isDirty(false), m_aData()
		{
		}

		/// @brief �R���X�g���N�^
		/// @param desc ���\�[�XDesc
		Resource(const ResourceDesc& desc) :
			m_desc(desc), m_isDirty(false), m_aData()
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~Resource() noexcept = default;

		/// @brief ���\�[�X�X�V
		/// @param pData �X�V�f�[�^
		/// @param size �X�V�T�C�Y
		void UpdateResource(void* pData, std::size_t size)
		{
			std::memcpy(m_aData.data(), pData, size);
			m_isDirty = true;
		}

		/// @brief ���\�[�X���擾
		/// @return ���\�[�XDesc
		ResourceDesc GetDesc() { return m_desc; }

		/// @brief CPU�f�[�^�̎擾
		/// @return �ėp�|�C���g
		void* GetData() { return m_aData.data(); }

		/// @brief CPU�f�[�^�T�C�Y�̎擾
		/// @return �f�[�^�T�C�Y
		std::size_t GetDataSize() { return m_aData.size(); }

		/// @brief �X�V�t���O�擾
		/// @return TRUE �X�V�ς� / FALSE ���X�V
		bool GetDirty() { return m_isDirty; }

		/// @brief �X�V�t���O�����ɖ߂�
		void ResetDirty() { m_isDirty = false; }

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

		ResourceDesc				m_desc;		///< ���\�[�XDesc
		bool						m_isDirty;	///< ���\�[�X�X�V�t���O
		std::vector<std::byte>		m_aData;	///< CPU���̃f�[�^

	};
}

#endif // !_RHI_RESOURCE_
