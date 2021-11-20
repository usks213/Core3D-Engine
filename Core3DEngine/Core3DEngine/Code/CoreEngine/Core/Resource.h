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

// リソースID スマートID
class ResourceID;

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

	virtual void DispAssets() = 0;

private:

	std::string		m_name;	///< リソース名

};


#endif // !_RESOURCE_
