/*****************************************************************//**
 * \file   ComponentManager.h
 * \brief  �R���|�[�l���g�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/20
 *********************************************************************/
#include "ComponentManager.h"

 /// @brief �R���|�[�l���g���폜���X�g�ɓo�^
 /// @param typeID �R���|�[�l���g�^�C�vID
 /// @param componentID �R���|�[�l���gID
void ComponentManager::DestroyComponent(const TypeID& typeID, const ComponentID& componentID)
{
	// ����
	Component* pCom = FindComponent(typeID, componentID);
	if (pCom)
	{
		// �폜���R�[���o�b�N
		pCom->OnDestroy();
		//�@�i�[
		m_destroyList[typeID].push_back(componentID);
	}
}

/// @brief �R���|�[�l���g�̌���
/// @param typeID �R���|�[�l���g�^�C�vID
/// @param componentID �R���|�[�l���gID
/// @return �R���|�[�l���g�^�|�C���^ or nullptr
Component* ComponentManager::FindComponent(const TypeID& typeID, const ComponentID& componentID)
{
	// ����
	auto itr = m_componentLookupTable[typeID].find(componentID);
	if (m_componentLookupTable[typeID].end() == itr)
	{
		return nullptr;
	}
	return m_componentPool[typeID][itr->second].get();
}

/// @brief �R���|�[�l���g�̗L���w��
/// @param pComponent �Ώۂ̃R���|�[�l���g�|�C���^
/// @param isEnable �L���t���O
void ComponentManager::SetComponentEnable(Component* pComponent, bool isEnable)
{
	//--- �e���X�g�ɑ��݂�����폜
	auto typeID = pComponent->GetTypeID();
	auto comID = pComponent->GetComponentID();

	// �L�����X�g
	auto enableItr = m_enableComponentsTable[typeID].find(comID);
	if (m_enableComponentsTable[typeID].end() != enableItr)
	{
		// �Ō���Ɠ���ւ�
		auto backComID = m_enableComponents[typeID].back();
		m_enableComponents[typeID][enableItr->second] = backComID;
		m_enableComponentsTable[typeID][backComID] = enableItr->second;
		// �폜
		m_enableComponents[typeID].pop_back();
		m_enableComponentsTable[typeID].erase(enableItr);
	}

	// �������X�g
	auto disable = m_disableComponentsTable[typeID].find(comID);
	if (m_disableComponentsTable[typeID].end() != enableItr)
	{
		// �Ō���Ɠ���ւ�
		auto backComID = m_disableComponents[typeID].back();
		m_disableComponents[typeID][enableItr->second] = backComID;
		m_disableComponentsTable[typeID][backComID] = enableItr->second;
		// �폜
		m_disableComponents[typeID].pop_back();
		m_disableComponentsTable[typeID].erase(enableItr);
	}

	// �ύX��ɒǉ�
	if (isEnable)
	{
		// �L��
		Index index = m_enableComponents[typeID].size();
		m_enableComponents[typeID].push_back(comID);
		m_enableComponentsTable[typeID].emplace(comID, index);
		//�@�R�[���o�b�N
		pComponent->OnEnable();
	}
	else
	{
		// ����
		Index index = m_disableComponents[typeID].size();
		m_disableComponents[typeID].push_back(comID);
		m_disableComponentsTable[typeID].emplace(comID, index);
		//�@�R�[���o�b�N
		pComponent->OnDisable();
	}
}

/// @brief �폜���X�g�̎��s
void ComponentManager::CleanupComponent()
{
	for (auto& comList : m_destroyList)
	{
		auto typeID = comList.first;
		for (auto& comID : comList.second)
		{
			// ����
			auto itr = m_componentLookupTable[typeID].find(comID);
			if (m_componentLookupTable[typeID].end() == itr) continue;

			// ID
			auto backComID = m_componentPool[typeID].back()->GetComponentID();
			// �Ō���Ɠ���ւ�
			m_componentPool[typeID][itr->second] = std::move(m_componentPool[typeID].back());
			m_componentLookupTable[typeID][backComID] = itr->second;

			// �폜
			m_componentPool[typeID].pop_back();
			m_componentLookupTable[typeID].erase(itr);
		}
	}
}
