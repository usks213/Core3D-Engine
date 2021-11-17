/*****************************************************************//**
 * \file   TransformManager.h
 * \brief  トランスフォームマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/17
 *********************************************************************/
#ifndef _TRANSFORM_MANAGER_
#define _TRANSFORM_MANAGER_

#include "Object.h"
#include <vector>

class Transform;

class TransformManager
{
public:
	TransformManager();
	~TransformManager();

	Transform* RegisterRoot(const InstanceID& instanceID);

	void RemoveRoot(const InstanceID& instanceID);

private:

	/// @brief ルートトランスフォームリスト
	std::vector<InstanceID> m_rootTransforms;


};


#endif // !_TRANSFORM_MANAGER_

