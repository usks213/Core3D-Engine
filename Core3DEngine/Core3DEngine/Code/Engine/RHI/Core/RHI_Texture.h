/*****************************************************************//**
 * \file   RHI_Texture.h
 * \brief  �e�N�X�`��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_TEXTURE_
#define _CORE_TEXTURE_

#include <cstdint>
#include <string>
#include <RHI\Core\RHI_CommonState.h>

namespace Core::RHI
{
	/// @struct TextureData
	/// @brief �e�N�X�`���������f�[�^
	struct TextureData
	{
		const void* pInitData = nullptr;
		std::size_t size = 0;
	};

	/// @struct TextureDesc
	/// @brief �e�N�X�`��Desc
	struct TextureDesc
	{
		std::string			name;										///< �e�N�X�`����or�t�@�C���p�X
		std::uint32_t		width = 0;						///< ����(px)
		std::uint32_t		height = 0;						///< �c��(px)
		std::uint32_t		depth = 4;						///< �t�H�[�}�b�g�̐�(RGBA:4)
		std::uint32_t		mipLevels = 1;						///< �~�b�v�}�b�v���x��(0:��������)
		std::uint32_t		arraySize = 1;						///< �z��T�C�Y
		TextureFormat		format = TextureFormat::UNKNOWN;	///< �t�H�[�}�b�g
		SampleDesc			sampleDesc = SampleDesc();				///< �}���`�T���v���w��
		Usage				usage = Usage::DEFAULT;			///< ���\�[�X�g�p����
		std::uint32_t		bindFlags = 0 | BindFlags::UNKNOWN;	///< �o�C���h�t���O
		std::uint32_t		cpuAccessFlags = 0 | CPUAccessFlags::NONE;	///< CPU�A�N�Z�X�t���O
		std::uint32_t		miscFlags = 0 | MiscFlags::UNKNONE;	///< �o�b�t�@�w��t���O
	};

	/// @class Texture
	/// @brief �e�N�X�`��
	class Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^(�t�@�C���ǂݍ���)
		/// @param id �e�N�X�`��ID
		/// @param filepath �t�@�C���p�X
		explicit Texture(const std::string& filepath)
		{}

		/// @brief �R���X�g���N�^(Desc���琶��)
		/// @param id �e�N�X�`��ID
		/// @param desc �e�N�X�`��Desc
		explicit Texture(TextureDesc& desc, const TextureData* pData = nullptr)
		{}

		/// @brief �f�X�g���N�^
		virtual ~Texture() noexcept = default;


		/// @brief ���\�[�X�|�C���^�̎擾
		/// @return ���\�[�X�^
		virtual void* GetResource() = 0;

		/// @brief SRV�|�C���^�̎擾
		/// @return SRV�^
		virtual void* GetSRV() = 0;

		/// @brief UAV�|�C���^�̎擾
		/// @return UAV�^
		virtual void* GetUAV() = 0;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_CORE_TEXTURE_
