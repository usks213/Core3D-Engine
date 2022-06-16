/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  ���\�[�X�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "ResourceManager.h"

using namespace Core;

 /// @brief ���\�[�X���폜���X�g�ɓo�^
 /// @param typeID ���\�[�X�^�C�vID
 /// @param resourceID ���\�[�XID
void ResourceManager::DestroyResource(const TypeID& typeID, const ResourceID& resourceID)
{
	// ����
	Resource* pResource = GetResource(typeID, resourceID);
	if (pResource)
	{
		//�@�i�[
		m_destroyList[typeID].push_back(resourceID);
	}
}

/// @brief ���\�[�X�̌���
/// @param typeID ���\�[�X�^�C�vID
/// @param resourceID ���\�[�XID
/// @return ���\�[�X�|�C���^ or nullptr
Resource* ResourceManager::GetResource(const TypeID& typeID, const ResourceID& resourceID)
{
	// ����
	auto itr = m_resourcePool[typeID].find(resourceID);
	if (m_resourcePool[typeID].end() == itr)
	{
		return nullptr;
	}
	return itr->second.get();
}

/// @brief �폜���X�g�̎��s
void ResourceManager::CleanupResource()
{
	for (auto& resoures : m_destroyList)
	{
		auto typeID = resoures.first;
		for (auto& id : resoures.second)
		{
			// ����
			auto itr = m_resourcePool[typeID].find(id);
			if (m_resourcePool[typeID].end() == itr) continue;

			// �폜
			m_resourcePool[typeID].erase(itr);
		}
	}
}
