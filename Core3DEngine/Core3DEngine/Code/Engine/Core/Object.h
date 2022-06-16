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
#include "TypeID.h"

namespace Core
{

/// @brief �I�u�W�F�N�g�̏���t��
#define DECLARE_OBJECT_INFO(T)											\
DECLARE_TYPE_INFO( T );													\
[[nodiscard]] TypeID GetTypeID() const noexcept override {				\
	return static_cast<TypeID>(GetTypeHash());							\
}																		\
[[nodiscard]] std::string_view GetTypeName() const noexcept override {	\
	return GetTypeString();												\
}																		
//enum class ID : BaseID {};												\
//[[nodiscard]] T::ID Get##T##ID() const noexcept {						\
//	return static_cast<T::ID>(GetInstanceID());							\
//}																		\
//static constexpr T::ID NONE_ID = NONE_TYPE_ID(T::ID);					\
//void _dumyFunction2() = delete


	/// @brief �I�u�W�F�N�g
	class Object
	{
	public:
		/// @brief �R���X�g���N�^
		explicit Object() noexcept :
			m_instanceID(NONE_INSTANCE_ID)
		{
		}

		/// @brief �R���X�g���N�^
		/// @param name ���O
		explicit Object(const InstanceID& id) noexcept :
			m_instanceID(id)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~Object() noexcept = default;

		/// @brief �^�C�vID�擾
		/// @return ID
		[[nodiscard]] virtual TypeID GetTypeID() const noexcept = 0;

		/// @brief �^�C�v���擾
		/// @return ���O
		[[nodiscard]] virtual std::string_view GetTypeName() const noexcept = 0;

		/// @brief �C���X�^���XID�擾
		/// @return ID
		[[nodiscard]] InstanceID GetInstanceID() const noexcept { return m_instanceID; }

		/// @brief �C���X�y�N�^�[�\��
		virtual void OnInspectorGUI() = 0;

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

	};

	// ������g����ID���^�ō��ʉ��ł���H

	/// @brief �I�u�W�F�N�g�̎Q��ID
	/// @tparam T �I�u�W�F�N�g�p���^
	template<class T, typename std::enable_if_t<std::is_base_of_v<Object, T>>>
	struct RefID
	{
		RefID() : m_id(NONE_INSTANCE_ID) {}
		explicit RefID(const InstanceID& id) : m_id(id) {}
		explicit RefID(const Object& object) : m_id(object.GetInstanceID()) {}
		explicit RefID(const Object* object) : m_id(object->GetInstanceID()) {}

		~RefID() noexcept = default;
		 
	private:
		InstanceID m_id;
	};
}

#endif // !_OBJECT_
