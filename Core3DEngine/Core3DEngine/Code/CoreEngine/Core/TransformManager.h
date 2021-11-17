/*****************************************************************//**
 * \file   TransformManager.h
 * \brief  �g�����X�t�H�[���}�l�[�W���[
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

	/// @brief ���[�g�g�����X�t�H�[�����X�g
	std::vector<InstanceID> m_rootTransforms;


};


#endif // !_TRANSFORM_MANAGER_

