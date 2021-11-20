/*****************************************************************//**
 * \file   ComponentManager.h
 * \brief  �R���|�[�l���g�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _COMPONENT_MANAGER_
#define _COMPONENT_MANAGER_

#include "Component.h"

#include <memory>
#include <vector>
#include <unordered_map>

class Scene;

class ComponentManager final
{
public:
	/// @brief �R���X�g���N�^
	/// @param pScene �V�[���|�C���^
	explicit ComponentManager(Scene* pScene) noexcept :
		m_pScene(pScene)
	{
	}

	/// @brief �f�X�g���N�^
	~ComponentManager() noexcept = default;


	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* CreateComponent(const EntityID& entityID, bool isEnable)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ID����

		// ����
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		pResult->m_instanceID = ;
		pResult->m_entityID = entityID;
		pResult->m_isEnable = isEnable;
		// �i�[
		m_componentLookupTable[typeID].emplace(pCom->GetComponentID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));

		return pResult;
	}

	void DestroyComponent(const TypeID& typeID ,const ComponentID& componentID);

	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* FindComponent(const ComponentID& componentID)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ����
		auto itr = m_componentLookupTable[typeID].find(componentID);
		if (m_componentLookupTable[typeID].end()) == itr)
		{
			return nullptr;
		}
		return static_cast<T*>(m_componentPool[typeID][itr->second].get());
	}

	/// @brief �폜���X�g�̎��s
	void CleanupComponent();

	/// @brief �R���|�[�l���g�̃V���A���C�Y
	void Serialize();

	/// @brief �R���|�[�l���g�̃f�V���A���C�Y
	void Deserialize();

private:

	Component* RegisterComponent(const TypeID& typeID, const ComponentID& componentID, Component* pComponent);

private:
	/// @brief vectorIndex
	using Index = std::size_t;

	//--- serialize param

	/// @brief �^���Ƃ̃R���|�[�l���g�v�[��
	std::unordered_map<TypeID, std::vector<std::unique_ptr<Component>>>		m_componentPool;

	//--- none serialize param

	/// @brief �����V�[��
	Scene* m_pScene;

	/// @brief �R���|�[�l���g�̃��b�N�A�b�v�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_componentLookupTable;

	/// @brief �������X�g
	std::unordered_map<TypeID, ComponentID>	m_createList;
	/// @brief �폜���X�g
	std::unordered_map<TypeID, ComponentID>	m_destroyList;

	/// @brief �A�N�e�B�u�R���|�[�l���g���X�g
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_activeComponents;
	/// @brief �A�N�e�B�u�R���|�[�l���g�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_activeComponentsTable;
	/// @brief ��A�N�e�B�u�R���|�[�l���g���X�g
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_inactiveComponents;
	/// @brief ��A�N�e�B�u�R���|�[�l���g�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_inactiveComponentsTable;

};

#endif // !_COMPONENT_MANAGER_
