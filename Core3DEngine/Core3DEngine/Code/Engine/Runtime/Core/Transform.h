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

namespace Core
{
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
			m_isDirty(true),
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

		/// @brief インスペクター表示
		void OnInspectorGUI() override;

	public:

		/// @brief ローカル座標指定
		/// @param pos 座標
		void position(Vector3 pos);
		/// @brief ローカル回転指定
		/// @param rot クォータニオン
		void rotation(Quaternion rot);
		/// @brief ローカルスケール指定
		/// @param scale スケール
		void scale(Vector3 scale);
		/// @brief オイラー角指定
		/// @param euler オイラー角
		void euler(Vector3 euler);

		/// @brief ローカル座標取得
		/// @return ローカル座標
		const Vector3 position() const noexcept { return m_localPosition; }
		/// @brief ローカル回転取得
		/// @return ローカル回転
		const Quaternion rotation() const noexcept { return m_localRotation; }
		/// @brief ローカルスケール取得
		/// @return ローカルスケール
		const Vector3 scale() const noexcept { return m_localScale; }

		/// @brief オイラー角取得
		/// @return オイラー角
		const Vector3 euler();

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

		/// @brief ローカルマトリックス更新
		void UpdateLocalMatrix();

	private:

		//--- none serialize param

		TransformManager* m_pTransformManager;	///< トランスフォームマネージャー
		bool						m_isDirty;				///< 更新フラグ

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
}

#endif // !_TRANSFORM_

