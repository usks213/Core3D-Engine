/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  ���\�[�X�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include "Resource.h"
#include <unordered_map>
#include <memory>

class SceneManager;

class ResourceManager final
{
public:
	/// @brief �R���X�g���N�^
	/// @param pSceneManager �V�[���}�l�[�W���[�|�C���^
	explicit ResourceManager(SceneManager* pSceneManager) noexcept :
		m_pSceneManager(pSceneManager)
	{
	}

	/// @brief �f�X�g���N�^
	~ResourceManager() noexcept = default;

	/// @brief ���\�[�X�̐���
	/// @tparam T ���\�[�X�^
	/// @return ��������r���\�[�X�^�|�C���^
	template<class T, bool isResourceBase = std::is_base_of_v<Resource, T>>
	T* CreateResource()
	{
		static_assert(isResourceBase, "Not ResourceBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ����
		auto pResource = std::make_unique<T>();
		auto pResult = pResource.get();
		pResult->m_pResourceManager = this;
		pResult->m_instanceID = static_cast<InstanceID>(CreateResourceID(typeID));
		// �i�[
		m_resourcePool[typeID].emplace(pResult->GetResourceID(), std::move(pResource));

		return pResult;
	}

private:

	/// @brief �V�[���}�l�[�W���[
	SceneManager* m_pSceneManager;

	std::unordered_map<TypeID, std::unordered_map<ResourceID, std::unique_ptr<Resource>>>	m_resourcePool;

};


#endif // !_RESOURCE_MANAGER_

