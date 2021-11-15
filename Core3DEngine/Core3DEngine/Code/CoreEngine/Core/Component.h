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
	explicit Component() :
		Object("Component"), m_parentID(MAX_INSTANCE_ID)
	{
	}

	/// @brief �R���X�g���N�^
	/// @param name �R���|�[�l���g��
	explicit Component(std::string_view name) :
		Object(name), m_parentID(MAX_INSTANCE_ID)
	{
	}

	/// @brief �f�X�g���N�^
	virtual ~Component() = default;


	/// @brief �e�G���e�B�e�B�̎擾
	/// @return �G���e�B�e�B�|�C���^
	Entity* GetParent();

	/// @brief �g�����X�t�H�[���̎擾
	/// @return �g�����X�t�H�[���|�C���^
	Transform* GetTransform();



protected:

	/// @brief �e�̃G���e�B�e�BID
	InstanceID m_parentID;


};

#endif // !_COMPONENT_
