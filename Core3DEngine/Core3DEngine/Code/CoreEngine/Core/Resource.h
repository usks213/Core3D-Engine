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

// ���\�[�XID �X�}�[�gID
class ResourceID;

class Resource : public Object
{
public:
	explicit Resource() noexcept :
		Object("Resource")
	{
	}

	explicit Resource(std::string_view name) noexcept :
		Object(name)
	{
	}

	virtual ~Resource() noexcept = default;

	virtual void DispAssets() = 0;

private:

};


#endif // !_RESOURCE_
