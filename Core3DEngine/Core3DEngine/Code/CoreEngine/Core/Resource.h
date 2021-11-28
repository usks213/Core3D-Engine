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

/// @brief ���\�[�X�N���X
class Resource : public Object
{
public:
	explicit Resource() noexcept :
		Object()
	{
	}

	explicit Resource(std::string_view name) noexcept :
		Object(), m_name(name)
	{
	}

	virtual ~Resource() noexcept = default;


	virtual void OnInspectorGUI() = 0;

	virtual void OnProjectGUI() = 0;

private:

	std::string		m_name;	///< ���\�[�X��

};


#endif // !_RESOURCE_
