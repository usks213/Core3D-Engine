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

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	Entity* CreateEntity(std::string_view name, bool bActive = true, bool bStatic = false);

	void DestroyEntity(const InstanceID& instanceID);

private:
	/// @brief �G���e�B�e�B�v�[��
	std::unordered_map<InstanceID, std::unique_ptr<Entity>> m_entityPool;


};


#endif // !_ENTITY_MANAGER_

