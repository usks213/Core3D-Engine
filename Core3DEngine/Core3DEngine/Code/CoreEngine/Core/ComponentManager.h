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

class ComponentManager final
{
public:
	ComponentManager();
	~ComponentManager();


	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* CreateComponent()
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ����
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		// �i�[
		m_componentLookupTable[typeID].emplace(pCom->GetInstanceID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));

		return pResult;
	}

	void DestroyComponent(const TypeID& typeID ,const InstanceID& instanceID);

	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* FindComponent(const InstanceID& instanceID)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ����
		auto itr = m_componentLookupTable[typeID].find(instanceID);
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

	Component* RegisterComponent(const TypeID& typeID, const InstanceID& instanceID, Component* pComponent);

private:
	/// @brief �^���Ƃ̃R���|�[�l���g�v�[��
	std::unordered_map<TypeID, std::vector<std::unique_ptr<Component>>>		m_componentPool;
	/// @brief �R���|�[�l���g�̃��b�N�A�b�v�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<InstanceID, std::size_t>> m_componentLookupTable;

	/// @brief �������X�g
	std::unordered_map<TypeID, InstanceID>	m_createList;
	/// @brief �폜���X�g
	std::unordered_map<TypeID, InstanceID>	m_destroyList;

	/// @brief �A�N�e�B�u�R���|�[�l���g���X�g
	std::unordered_map<TypeID, std::vector<InstanceID>>						m_activeComponents;
	/// @brief �A�N�e�B�u�R���|�[�l���g�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<InstanceID, std::size_t>> m_activeComponentsTable;
	/// @brief ��A�N�e�B�u�R���|�[�l���g���X�g
	std::unordered_map<TypeID, std::vector<InstanceID>>						m_inactiveComponents;
	/// @brief ��A�N�e�B�u�R���|�[�l���g�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<InstanceID, std::size_t>> m_inactiveComponentsTable;

};

#endif // !_COMPONENT_MANAGER_
