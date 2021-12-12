/*****************************************************************//**
 * \file   RHI_ShaderCBufferLayout.h
 * \brief  �R���X�^���g�o�b�t�@
 *
 * \author USAMI KOSHI
 * \date   2021/12/04
 *********************************************************************/
#ifndef _RHI_CONSTANT_BUFFER_
#define _RHI_CONSTANT_BUFFER_

#include <vector>
#include <unordered_map>
#include <Utils\Util_Mathf.h>

namespace Core::RHI
{
	/// @brief �R���X�^���g�o�b�t�@���C�A�E�g
	class ShaderCBufferLayout
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		ShaderCBufferLayout() :
			m_name(), m_slot(0), m_size(0), m_variables() 
		{}

		/// @brief �R���X�g���N�^
		/// @param slot �X���b�g
		/// @param name ���O
		/// @param size �T�C�Y
		ShaderCBufferLayout(const std::uint32_t& slot, const std::string& name, const std::size_t& size) :
			m_slot(slot), m_name(name), m_size(size), m_variables() 
		{}

		/// @brief �f�X�g���N�^
		~ShaderCBufferLayout() = default;

	public:
		/// @brief CBuffer�̕ϐ����
		struct CBufferVariable
		{
			//std::string		name;			///< �ϐ���
			std::size_t		size	= 0;		///< �^�T�C�Y
			std::size_t		offset	= 0;		///< �ϐ��I�t�Z�b�g
			std::uint8_t	stage	= 0;		///< �X�e�[�W
			std::uint8_t	slot	= 0;		///< �X���b�g
			std::vector<std::byte> defaultVal;	///< �f�t�H���g�l
		};

	private:
		//------------------------------------------------------------------------------
		// private variabes
		//------------------------------------------------------------------------------

		std::string						m_name;			///< cbuffer�錾��
		std::uint32_t					m_slot;			///< ���W�X�^�X���b�g
		std::size_t						m_size;			///< cbuffer�T�C�Y
		std::unordered_map<std::string, CBufferVariable>	m_variables;	///< �ϐ��f�[�^
	};

	///// @brief �R���X�^���g�o�b�t�@
	//class ShaderCBufferLayout
	//{
	//public:
	//	//------------------------------------------------------------------------------
	//	// public methods
	//	//------------------------------------------------------------------------------

	//	/// @brief �R���X�g���N�^
	//	ShaderCBufferLayout() : 
	//		m_data(),m_layout(), m_isDitry(false)
	//	{}

	//	/// @brief �R���X�g���N�^
	//	/// @param layout �R���X�^���g�o�b�t�@���C�A�E�g
	//	explicit ShaderCBufferLayout(const ShaderCBufferLayoutLayout& layout);

	//	/// @brief �f�X�g���N�^
	//	~ShaderCBufferLayout() = default;

	//	/// @brief �f�[�^�擾
	//	template<class T>
	//	T GetData(const char* name)
	//	{
	//		auto itr = m_layout.m_variables.find(name);
	//		if (m_layout.m_variables.end() == itr) return T();

	//		return *(T*)(m_data.data() + itr->second.offset);
	//	}

	//	/// @brief �f�[�^�ݒ�
	//	bool SetData(const char* name, const void* data);

	//protected:
	//	//------------------------------------------------------------------------------
	//	// protected methods
	//	//------------------------------------------------------------------------------

	//private:
	//	ShaderCBufferLayoutLayout	m_layout;
	//	std::vector<std::byte>	m_data;
	//	bool					m_isDitry;
	//};
}


#endif // !_RHI_CONSTANT_BUFFER_

