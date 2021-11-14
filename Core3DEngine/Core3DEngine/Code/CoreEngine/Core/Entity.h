/*****************************************************************//**
 * \file   Entity.h
 * \brief  �G���e�B�e�B
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "Object.h"
#include <unordered_map>

class Component;
class EntityManager;
class ComponentManager;

/// @brief �G���e�B�e�B
class Entity final : public Object
{
	friend class Component;
	friend class EntityManager;
public:
	/// @brief �I�u�W�F�N�g���
	DECLARE_OBJECT_INFO(Entity);

	/// @brief �R���X�g���N�^
	/// @param id �G���e�B�e�BID
	/// @param entity �G���e�B�e�B
	explicit Entity(ComponentManager* pComponentManager, const InstanceID& id,
		std::string_view name, const InstanceID& transformID) :
		Object(id, name), 
		m_transformID(transformID),
		m_pComponentManager(pComponentManager)
	{
	}

	/// @brief �f�X�g���N�^
	~Entity() = default;


	template<class T>
	constexpr T* AddComponent()
	{
		constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ����

	}


	///// @brief �V���A���C�Y��
	//template<class T>
	//void serialize(T& archive)
	//{
	//	Object::serialize(archive);
	//	archive(
	//		CEREAL_NVP(m_entity),
	//		CEREAL_NVP(m_parentID),
	//		CEREAL_NVP(m_childsID)
	//	);
	//}

private:
	/// @brief �ێ����Ă���R���|�[�l���g
	std::unordered_map<TypeID, InstanceID> m_components;
	/// @brief �g�����X�t�H�[��ID
	InstanceID				m_transformID;
	/// @brief �R���|�[�l���g�}�l�[�W���[
	ComponentManager*		m_pComponentManager;

};

#endif // !_ENTITY_
