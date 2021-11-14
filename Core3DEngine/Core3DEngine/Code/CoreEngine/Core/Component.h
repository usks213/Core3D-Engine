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
	friend class ComponentManager;
public:

	/// @brief �R���X�g���N�^
	/// @param id �R���|�[�l���gID
	/// @param entity �R���|�[�l���g
	explicit Component(const InstanceID& id, std::string_view name) :
		Object(id, name)
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
