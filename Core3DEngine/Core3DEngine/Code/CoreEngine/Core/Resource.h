/*****************************************************************//**
 * \file   Resource.h
 * \brief  リソースオブジェクト
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _RESOURCE_
#define _RESOURCE_

#include "Object.h"

class Resource : public Object
{
public:
	explicit Resource(const InstanceID& id, std::string_view name) :
		Object(id, name)
	{
	}

	virtual ~Resource() = default;

private:

};


#endif // !_RESOURCE_
