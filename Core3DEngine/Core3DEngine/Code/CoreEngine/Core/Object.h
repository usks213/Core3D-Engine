/*****************************************************************//**
 * \file   Object.h
 * \brief  �I�u�W�F�N�g
 * \detail �C���X�y�N�^�[�ɕ\���\
 * 
 * \author USAMI KOSHI
 * \date   2021/011/13
 *********************************************************************/
#ifndef _OBJECT_
#define _OBJECT_

#include "TypeHash.h"

/// @brief ����ID(�T�C�Y)
using BaseID = std::uint32_t;

 /// @brief �C���X�^���XID
enum class InstanceID : BaseID;
/// @brief �^�C�vID
enum class TypeID : BaseID {};

/// @brief �ő�C���X�^���XID
constexpr InstanceID MAX_INSTANCE_ID = std::numeric_limits<InstanceID>::max();
/// @brief �ő�^�C�vID
constexpr TypeID MAX_TYPE_ID = std::numeric_limits<TypeID>::max();


 /// @brief �I�u�W�F�N�g�̏���t��
#define DECLARE_OBJECT_INFO(T)									\
DECLARE_TYPE_INFO( T );											\
[[nodiscard]] TypeID GetTypeID() noexcept override {			\
	return static_cast<TypeID>(GetTypeHash());					\
}																\
[[nodiscard]] std::string_view GetTypeName() noexcept override {\
	return GetTypeString();										\
}																\
void _dumyFunction2() = delete



/// @brief �I�u�W�F�N�g
class Object
{
public:
	/// @brief �R���X�g���N�^
	explicit Object() noexcept :
		m_instanceID(MAX_INSTANCE_ID), m_name("Object")
	{
	}

	/// @brief �R���X�g���N�^
	/// @param name ���O
	explicit Object(std::string_view name) noexcept :
		m_instanceID(MAX_INSTANCE_ID), m_name(name)
	{
	}

	/// @brief �R���X�g���N�^
	/// @param name ���O
	explicit Object(const InstanceID& id ,std::string_view name) noexcept :
		m_instanceID(id), m_name(name)
	{
	}

	/// @brief �f�X�g���N�^
	virtual ~Object() noexcept = default;

	/// @brief �^�C�vID�擾
	/// @return ID
	[[nodiscard]] virtual TypeID GetTypeID() noexcept = 0;

	/// @brief �^�C�v���擾
	/// @return ���O
	[[nodiscard]] virtual std::string_view GetTypeName() noexcept = 0;

	/// @brief �C���X�^���XID�擾
	/// @return ID
	[[nodiscard]] InstanceID GetInstanceID() noexcept { return m_instanceID; }

	/// @brief ���O�̎擾
	/// @return ���O
	[[nodiscard]] std::string_view GetName() noexcept { return m_name; }

	/// @brief �C���X�y�N�^�[�\��
	virtual void DispInspector() noexcept = 0;
	
	///// @brief �V���A���C�Y��
	//template<class T>
	//void serialize(T& archive)
	//{
	//	archive(CEREAL_NVP(m_instanceID), CEREAL_NVP(m_name));
	//}

protected:

	//--- serialize param

	/// @brief �C���X�^���XID
	InstanceID		m_instanceID;
	/// @brief ���O
	std::string		m_name;
};

#endif // !_OBJECT_
