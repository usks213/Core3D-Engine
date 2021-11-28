/*****************************************************************//**
 * \file   TransformManager.h
 * \brief  トランスフォームマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/17
 *********************************************************************/
#ifndef _TRANSFORM_MANAGER_
#define _TRANSFORM_MANAGER_

#include "Transform.h"
#include <unordered_map>

class Scene;

class TransformManager final
{
	friend class Transform;
public:

	/// @brief コンストラクタ
	/// @param pScene シーンポインタ
	explicit TransformManager(Scene* pScene) noexcept :
		m_pScene(pScene)
	{
	}

	/// @brief デストラクタ
	~TransformManager() noexcept = default;

	Transform* CreateTransform(const EntityID& entityID, bool bActive, bool bStatic, 
		const TransformID& parentID = NONE_TRANSFORM_ID);

	void DestroyTransform(const TransformID& transformID);

	Transform* FindTransform(const TransformID& transformID);

	void CreateRelation(const TransformID& transformID, const TransformID& parentID);

	void DestroyRelation(const TransformID& transformID, const TransformID& parentID);

	void UpdateAllMatrix(bool isStaticUpdate);

	void UpdateChildMatrix(Transform* pTransform, const Matrix& parentMatrix, const Vector3& parentScale, const bool isParentDirty = false);

	/// @brief ルートトランスフォームを取得
	std::vector<TransformID>& GetRootTransforms() { return m_rootTransforms; }

private:

	void RegisterRoot(const TransformID& transformID);

	void RemoveRoot(const TransformID& transformID);

	/// @brief 開始位置から親の関係を探索し、一致した値を返す
	/// @param pBegin 開始位置
	/// @param pFind 検索対象
	/// @return 一致した値 or nullptr
	Transform* FindParentRelation(Transform* pBegin, Transform* pFind);

private:
	/// @brief vectorIndex
	using Index = std::size_t;

	/// @brief 所属シーン
	Scene* m_pScene;

	/// @brief ルートトランスフォームリスト
	std::vector<TransformID>				m_rootTransforms;
	/// @brief ルートトランスフォーム検索テーブル
	std::unordered_map<TransformID, Index>	m_rootTransformTable;

};


#endif // !_TRANSFORM_MANAGER_

