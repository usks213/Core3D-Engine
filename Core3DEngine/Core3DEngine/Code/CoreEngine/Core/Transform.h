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
		Component(),
		m_pTransformManager(nullptr),
		m_parent(NONE_TRANSFORM_ID),
		m_childs()
	{
	}

	/// @brief デストラクタ
	~Transform() noexcept = default;

	/// @brief 自身のトランスフォームIDを取得
	/// @return トランスフォームID
	TransformID GetTransformID() noexcept 
	{ 
		return static_cast<TransformID>(GetInstanceID()); 
	}

public:

	/// @brief 親のトランスフォーム指定
	/// @param parentID 親のトランスフォームID
	void SetParent(const TransformID& parentID);

	/// @brief 親のトランスフォーム取得
	/// @return トランスフォームポインタ
	Transform* GetParent();

	/// @brief 自身をルートに戻す
	void ReturnRoot();

	/// @brief 子のトランスフォームを追加
	/// @param childID 子のトランスフォームID
	void AddChild(const TransformID& childID);

	/// @brief 指定した子のトランスフォームを取得
	/// @param index インデックス
	/// @return トランスフォームポインタ
	Transform* GetChild(std::size_t index);

	/// @brief 子のトランスフォームを削除
	/// @param childID 子のトランスフォームID
	void RemoveChild(const TransformID& childID);

	/// @brief 子のリストを取得
	/// @return 子の配列
	std::vector<TransformID>& GetChildList() noexcept
	{
		return m_childs;
	}

	/// @brief 子の数を取得
	/// @return サイズ
	std::size_t GetChildCount() const noexcept
	{
		return m_childs.size();
	}

private:

	//--- none serialize param

	TransformManager*			m_pTransformManager;

	//--- serialize param

	TransformID					m_parent;		  ///< 親のトランスフォームID
	std::vector<TransformID>	m_childs;		  ///< 子のトランスフォームIDリスト

	Vector3						m_localPosition;  ///< 
	Quaternion					m_localRotation;  ///<
	Vector3						m_localScale;	  ///<
	Vector3						m_globalScale;	  ///<

	Matrix						m_localMatrix;	  ///<
	Matrix						m_globalMatrix;	  ///<
	Matrix						m_parentMatrix;	  ///<
};

#endif // !_TRANSFORM_

