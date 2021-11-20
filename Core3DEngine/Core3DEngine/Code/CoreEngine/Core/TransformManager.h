/*****************************************************************//**
 * \file   TransformManager.h
 * \brief  トランスフォームマネージャー
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

	/// @brief コンストラクタ
	/// @param pScene シーンポインタ
	explicit TransformManager(Scene* pScene) :
		m_pScene(pScene)
	{
	}

	/// @brief デストラクタ
	~TransformManager() noexcept = default;

	Transform* CreateTransform();

	void DestroyTransform(const TransformID& transformID);

	Transform* RegisterRoot(const TransformID& transformID);

	void RemoveRoot(const TransformID& transformID);

private:
	/// @brief 所属シーン
	Scene* m_pScene;

	/// @brief ルートトランスフォームリスト
	std::vector<InstanceID> m_rootTransforms;

};


#endif // !_TRANSFORM_MANAGER_

