/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  ���\�[�X�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <Utils\Util_Singleton.h>
#include "Resource.h"
#include <unordered_map>
#include <memory>


namespace Core
{
	class ResourceManager final : public Util::Singleton<ResourceManager>
	{
	public:
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

		/// @brief ���\�[�X���폜���X�g�ɓo�^
		/// @tparam T ���\�[�X�^
		/// @param typeID ���\�[�X�^�C�vID
		/// @param resourceID ���\�[�XID
		template<class T, bool isResourceBase = std::is_base_of_v<Resource, T>>
		T* DestroyResource(const typename T::ID resourceID)
		{
			static_assert(isResourceBase, "Not ResourceBase");
			static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
			return static_cast<T*>(DestroyResource(typeID, static_cast<Resource::ID>(resourceID)));
		}

		/// @brief ���\�[�X�̌���
		/// @tparam T ���\�[�X�^
		/// @param resourceID ���\�[�XID
		/// @return ���\�[�X�^�|�C���^ or nullptr
		template<class T, class U, bool isResourceBase = std::is_base_of_v<Resource, T>, 
			bool isID = std::is_same_v<typename T::ID, U>>
		T* GetResource(const U resourceID)
		{
			static_assert(isResourceBase, "Not ResourceBase");
			static_assert(isID, "Not ID");
			static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
			return static_cast<T*>(GetResource(typeID, static_cast<Resource::ID>(resourceID)));
		}

		/// @brief ���\�[�X���폜���X�g�ɓo�^
		/// @param typeID ���\�[�X�^�C�vID
		/// @param resourceID ���\�[�XID
		void DestroyResource(const TypeID& typeID, const Resource::ID& resourceID);

		/// @brief ���\�[�X�̌���
		/// @param typeID ���\�[�X�^�C�vID
		/// @param resourceID ���\�[�XID
		/// @return ���\�[�X�|�C���^ or nullptr
		Resource* GetResource(const TypeID& typeID, const Resource::ID& resourceID);

		/// @brief �폜���X�g�̎��s
		void CleanupResource();

	private:

		/// @brief ���\�[�X�v�[��
		std::unordered_map<TypeID, std::unordered_map<Resource::ID, std::unique_ptr<Resource>>>	m_resourcePool;

		/// @brief �폜���X�g
		std::unordered_map<TypeID, std::vector<Resource::ID>>					m_destroyList;
	};
}

#endif // !_RESOURCE_MANAGER_

