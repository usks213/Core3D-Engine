/*****************************************************************//**
 * \file   TransformSystem.h
 * \brief  トランスフォームシステム
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "TransformSystm.h"

#include "../Core/SystemManager.h"
#include "../Core/Scene.h"

using namespace Core;

 /// @brief コンストラクタ
 /// @param pSystemManafer システムマネージャー
TransformSystem::TransformSystem(SystemManager* pSystemManafer) :
	System(pSystemManafer)
{

}


/// @brief 更新
void TransformSystem::OnUpdate()
{
	GetSystemManager()->GetScene()->GetTransformManager()->UpdateAllMatrix(true);
}

/// @brief ギズモ表示
void TransformSystem::OnGizmo()
{

}

