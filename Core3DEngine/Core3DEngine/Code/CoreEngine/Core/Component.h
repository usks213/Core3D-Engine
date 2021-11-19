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
		m_pComponentManager(nullptr),
		m_entityID(NONE_ENTITY_ID),
		m_isActive(true)
	{
	}

	/// @brief �R���X�g���N�^
	explicit Component(std::string_view name) noexcept :
		Object(name),
		m_pComponentManager(nullptr),
		m_entityID(NONE_ENTITY_ID),
		m_isActive(true)
	{
	}

	/// @brief �f�X�g���N�^
	virtual ~Component() noexcept = default;


	/// @brief �e�G���e�B�e�B�̎擾
	/// @return �G���e�B�e�B�|�C���^
	Entity* entity() noexcept;

	/// @brief �g�����X�t�H�[���̎擾
	/// @return �g�����X�t�H�[���|�C���^
	Transform* transform() noexcept;

	/// @brief �A�N�e�B�u�w��
	/// @param isActive �t���O
	void SetActive(bool isActive) noexcept;

public:
	//--- �R�[���o�b�N�֐�

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;

	virtual void OnStart() = 0;	///< ����X�V�O�Ɉ�x

protected:
	//--- none serialize param

	ComponentManager* m_pComponentManager;

	//--- serialize param

	/// @brief �e�̃G���e�B�e�BID
	EntityID	m_entityID;
	/// @brief �A�N�e�B�u�t���O
	bool		m_isActive;

};

#endif // !_COMPONENT_
