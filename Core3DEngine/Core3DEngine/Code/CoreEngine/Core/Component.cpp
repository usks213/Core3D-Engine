/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネント
 *
 * \author USAMI KOSHI
 * \date   2021/11/25
 *********************************************************************/
#include "Component.h"

#include "Scene.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "TransformManager.h"


 /// @brief 親エンティティの取得
 /// @return エンティティポインタ
Entity* Component::entity() noexcept
{
	return m_pComponentManager->GetScene()->GetEntityManager()->FindEntity(m_entityID);
}

/// @brief トランスフォームの取得
/// @return トランスフォームポインタ
Transform* Component::transform() noexcept
{
	auto* pEntity = entity();
	if (pEntity == nullptr) return nullptr;

	return m_pComponentManager->GetScene()->GetTransformManager()->FindTransform(pEntity->m_transformID);
}

/// @brief 使用フラグ指定
/// @param isEnable フラグ
void Component::SetEnable(bool isEnable) noexcept
{

}
