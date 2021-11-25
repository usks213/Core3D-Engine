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

#include "Entity.h"

class Scene;
class Entity;
class ComponentManager;
class TransformManager;

class EntityManager final
{
public:

	/// @brief �R���X�g���N�^
	explicit EntityManager(Scene* pScene) noexcept : 
		m_pScene(pScene) ,m_entityPool()
	{
	}

	/// @brief �f�X�g���N�^
	~EntityManager() noexcept = default;

	/// @brief �G���e�B�e�B�̐���
	/// @param name �G���e�B�e�B��
	/// @param bActive �A�N�e�B�u�w��
	/// @param bStatic �ÓI�w��
	/// @return �G���e�B�e�B�|�C���^
	Entity* CreateEntity(std::string_view name, bool bActive = true, 
		bool bStatic = false, const TransformID& parentID = NONE_TRANSFORM_ID);

	/// @brief �G���e�B�e�B�̍폜
	/// @param instanceID �C���X�^���XID
	void DestroyEntity(const EntityID& entityID);

	/// @brief �G���e�B�e�B�̌���
	/// @param entityID �G���e�B�e�BID
	/// @return ������ �G���e�B�e�B�|�C���^ / �Ȃ� nullptr
	Entity* FindEntity(const EntityID& entityID);

	/// @brief �R���|�[�l���g�}�l�[�W���[�擾
	/// @return �R���|�[�l���g�}�l�[�W���[
	ComponentManager* GetComponentManager();

	/// @brief �g�����X�t�H�[���}�l�[�W���[�擾
	/// @return �g�����X�t�H�[���}�l�[�W���[
	TransformManager* GetTransformManager();

private:
	/// @brief �����V�[��
	Scene* m_pScene;

	/// @brief �G���e�B�e�B�v�[��
	std::unordered_map<EntityID, std::unique_ptr<Entity>> m_entityPool;

};


#endif // !_ENTITY_MANAGER_

