/*****************************************************************//**
 * \file   TransformSystem.h
 * \brief  �g�����X�t�H�[���V�X�e��
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "TransformSystm.h"

#include "../Core/SystemManager.h"
#include "../Core/Scene.h"

using namespace Core;

 /// @brief �R���X�g���N�^
 /// @param pSystemManafer �V�X�e���}�l�[�W���[
TransformSystem::TransformSystem(SystemManager* pSystemManafer) :
	System(pSystemManafer)
{

}


/// @brief �X�V
void TransformSystem::OnUpdate()
{
	GetSystemManager()->GetScene()->GetTransformManager()->UpdateAllMatrix(true);
}

/// @brief �M�Y���\��
void TransformSystem::OnGizmo()
{

}

