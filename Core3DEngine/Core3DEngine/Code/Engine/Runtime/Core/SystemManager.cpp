/*****************************************************************//**
 * \file   SystemManager.h
 * \brief  �V�X�e��
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "SystemManager.h"

 /// @brief �R���X�g���N�^
 /// @param pScene �V�[���|�C���^
SystemManager::SystemManager(Scene* pScene) :
	m_pScene(pScene)
{
}

/// @brief �V�X�e���X�V
void SystemManager::Update()
{
	for (auto& system : m_systemPool)
	{
		system.second->OnUpdate();
	}
}

/// @brief �M�Y���\��
void SystemManager::DispGizmo()
{
	for (auto& system : m_systemPool)
	{
		system.second->OnGizmo();
	}
}
