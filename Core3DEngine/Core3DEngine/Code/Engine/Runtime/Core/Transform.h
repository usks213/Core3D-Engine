/*****************************************************************//**
 * \file   Transform.h
 * \brief  �g�����X�t�H�[��
 *
 * \author USAMI KOSHI
 * \date   2021/011/17
 *********************************************************************/
#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "Component.h"
#include <Utils\Util_Mathf.h>
#include <vector>

class TransformManager;

/// @brief �g�����X�t�H�[���N���X
class Transform final : public Component
{
	friend class Entity;
	friend class TransformManager;
public:
	/// @brief �I�u�W�F�N�g���
	DECLARE_OBJECT_INFO(Transform);
public:

	/// @brief �R���X�g���N�^
	explicit Transform() noexcept :
		Component(),
		m_pTransformManager(nullptr),
		m_isDirty(true),
		m_parent(NONE_TRANSFORM_ID),
		m_childs()
	{
	}

	/// @brief �f�X�g���N�^
	~Transform() noexcept = default;

	/// @brief ���g�̃g�����X�t�H�[��ID���擾
	/// @return �g�����X�t�H�[��ID
	TransformID GetTransformID() noexcept 
	{ 
		return static_cast<TransformID>(GetInstanceID()); 
	}

	/// @brief �C���X�y�N�^�[�\��
	void OnInspectorGUI() override;

public:
	
	/// @brief ���[�J�����W�w��
	/// @param pos ���W
	void position(Vector3 pos);
	/// @brief ���[�J����]�w��
	/// @param rot �N�H�[�^�j�I��
	void rotation(Quaternion rot);
	/// @brief ���[�J���X�P�[���w��
	/// @param scale �X�P�[��
	void scale(Vector3 scale);
	/// @brief �I�C���[�p�w��
	/// @param euler �I�C���[�p
	void euler(Vector3 euler);

	/// @brief ���[�J�����W�擾
	/// @return ���[�J�����W
	const Vector3 position() const noexcept { return m_localPosition; }
	/// @brief ���[�J����]�擾
	/// @return ���[�J����]
	const Quaternion rotation() const noexcept { return m_localRotation; }
	/// @brief ���[�J���X�P�[���擾
	/// @return ���[�J���X�P�[��
	const Vector3 scale() const noexcept { return m_localScale; }

	/// @brief �I�C���[�p�擾
	/// @return �I�C���[�p
	const Vector3 euler();

public:

	/// @brief �e�̃g�����X�t�H�[���w��
	/// @param parentID �e�̃g�����X�t�H�[��ID
	void SetParent(const TransformID& parentID);

	/// @brief �e�̃g�����X�t�H�[���擾
	/// @return �g�����X�t�H�[���|�C���^
	Transform* GetParent();

	/// @brief ���g�����[�g�ɖ߂�
	void ReturnRoot();

	/// @brief �q�̃g�����X�t�H�[����ǉ�
	/// @param childID �q�̃g�����X�t�H�[��ID
	void AddChild(const TransformID& childID);

	/// @brief �w�肵���q�̃g�����X�t�H�[�����擾
	/// @param index �C���f�b�N�X
	/// @return �g�����X�t�H�[���|�C���^
	Transform* GetChild(std::size_t index);

	/// @brief �q�̃g�����X�t�H�[�����폜
	/// @param childID �q�̃g�����X�t�H�[��ID
	void RemoveChild(const TransformID& childID);

	/// @brief �q�̃��X�g���擾
	/// @return �q�̔z��
	std::vector<TransformID>& GetChildList() noexcept
	{
		return m_childs;
	}

	/// @brief �q�̐����擾
	/// @return �T�C�Y
	std::size_t GetChildCount() const noexcept
	{
		return m_childs.size();
	}

private:

	/// @brief ���[�J���}�g���b�N�X�X�V
	void UpdateLocalMatrix();

private:

	//--- none serialize param

	TransformManager*			m_pTransformManager;	///< �g�����X�t�H�[���}�l�[�W���[
	bool						m_isDirty;				///< �X�V�t���O

	//--- serialize param

	TransformID					m_parent;		  ///< �e�̃g�����X�t�H�[��ID
	std::vector<TransformID>	m_childs;		  ///< �q�̃g�����X�t�H�[��ID���X�g

	Vector3						m_localPosition;  ///< 
	Quaternion					m_localRotation;  ///<
	Vector3						m_localScale;	  ///<
	Vector3						m_globalScale;	  ///<

	Matrix						m_localMatrix;	  ///<
	Matrix						m_globalMatrix;	  ///<
	Matrix						m_parentMatrix;	  ///<
};

#endif // !_TRANSFORM_
