/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  �G���e�B�e�B�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _ENTITY_MANAGER_
#define _ENTITY_MANAGER_

#include "Object.h"
#include <memory>
#include <unordered_map>

class Entity;

class EntityManager final
{
public:

	/// @brief �R���X�g���N�^
	explicit EntityManager() noexcept : 
		m_entityPool()
	{
	}

	/// @brief �f�X�g���N�^
	~EntityManager() noexcept = default;

	/// @brief �G���e�B�e�B�̐���
	/// @param name �G���e�B�e�B��
	/// @param bActive �A�N�e�B�u�w��
	/// @param bStatic �ÓI�w��
	/// @return �G���e�B�e�B�|�C���^
	Entity* CreateEntity(std::string_view name, bool bActive = true, bool bStatic = false);

	/// @brief �G���e�B�e�B�̍폜
	/// @param instanceID �C���X�^���XID
	void DestroyEntity(const InstanceID& instanceID);

private:
	/// @brief �G���e�B�e�B�v�[��
	std::unordered_map<InstanceID, std::unique_ptr<Entity>> m_entityPool;



};


#endif // !_ENTITY_MANAGER_

