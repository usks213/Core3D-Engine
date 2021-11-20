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
#include <unordered_map>

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

	Transform* CreateTransform(const EntityID& entityID, bool bActive, bool bStatic, 
		const TransformID& parentID = NONE_TRANSFORM_ID);

	void DestroyTransform(const TransformID& transformID);

	Transform* FindTransform(const TransformID& transformID);

	void CreateRelation(const TransformID& transformID, const TransformID& parentID);

	void DestroyRelation(const TransformID& transformID, const TransformID& parentID);

	void SetParentTransform(Transform* pTransform, const TransformID& parentID);

	void AddChildTransform(Transform* pTransform, const TransformID& childID);

	void RemoveChildTransform(Transform* pTransform, const TransformID& childID);

private:

	void RegisterRoot(const TransformID& transformID);

	void RemoveRoot(const TransformID& transformID);

	/// @brief �J�n�ʒu����e�̊֌W��T�����A��v�����l��Ԃ�
	/// @param pBegin �J�n�ʒu
	/// @param pFind �����Ώ�
	/// @return ��v�����l or nullptr
	Transform* FindParentRelation(Transform* pBegin, Transform* pFind);

private:
	/// @brief vectorIndex
	using Index = std::size_t;

	/// @brief �����V�[��
	Scene* m_pScene;

	/// @brief ���[�g�g�����X�t�H�[�����X�g
	std::vector<TransformID>				m_rootTransforms;
	/// @brief ���[�g�g�����X�t�H�[�������e�[�u��
	std::unordered_map<TransformID, Index>	m_rootTransformTable;

};


#endif // !_TRANSFORM_MANAGER_

