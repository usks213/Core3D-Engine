/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォーム
 *
 * \author USAMI KOSHI
 * \date   2021/011/17
 *********************************************************************/
#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "Component.h"
#include <Utils\Util_Mathf.h>
#include <vector>

 /// @brief ルートトランスフォームID
constexpr InstanceID ROOT_TRANSFORM_ID = MAX_INSTANCE_ID;

class TransformManager;

/// @brief トランスフォームクラス
class Transform final : public Component
{
	friend class Entity;
	friend class TransformManager;
public:
	/// @brief オブジェクト情報
	DECLARE_OBJECT_INFO(Transform);
public:

	/// @brief コンストラクタ
	explicit Transform() noexcept :
		Component("Transform"),
		m_pTransformManager(nullptr),
		m_root(MAX_INSTANCE_ID),
		m_childs()
	{
	}

	/// @brief デストラクタ
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

	InstanceID				m_root;			  ///< ルートトランスフォームID
	std::vector<InstanceID>	m_childs;		  ///< 子ノードトランスフォームID

	Vector3					m_localPosition;  ///< 
	Quaternion				m_localRotation;  ///<
	Vector3					m_localScale;	  ///<
	Vector3					m_globalScale;	  ///<

	Matrix					m_localMatrix;	  ///<
	Matrix					m_globalMatrix;	  ///<
	Matrix					m_parentMatrix;	  ///<
};

#endif // !_TRANSFORM_

