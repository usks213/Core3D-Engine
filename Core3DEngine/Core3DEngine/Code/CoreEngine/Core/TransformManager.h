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

class Scene;
class Transform;

class TransformManager final
{
	friend class Transform;
public:

	/// @brief �R���X�g���N�^
	/// @param pScene �V�[���|�C���^
	explicit TransformManager(Scene* pScene) :
		m_pScene(pScene)
	{
	}

	/// @brief �f�X�g���N�^
	~TransformManager() noexcept = default;

	Transform* CreateTransform(const InstanceID& entityID);

	void DestroyTransform(const InstanceID& transformID);

	Transform* RegisterRoot(const InstanceID& transformID);

	void RemoveRoot(const InstanceID& transformID);

private:
	/// @brief �����V�[��
	Scene* m_pScene;

	/// @brief ���[�g�g�����X�t�H�[�����X�g
	std::vector<InstanceID> m_rootTransforms;

};


#endif // !_TRANSFORM_MANAGER_

