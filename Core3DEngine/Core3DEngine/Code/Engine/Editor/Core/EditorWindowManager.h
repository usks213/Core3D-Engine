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
#include <CoreEngine\Core\TypeID.h>
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
	/// @brief �I�𒆂̃I�u�W�F�N�g
	struct SelectObject
	{
		enum class Type
		{
			Entity,
			Resource,
			MaxType,
		};
		InstanceID	instanceID = NONE_INSTANCE_ID;
		Type		objectType = Type::MaxType;
	};
public:
	/// @brief �R���X�g���N�^
	/// @param pCoreEditor �R�A�G�f�B�^�[�|�C���^
	explicit EditorWindowManager(core::CoreEditor* pCoreEditor) noexcept;

	/// @brief �f�X�g���N�^
	~EditorWindowManager() noexcept = default;

	/// @brief �E�B���h�E�̕\��
	void DispWindow();

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

	/// @brief ���ݑI�𒆂̃I�u�W�F�N�g���擾
	/// @return �I�𒆂̃I�u�W�F�N�g���
	SelectObject GetSelectObject() { return m_selectObject; }

	/// @brief �I���̃I�u�W�F�N�g�̎w��
	/// @param objectType �I�u�W�F�N�g�^�C�v
	/// @param instanceID �C���X�^���XID
	void SetSelectObject(SelectObject::Type objectType, const InstanceID& instanceID)
	{
		m_selectObject.objectType = objectType;
		m_selectObject.instanceID = instanceID;
	}



private:

	/// @brief ���j���[�o�[�̕\��
	void DispMenueBar();

	/// @brief �{�^���̕\��
	void DispButton();

private:

	/// @brief �R�A�G�f�B�^�[
	core::CoreEditor* m_pCoreEditor;

	/// @brief �^��ʂ̃G�f�B�^�[�E�B���h�E
	std::unordered_map<TypeHash, std::unique_ptr<EditorWindow>>	m_windowPool;

	//--- EditorParam

	/// @brief ���ݑI�𒆂̃I�u�W�F�N�g
	SelectObject	m_selectObject;

};


#endif // !_EDITOR_WINDOW_MANAGER_
