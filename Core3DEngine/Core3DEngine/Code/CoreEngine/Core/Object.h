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

 /// @brief �C���X�^���XID
enum class InstanceID : std::uint32_t;
/// @brief �^�C�vID
enum class TypeID : std::uint32_t {};

/// @brief �ő�C���X�^���XID
constexpr InstanceID MAX_INSTANCE_ID = std::numeric_limits<InstanceID>::max();
/// @brief �ő�^�C�vID
constexpr TypeID MAX_TYPE_ID = std::numeric_limits<TypeID>::max();


 /// @brief �I�u�W�F�N�g�̏���t��
#define DECLARE_OBJECT_INFO(T)									\
DECLARE_TYPE_INFO( T );											\
[[nodiscard]] TypeID GetTypeID() override {						\
	return static_cast<TypeID>(GetTypeHash());					\
}																\
[[nodiscard]] std::string_view GetTypeName() override {			\
	return GetTypeString();										\
}																\
void _dumyFunction2() = delete



/// @brief �I�u�W�F�N�g
class Object
{
public:
	/// @brief �R���X�g���N�^
	/// @param id �C���X�^���XID
	/// @param name ���O
	explicit Object(const InstanceID& id, std::string_view name) :
		m_instanceID(id), m_name(name)
	{
	}

	/// @brief �f�X�g���N�^
	~Object() = default;

	/// @brief �^�C�vID�擾
	/// @return ID
	[[nodiscard]] virtual TypeID GetTypeID() = 0;

	/// @brief �^�C�v���擾
	/// @return ���O
	[[nodiscard]] virtual std::string_view GetTypeName() = 0;

	/// @brief �C���X�^���XID�擾
	/// @return ID
	[[nodiscard]] InstanceID GetInstanceID() { return m_instanceID; }

	/// @brief ���O�̎擾
	/// @return ���O
	[[nodiscard]] std::string_view GetName() { return m_name; }

	///// @brief �V���A���C�Y��
	//template<class T>
	//void serialize(T& archive)
	//{
	//	archive(CEREAL_NVP(m_instanceID), CEREAL_NVP(m_name));
	//}

protected:
	/// @brief �C���X�^���XID
	InstanceID		m_instanceID;
	/// @brief ���O
	std::string		m_name;
};

#endif // !_OBJECT_
