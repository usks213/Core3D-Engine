/*****************************************************************//**
 * \file   Entity.h
 * \brief  �G���e�B�e�B
 *
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#include "Entity.h"

#include "EntityManager.h"
#include "TransformManager.h"


 /// @brief �g�����X�t�H�[���̎擾
 /// @return �g�����X�t�H�[���|�C���^
Transform* Entity::transform() noexcept
{
	TransformManager* pTransformManager = m_pEntityManager->GetTransformManager();
	return pTransformManager->FindTransform(m_transformID);
}

/// @brief �R���|�[�l���g�}�l�[�W���[�擾
/// @return �R���|�[�l���g�}�l�[�W���[�|�C���^
ComponentManager* Entity::GetComponentManager() noexcept
{
	return m_pEntityManager->GetComponentManager();
}
