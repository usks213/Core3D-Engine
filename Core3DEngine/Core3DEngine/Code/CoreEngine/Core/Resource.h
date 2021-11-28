/*****************************************************************//**
 * \file   Resource.h
 * \brief  ���\�[�X�I�u�W�F�N�g
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _RESOURCE_
#define _RESOURCE_

#include "Object.h"

 /// @brief �^���t��
#define DECLARE_RESOURCE_INFO(T)	\
DECLARE_OBJECT_INFO(T);				\
using T##ID = ResourceID

class ResourceManager;


/// @brief ���\�[�X�N���X
class Resource : public Object
{
public:
	/// @brief �R���X�g���N�^
	/// @return 
	explicit Resource() noexcept :
		Object(),
		m_pResourceManager(nullptr)
	{
	}

	/// @brief �f�X�g���N�^
	/// @return 
	virtual ~Resource() noexcept = default;


	/// @brief �C���X�y�N�^�[�\��
	virtual void OnInspectorGUI() = 0;

private:
	//--- none serialize param

	ResourceManager* m_pResourceManager;

	//--- serialize param

	std::string		m_name;	///< ���\�[�X��

};


#endif // !_RESOURCE_
