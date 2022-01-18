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


namespace Core
{
	class Engine;

	class ResourceManager final
	{
	public:
		/// @brief �R���X�g���N�^
		/// @param pSceneManager �V�[���}�l�[�W���[�|�C���^
		explicit ResourceManager(Engine* pEngine) noexcept :
			m_pEngine(pEngine)
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

		/// @brief �R���|�[�l���g���폜���X�g�ɓo�^
		/// @param typeID �R���|�[�l���g�^�C�vID
		/// @param componentID �R���|�[�l���gID
		void DestroyResource(const TypeID& typeID, const ResourceID& componentID);

		/// @brief �R���|�[�l���g�̌���
		/// @param typeID �R���|�[�l���g�^�C�vID
		/// @param componentID �R���|�[�l���gID
		/// @return �R���|�[�l���g�|�C���^ or nullptr
		Resource* GetResource(const TypeID& typeID, const ResourceID& componentID);

		/// @brief �R���|�[�l���g�̌���
		/// @tparam T �R���|�[�l���g�^
		/// @param componentID �R���|�[�l���gID
		/// @return �R���|�[�l���g�^�|�C���^ or nullptr
		template<class T, bool isComBase = std::is_base_of_v<Resource, T>>
		T* GetResource(const typename T::ID resourceID)
		{
			static_assert(isComBase, "Not ResourceBase");
			static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
			return static_cast<T*>(GetResource(typeID, componentID));
		}

		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		Engine* GetEngine() const noexcept { return m_pEngine; }

	private:

		/// @brief �G���W���|�C���^
		Engine* m_pEngine;

		std::unordered_map<TypeID, std::unordered_map<ResourceID, std::unique_ptr<Resource>>>	m_resourcePool;

	};
}

#endif // !_RESOURCE_MANAGER_

