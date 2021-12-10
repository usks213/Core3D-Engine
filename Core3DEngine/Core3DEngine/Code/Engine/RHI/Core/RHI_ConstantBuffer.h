/*****************************************************************//**
 * \file   RHI_ConstantBuffer.h
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
	class ConstantBuffer;

	/// @brief �R���X�^���g�o�b�t�@���C�A�E�g
	class ConstantBufferLayout
	{
		friend class ConstantBuffer;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		ConstantBufferLayout() :
			m_name(), m_slot(0), m_size(0), m_variables() 
		{}

		/// @brief �R���X�g���N�^
		/// @param slot �X���b�g
		/// @param name ���O
		/// @param size �T�C�Y
		ConstantBufferLayout(const std::uint32_t& slot, const std::string& name, const std::size_t& size) :
			m_slot(slot), m_name(name), m_size(size), m_variables() 
		{}

		/// @brief �f�X�g���N�^
		~ConstantBufferLayout() = default;

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

	/// @brief �R���X�^���g�o�b�t�@
	class ConstantBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		ConstantBuffer() : 
			m_data(),m_layout(), m_isDitry(false)
		{}

		/// @brief �R���X�g���N�^
		/// @param layout �R���X�^���g�o�b�t�@���C�A�E�g
		explicit ConstantBuffer(const ConstantBufferLayout& layout);

		/// @brief �f�X�g���N�^
		~ConstantBuffer() = default;

		/// @brief uint�ݒ�
		bool SetUint(const char* name, const unsigned int& data) { return SetData(name, &data); }

		/// @brief VectorUint2�ݒ�
		bool SetVectorUint2(const char* name, const VectorUint2& data) { return SetData(name, &data); }

		/// @brief VectorUint3�ݒ�
		bool SetVectorUint3(const char* name, const VectorUint3& data) { return SetData(name, &data); }

		/// @brief VectorUint4�ݒ�
		bool SetVectorUint4(const char* name, const VectorUint4& data) { return SetData(name, &data); }

		/// @brief float�ݒ�
		bool SetFloat(const char* name, const float& data) { return SetData(name, &data); }

		/// @brief Vector2�ݒ�
		bool SetVector2(const char* name, const Vector2& data) { return SetData(name, &data); }

		/// @brief Vector3�ݒ�
		bool SetVector3(const char* name, const Vector3& data) { return SetData(name, &data); }

		/// @brief Vector4�ݒ�
		bool SetVector4(const char* name, const Vector4& data) { return SetData(name, &data); }

		/// @brief Matrix�ݒ�
		bool SetMatrix(const char* name, const Matrix& data) { return SetData(name, &data); }

		/// @brief Struct�ݒ�
		bool SetStruct(const char* name, const void* data) { return SetData(name, &data); }

		/// @brief �f�[�^�擾
		template<class T>
		T GetData(const char* name)
		{
			auto itr = m_layout.m_variables.find(name);
			if (m_layout.m_variables.end() == itr) return T();

			return *(T*)(m_data.data() + itr->second.offset);
		}

	protected:
		//------------------------------------------------------------------------------
		// protected methods
		//------------------------------------------------------------------------------

		/// @brief �f�[�^�ݒ�
		bool SetData(const char* name, const void* data);

	private:
		ConstantBufferLayout	m_layout;
		std::vector<std::byte>	m_data;
		bool					m_isDitry;
	};
}


#endif // !_RHI_CONSTANT_BUFFER_

