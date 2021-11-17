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

 /// @brief ���[�g�g�����X�t�H�[��ID
constexpr InstanceID ROOT_TRANSFORM_ID = MAX_INSTANCE_ID;

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
		Component("Transform"),
		m_pTransformManager(nullptr),
		m_root(MAX_INSTANCE_ID),
		m_childs()
	{
	}

	/// @brief �f�X�g���N�^
	~Transform() noexcept = default;

private:

	void SetParent(const InstanceID& parentID);
	Transform* GetParent();
	void ResetParent();

	void AddChild(const InstanceID& childID);
	Transform* GetChild(std::size_t index);
	void RemoveChild(const InstanceID& childID);

	std::vector<InstanceID>& GetChildList();
	std::size_t GetChildCount();

private:

	//--- none serialize param

	TransformManager*	m_pTransformManager;

	//--- serialize param

	InstanceID				m_root;			  ///< ���[�g�g�����X�t�H�[��ID
	std::vector<InstanceID>	m_childs;		  ///< �q�m�[�h�g�����X�t�H�[��ID

	Vector3					m_localPosition;  ///< 
	Quaternion				m_localRotation;  ///<
	Vector3					m_localScale;	  ///<
	Vector3					m_globalScale;	  ///<

	Matrix					m_localMatrix;	  ///<
	Matrix					m_globalMatrix;	  ///<
	Matrix					m_parentMatrix;	  ///<
};

#endif // !_TRANSFORM_

