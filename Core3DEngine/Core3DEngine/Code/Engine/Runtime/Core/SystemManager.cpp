/*****************************************************************//**
 * \file   SystemManager.h
 * \brief  システム
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "SystemManager.h"

 /// @brief コンストラクタ
 /// @param pScene シーンポインタ
SystemManager::SystemManager(Scene* pScene) :
	m_pScene(pScene)
{
}

/// @brief システム更新
void SystemManager::Update()
{
	for (auto& system : m_systemPool)
	{
		system.second->OnUpdate();
	}
}

/// @brief ギズモ表示
void SystemManager::DispGizmo()
{
	for (auto& system : m_systemPool)
	{
		system.second->OnGizmo();
	}
}
