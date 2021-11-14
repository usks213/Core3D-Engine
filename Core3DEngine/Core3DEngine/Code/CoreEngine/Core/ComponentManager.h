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
		// ����
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		TypeID typeID = pCom->GetTypeID();
		// �i�[
		m_componentLookupTable[typeID].emplace(pCom->GetInstanceID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));
		
		return pResult;
	}

	void DestroyComponent();


	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* FindComponent(const InstanceID& instanceID)
	{
		static_assert(isComBase, "Not ComponentBase");
		// ����
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		TypeID typeID = pCom->GetTypeID();
		// �i�[
		m_componentLookupTable[typeID].emplace(pCom->GetInstanceID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));

		return pResult;
	}

private:
	/// @brief �^���Ƃ̃R���|�[�l���g�v�[��
	std::unordered_map<TypeID, std::vector<std::unique_ptr<Component>>> m_componentPool;
	/// @brief �R���|�[�l���g�̃��b�N�A�b�v�e�[�u��
	std::unordered_map<TypeID, std::unordered_map<InstanceID, std::size_t>> m_componentLookupTable;
};

#endif // !_COMPONENT_MANAGER_
