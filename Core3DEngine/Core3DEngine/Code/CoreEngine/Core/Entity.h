/*****************************************************************//**
 * \file   Entity.h
 * \brief  �G���e�B�e�B
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "Object.h"

class EntityManager;

/// @brief �G���e�B�e�B
class Entity final : public Object
{
	friend class EntityManager;
public:
	/// @brief �I�u�W�F�N�g���
	DECLARE_OBJECT_INFO(Entity);

	/// @brief �R���X�g���N�^
	/// @param id �G���e�B�e�BID
	/// @param entity �G���e�B�e�B
	explicit Entity(const InstanceID& id, std::string_view name) :
		Object(id, name)
	{
	}

	/// @brief �f�X�g���N�^
	~Entity() = default;


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
