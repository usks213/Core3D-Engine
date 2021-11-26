/*****************************************************************//**
 * \file   EditorWindowManager.h
 * \brief  �G�f�B�^�[�E�B���h�E�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _EDITOR_WINDOW_MANAGER_
#define _EDITOR_WINDOW_MANAGER_

#include "EditorWindow.h"
#include <unordered_map>
#include <memory>

namespace core
{
	class CoreEditor;
}

/// @brief �G�f�B�^�[�E�B���h�E�}�l�[�W���[�N���X
class EditorWindowManager final
{
public:
	/// @brief �R���X�g���N�^
	/// @param pCoreEditor �R�A�G�f�B�^�[�|�C���^
	explicit EditorWindowManager(core::CoreEditor* pCoreEditor) noexcept :
		m_pCoreEditor(pCoreEditor)
	{
	}

	/// @brief �f�X�g���N�^
	~EditorWindowManager() noexcept = default;

	/// @brief �E�B���h�E�̕\��
	void DispWindow()
	{
		for (auto& window : m_windowPool)
		{
			//window.second->DispWindow();
		}
	}

	/// @brief �G�f�B�^�[�E�B���h�E�̒ǉ�
	/// @tparam T �G�f�B�^�[�E�B���h�E�^
	/// @return ���������G�f�B�^�[�E�B���h�E
	template<class T, typename = std::enable_if_t<std::is_base_of_v<EditorWindow, T>>>
	T* AddEditorWindow()
	{
		static constexpr TypeHash typeHash = T::GetTypeHash();
		// ����
		auto itr = m_windowPool.find(typeHash);
		if (m_windowPool.end() != itr)
		{
			return static_cast<T*>(itr->second.get());
		}
		// �V�K����
		auto pWindow = std::make_unique<T>();
		auto* pResult = pWindow.get();
		pResult->m_pManager = this;
		// �i�[
		m_windowPool.emplace(typeHash, std::move(pWindow));

		return pResult;
	}

	/// @brief �G�f�B�^�[�E�B���h�E�̌���
	/// @tparam T �G�f�B�^�[�E�B���h�E�^
	/// @return ��v�����G�f�B�^�[�E�B���h�E
	template<class T, typename = std::enable_if_t<std::is_base_of_v<EditorWindow, T>>>
	T* GetEditorWindow()
	{
		static constexpr TypeHash typeHash = T::GetTypeHash();
		// ����
		auto itr = m_windowPool.find(typeHash);
		if (m_windowPool.end() != itr)
		{
			return static_cast<T*>(itr->second.get());
		}

		return nullptr;
	}

	/// @brief �R�A�G�f�B�^�[�̎擾
	/// @return �R�A�G�f�B�^�[�|�C���^
	core::CoreEditor* GetCoreEditor() { return m_pCoreEditor; }

private:

	/// @brief �R�A�G�f�B�^�[
	core::CoreEditor* m_pCoreEditor;

	/// @brief �^��ʂ̃G�f�B�^�[�E�B���h�E
	std::unordered_map<TypeHash, std::unique_ptr<EditorWindow>>	m_windowPool;

};


#endif // !_EDITOR_WINDOW_MANAGER_

