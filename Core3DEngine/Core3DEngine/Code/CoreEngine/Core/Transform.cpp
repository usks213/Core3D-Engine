/*****************************************************************//**
 * \file   Transform.h
 * \brief  �g�����X�t�H�[��
 *
 * \author USAMI KOSHI
 * \date   2021/011/21
 *********************************************************************/
#include "Transform.h"

#include "TransformManager.h"


 /// @brief ���[�J�����W�w��
 /// @param pos ���W
void Transform::position(Vector3 pos)
{
	m_isDirty = true;
	m_localPosition = pos;
}

/// @brief ���[�J����]�w��
/// @param rot �N�H�[�^�j�I��
void Transform::rotation(Quaternion rot)
{
	m_isDirty = true;
	m_localRotation = rot;
}

/// @brief ���[�J���X�P�[���w��
/// @param scale �X�P�[��
void Transform::scale(Vector3 scale)
{
	m_isDirty = true;
	m_localScale = scale;
}

/// @brief �e�̃g�����X�t�H�[���w��
/// @param parentID �e�̃g�����X�t�H�[��ID
void Transform::SetParent(const TransformID& parentID)
{
	m_pTransformManager->CreateRelation(GetTransformID(), parentID);
}

/// @brief �e�̃g�����X�t�H�[���擾
/// @return �g�����X�t�H�[���|�C���^
Transform* Transform::GetParent()
{
	return m_pTransformManager->FindTransform(m_parent);
}

/// @brief ���g�����[�g�ɖ߂�
void Transform::ReturnRoot()
{
	m_pTransformManager->DestroyRelation(GetTransformID(), m_parent);
}

/// @brief �q�̃g�����X�t�H�[����ǉ�
/// @param childID �q�̃g�����X�t�H�[��ID
void Transform::AddChild(const TransformID& childID)
{
	m_pTransformManager->CreateRelation(childID, GetTransformID());
}

/// @brief �w�肵���q�̃g�����X�t�H�[�����擾
/// @param index �C���f�b�N�X
/// @return �g�����X�t�H�[���|�C���^
Transform* Transform::GetChild(std::size_t index)
{
	if (index < m_childs.size())
	{
		return m_pTransformManager->FindTransform(m_childs[index]);
	}
	return nullptr;
}

/// @brief �q�̃g�����X�t�H�[�����폜
/// @param childID �q�̃g�����X�t�H�[��ID
void Transform::RemoveChild(const TransformID& childID)
{
	m_pTransformManager->DestroyRelation(childID, GetTransformID());
}

/// @brief ���[�J���}�g���b�N�X�X�V
void Transform::UpdateLocalMatrix()
{
	m_isDirty = false;

	// ���[���h�}�g���b�N�X�X�V
	Matrix world = Matrix::CreateScale(m_localScale);
	world *= Matrix::CreateFromQuaternion(m_localRotation);
	world *= Matrix::CreateTranslation(m_localPosition);
	m_localMatrix = world;
}
