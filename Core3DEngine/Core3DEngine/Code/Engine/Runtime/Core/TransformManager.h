/*****************************************************************//**
 * \file   TransformManager.h
 * \brief  �g�����X�t�H�[���}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/17
 *********************************************************************/
#ifndef _TRANSFORM_MANAGER_
#define _TRANSFORM_MANAGER_

#include "Transform.h"
#include <unordered_map>

namespace Core
{
	class Scene;

	class TransformManager final
	{
		friend class Transform;
	public:

		/// @brief �R���X�g���N�^
		/// @param pScene �V�[���|�C���^
		explicit TransformManager(Scene* pScene) noexcept :
			m_pScene(pScene)
		{
		}

		/// @brief �f�X�g���N�^
		~TransformManager() noexcept = default;

		Transform* CreateTransform(const EntityID& entityID, bool bActive, bool bStatic,
			const Transform::ID& parentID = Transform::NONE_ID);

		void DestroyTransform(const Transform::ID& transformID);

		Transform* FindTransform(const Transform::ID& transformID);

		void CreateRelation(const Transform::ID& transformID, const Transform::ID& parentID);

		void DestroyRelation(const Transform::ID& transformID, const Transform::ID& parentID);

		void UpdateAllMatrix(bool isStaticUpdate);

		void UpdateChildMatrix(Transform* pTransform, const Matrix& parentMatrix, const Vector3& parentScale, const bool isParentDirty = false);

		/// @brief ���[�g�g�����X�t�H�[�����擾
		std::vector<Transform::ID>& GetRootTransforms() { return m_rootTransforms; }

	private:

		void RegisterRoot(const Transform::ID& transformID);

		void RemoveRoot(const Transform::ID& transformID);

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
		std::vector<Transform::ID>				m_rootTransforms;
		/// @brief ���[�g�g�����X�t�H�[�������e�[�u��
		std::unordered_map<Transform::ID, Index>	m_rootTransformTable;

	};
}

#endif // !_TRANSFORM_MANAGER_

