/*****************************************************************//**
 * \file   SystemManager.h
 * \brief  �V�X�e��
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _SYSTEM_MANAGER_
#define _SYSTEM_MANAGER_

#include "System.h"
#include <unordered_map>
#include <memory>

namespace Core
{
	class Scene;

	class SystemManager final
	{
	public:
		/// @brief �R���X�g���N�^
		/// @param pScene �V�[���|�C���^
		explicit SystemManager(Scene* pScene);

		/// @brief �f�X�g���N�^
		~SystemManager() noexcept = default;

		/// @brief �V�X�e���X�V
		void Update();

		/// @brief �M�Y���\��
		void DispGizmo();

		/// @brief �V�X�e���̒ǉ�
		/// @tparam T �V�X�e���p���^
		/// @return ���������V�X�e��
		template<class T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T* AddSystem()
		{
			static constexpr SystemID systemID = static_cast<SystemID>(T::GetTypeHash());
			// ����
			auto itr = m_systemPool.find(systemID);
			if (m_systemPool.end() != itr)
				return static_cast<T*>(itr->second.get());
			// �V�K����
			auto pSystem = std::make_unique<T>(this);
			T* pResult = pSystem.get();
			// �i�[
			m_systemPool.emplace(systemID, std::move(pSystem));

			return pResult;
		}

		/// @brief �V�X�e���̎擾
		/// @tparam T �V�X�e���p���^
		/// @return ��v T* or �s��v nullptr
		template<class T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T* GetSystem()
		{
			static constexpr SystemID systemID = static_cast<SystemID>(T::GetTypeHash());
			// ����
			auto itr = m_systemPool.find(systemID);
			// ��v
			if (m_systemPool.end() != itr)
				return  static_cast<T*>(itr->second.get());
			// �s��v
			return nullptr;
		}

		/// @brief �V�X�e���̍폜
		/// @tparam T �V�X�e���p���^
		/// @return ���� TRUE / ���s FALSE
		template<class T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		bool RemoveSystem()
		{
			static constexpr SystemID systemID = static_cast<SystemID>(T::GetTypeHash());
			// ����
			auto itr = m_systemPool.find(systemID);
			// ��v
			if (m_systemPool.end() != itr)
			{
				m_systemPool.erase(itr);
				return true;
			}
			return false;
		}

		/// @brief �����V�[���̎擾
		/// @return �V�[���|�C���^
		Scene* GetScene() { return m_pScene; }

	private:
		/// @brief �����V�[��
		Scene* m_pScene;
		/// @brief �V�X�e���v�[��
		std::unordered_map<SystemID, std::unique_ptr<System>> m_systemPool;
	};
}

#endif // !_SYSTEM_MANAGER_
