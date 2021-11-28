/*****************************************************************//**
 * \file   Entity.h
 * \brief  �G���e�B�e�B
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "ComponentManager.h"
#include "Script.h"

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
	explicit Entity() noexcept :
		Object(), 
		m_pEntityManager(nullptr),
		// components
		m_transformID(NONE_TRANSFORM_ID),
		m_components(),
		m_scripts(),
		// param
		m_name("Entity"),
		m_isActive(true),
		m_isStatic(false),
		m_tag("Default"),
		m_layer("Default")
	{
	}

	explicit Entity(const EntityID& id,
		EntityManager* pEntityManager,
		std::string_view name,
		bool bActive, bool bStatic) noexcept :
		// 
		Object(static_cast<InstanceID>(id)),
		m_pEntityManager(pEntityManager),
		// components
		m_transformID(NONE_TRANSFORM_ID),
		m_components(),
		m_scripts(),
		// param
		m_name(name),
		m_isActive(bActive),
		m_isStatic(bStatic),
		m_tag("Default"),
		m_layer("Default")
	{
	}

	/// @brief �f�X�g���N�^
	~Entity() noexcept = default;

	/// @brief ���g�̃G���e�B�e�BID�̎擾
	/// @return �G���e�B�e�BID
	[[nodiscard]] EntityID GetEntityID() noexcept
	{
		return static_cast<EntityID>(GetInstanceID());
	}

	/// @brief ���O�̎擾
	/// @return ���O
	[[nodiscard]] std::string_view GetName() noexcept { return m_name; }

	/// @brief ���O�̎w��
	/// @param name �G���e�B�e�B��
	void SetName(std::string_view name) noexcept { m_name = name; }


	/// @brief �R���|�[�l���g�̒ǉ�
	/// @tparam T �X�N���v�g�^�N���X
	/// @return �R���|�[�l���g�|�C���^
	template<class T, typename = std::enable_if_t<std::is_base_of_v<Component, T> && std::is_base_of_v<Script, T>>>
	T* AddComponent(T* Type = nullptr)
	{
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		static constexpr ScriptID scriptID = T::GetScriptTypeID();
		ComponentManager* pComponentManager = GetComponentManager();

		// �X�N���v�g��
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- �X�N���v�g
			// ����
			auto itr = m_scripts.find(scriptID);
			if (m_scripts.end() != itr)
			{
				return pComponentManager->FindComponent<T>(itr->second);
			}
			// �V�K����
			T* pCom = pComponentManager->CreateComponent<T>(GetEntityID(), m_isActive);
			// �i�[
			m_scripts.emplace(scriptID, pCom->GetComponentID());

			return pCom;
		}

		return nullptr;
	}

	/// @brief �R���|�[�l���g�̒ǉ�
	/// @tparam T �R���|�[�l���g�N���X
	/// @return �R���|�[�l���g�|�C���^
	template<class T, typename = std::enable_if_t<std::is_base_of_v<Component, T> && !std::is_base_of_v<Script, T>>>
	T* AddComponent()
	{
		//static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		ComponentManager* pComponentManager = GetComponentManager();
		//--- �R���|�[�l���g
		// ����
		auto itr = m_components.find(typeID);
		if (m_components.end() != itr)
		{
			return pComponentManager->FindComponent<T>(itr->second);
		}
		// �V�K����
		T* pCom = pComponentManager->CreateComponent<T>(GetEntityID(), m_isActive);
		// �i�[
		m_components.emplace(typeID, pCom->GetComponentID());

		return pCom;
	}

	/// @brief �R���|�[�l���g�̍폜
	/// @param pComponent �R���|�[�l���g�|�C���^
	void RemoveComponent(Component* pComponent)
	{
		ComponentManager* pComponentManager = GetComponentManager();
		TypeID typeID = pComponent->GetTypeID();
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- �X�N���v�g
			Script* pScript = static_cast<Script*>(pComponent);
			// ����
			auto itr = m_scripts.find(pScript->GetScriptID());
			if (m_scripts.end() != itr)
			{
				pComponentManager->DestroyComponent(typeID, itr->second);
			}
		}
		else
		{
			//--- �R���|�[�l���g
			// ����
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				pComponentManager->DestroyComponent(typeID, itr->second);
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
		ComponentManager* pComponentManager = GetComponentManager();

		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- �X�N���v�g
			ScriptID scriptID = T::GetScriptTypeID();
			// ����
			auto itr = m_scripts.find(scriptID);
			if (m_scripts.end() != itr)
			{
				return pComponentManager->FindComponent<T>(itr->second);
			}
		}
		else
		{
			//--- �R���|�[�l���g
			// ����
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				return pComponentManager->FindComponent<T>(itr->second);
			}
		}
		// �Ȃ�
		return nullptr;
	}

	/// @brief �A�N�e�B�u�w��
	/// @param isActive �t���O
	void SetActive(bool isActive);

	/// @brief �X�^�e�B�b�N�w��
	/// @param isStatic �t���O
	void SetStatic(bool isStatic);

	/// @brief �g�����X�t�H�[���̎擾
	/// @return �g�����X�t�H�[���|�C���^
	Transform* transform() noexcept;

	/// @brief �C���X�y�N�^�[�\��
	void OnInspectorGUI() override;

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

	/// @brief �R���|�[�l���g�}�l�[�W���[�擾
	/// @return �R���|�[�l���g�}�l�[�W���[�|�C���^
	ComponentManager* GetComponentManager() noexcept;

private:
	//--- none serialize param

	/// @brief �G���e�B�e�B�}�l�[�W���[
	EntityManager*		m_pEntityManager;

	//--- serialize param

	/// @brief �g�����X�t�H�[��ID
	TransformID								 m_transformID;
	/// @brief �ێ����Ă���R���|�[�l���g
	std::unordered_map<TypeID, ComponentID>	 m_components;
	/// @brief �ێ����Ă���X�N���v�g�R���|�[�l���g
	std::unordered_map<ScriptID, ComponentID> m_scripts;

	std::string				m_name;			///< �G���e�B�e�B��
	bool					m_isActive;		///< �A�N�e�B�u�t���O
	bool					m_isStatic;		///< �ÓI�t���O
	std::string				m_tag;			///< �^�O
	std::string				m_layer;		///< ���C���[
};

#endif // !_ENTITY_
