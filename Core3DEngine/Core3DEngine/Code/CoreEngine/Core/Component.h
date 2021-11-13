/*****************************************************************//**
 * \file   Component.h
 * \brief  �R���|�[�l���g
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "Object.h"

class ComponentManager;

/// @brief �R���|�[�l���g
class Component final : public Object
{
	friend class ComponentManager;
public:
	/// @brief �I�u�W�F�N�g���
	DECLARE_OBJECT_INFO(Component);

	/// @brief �R���X�g���N�^
	/// @param id �R���|�[�l���gID
	/// @param entity �R���|�[�l���g
	explicit Component(const InstanceID& id, std::string_view name) :
		Object(id, name)
	{
	}

	/// @brief �f�X�g���N�^
	~Component() = default;


	///// @brief �V���A���C�Y��
	//template<class T>
	//void serialize(T& archive)
	//{
	//	Object::serialize(archive);
	//	archive(
	//		CEREAL_NVP(m_entity),
	//		CEREAL_NVP(m_parentID),
	//		CEREAL_NVP(m_childsID)
	//	);
	//}

protected:


private:

};

#endif // !_ENTITY_
