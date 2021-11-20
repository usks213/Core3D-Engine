/*****************************************************************//**
 * \file   Entity.h
 * \brief  エンティティ
 *
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#include "Entity.h"

#include "EntityManager.h"
#include "TransformManager.h"


 /// @brief トランスフォームの取得
 /// @return トランスフォームポインタ
Transform* Entity::transform() noexcept
{
	TransformManager* pTransformManager = m_pEntityManager->GetTransformManager();
	return pTransformManager->FindTransform(m_transformID);
}

/// @brief コンポーネントマネージャー取得
/// @return コンポーネントマネージャーポインタ
ComponentManager* Entity::GetComponentManager() noexcept
{
	return m_pEntityManager->GetComponentManager();
}
