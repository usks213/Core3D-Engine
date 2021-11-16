/*****************************************************************//**
 * \file   Component.h
 * \brief  �R���|�[�l���g
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _COMPONENT_
#define _COMPONENT_

#include "Object.h"

class Entity;
class Transform;
class EntityManager;
class ComponentManager;

/// @brief �R���|�[�l���g
class Component : public Object
{
	friend class Entity;
	friend class ComponentManager;
public:

	/// @brief �R���X�g���N�^
	explicit Component() noexcept :
		Object("Component"), 
		m_pEntityManager(nullptr),
		m_parentID(MAX_INSTANCE_ID),
		m_isActive(true)
	{
	}

	/// @brief �R���X�g���N�^
	/// @param name �R���|�[�l���g��
	explicit Component(std::string_view name) noexcept :
		Object(name), 
		m_pEntityManager(nullptr),
		m_parentID(MAX_INSTANCE_ID),
		m_isActive(true)
	{
	}

	/// @brief �f�X�g���N�^
	virtual ~Component() noexcept = default;


	/// @brief �e�G���e�B�e�B�̎擾
	/// @return �G���e�B�e�B�|�C���^
	Entity* GetParent() noexcept;

	/// @brief �g�����X�t�H�[���̎擾
	/// @return �g�����X�t�H�[���|�C���^
	Transform* GetTransform() noexcept;

	/// @brief �A�N�e�B�u�w��
	/// @param isActive �t���O
	void SetActive(bool isActive) noexcept;

protected:
	//--- manager
	EntityManager* m_pEntityManager;

	//--- param

	/// @brief �e�̃G���e�B�e�BID
	InstanceID	m_parentID;
	/// @brief �A�N�e�B�u�t���O
	bool		m_isActive;

};

#endif // !_COMPONENT_
