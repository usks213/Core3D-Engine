/*****************************************************************//**
 * \file   Entity.h
 * \brief  �G���e�B�e�B
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "Script.h"
#include "ComponentManager.h"
#include <unordered_map>

class Component;
class EntityManager;
class Transform;

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
	explicit Entity() :
		Object("Entity"), 
		m_transformID(MAX_INSTANCE_ID),
		m_pComponentManager(nullptr),
		// param
		m_isActive(true),
		m_isStatic(false),
		m_tag("Default"),
		m_layer("Default")
	{
	}

	/// @brief �f�X�g���N�^
	~Entity() = default;


	/// @brief �R���|�[�l���g�̒ǉ�
	/// @tparam T �R���|�[�l���g�N���X
	/// @return �R���|�[�l���g�|�C���^
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* AddComponent()
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());

		// �R���|�[�l���g���X�N���v�g��
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- �X�N���v�g
			// ����
			auto itr = m_scripts.find(typeID);
			if (m_scripts.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
			// �V�K����
			T* pCom = m_pComponentManager->CreateComponent<T>(m_instanceID);
			pCom->m_parentID = m_instanceID;
			pCom->m_scriptID = T::GetScriptTypeID();
			// �i�[
			m_scripts.emplace(T::GetScriptTypeID(), pCom->GetInstanceID());

			return pCom;
		}
		else
		{
			//--- �R���|�[�l���g
			// ����
			auto itr = m_components.find(typeID);
			if (.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
			// �V�K����
			T* pCom = m_pComponentManager->CreateComponent<T>(m_instanceID);
			pCom->m_parentID = m_instanceID;
			// �i�[
			m_components.emplace(typeID, pCom->GetInstanceID());

			return pCom;
		}
	}

	/// @brief �R���|�[�l���g�̍폜
	/// @param pComponent �R���|�[�l���g�|�C���^
	void RemoveComponent(Component* pComponent)
	{
		TypeID typeID = pComponent->GetTypeID();
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- �X�N���v�g
			Script* pScript = static_cast<Script*>(pComponent);
			// ����
			auto itr = m_scripts.find(pScript->m_scriptID);
			if (m_scripts.end() != itr)
			{
				m_pComponentManager->DestroyComponent(typeID, itr->second);
			}
		}
		else
		{
			//--- �R���|�[�l���g
			// ����
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				m_pComponentManager->DestroyComponent(typeID, itr->second);
			}
		}
	}

	/// @brief �R���|�[�l���g�̎擾
	/// @tparam T �R���|�[�l���g�N���X
	/// @return �R���|�[�l���g�|�C���^
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* GetComponent()
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());

		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- �X�N���v�g
			ScriptID scriptID = T::GetScriptTypeID();
			// ����
			auto itr = m_scripts.find(scriptID);
			if (m_scripts.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
		}
		else
		{
			//--- �R���|�[�l���g
			// ����
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
		}
		// �Ȃ�
		return nullptr;
	}

	/// @brief �g�����X�t�H�[���̎擾
	/// @return 
	Transform* transform()
	{
		return m_pComponentManager->FindComponent<Transform>(m_transformID);
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
	/// @brief �ێ����Ă���X�N���v�g�R���|�[�l���g
	std::unordered_map<ScriptID, InstanceID> m_scripts;

	/// @brief �g�����X�t�H�[��ID
	InstanceID				m_transformID;
	/// @brief �R���|�[�l���g�}�l�[�W���[
	ComponentManager*		m_pComponentManager;

	//--- param

	bool					m_isActive;		///< �A�N�e�B�u�t���O
	bool					m_isStatic;		///< �ÓI�t���O
	std::string				m_tag;			///< �^�O
	std::string				m_layer;		///< ���C���[
};

#endif // !_ENTITY_
