/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  �G���e�B�e�B�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/17
 *********************************************************************/

#include "EntityManager.h"

 /// @brief �G���e�B�e�B�̐���
 /// @param name �G���e�B�e�B��
 /// @param bActive �A�N�e�B�u�w��
 /// @param bStatic �ÓI�w��
 /// @return �G���e�B�e�B�|�C���^
Entity* CreateEntity(std::string_view name, bool bActive = true, bool bStatic = false);

/// @brief �G���e�B�e�B�̍폜
/// @param instanceID �C���X�^���XID
void DestroyEntity(const InstanceID& instanceID);