/*****************************************************************//**
 * \file   ComponentManager.h
 * \brief  コンポーネントマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _COMPONENT_MANAGER_
#define _COMPONENT_MANAGER_

#include "Component.h"

#include <memory>
#include <vector>
#include <unordered_map>

class Scene;

class ComponentManager final
{
public:
	/// @brief コンストラクタ
	/// @param pScene シーンポインタ
	explicit ComponentManager(Scene* pScene) noexcept :
		m_pScene(pScene)
	{
	}

	/// @brief デストラクタ
	~ComponentManager() noexcept = default;

	/// @brief コンポーネントの生成
	/// @tparam T コンポーネント型
	/// @param entityID 親のエンティティID
	/// @param isEnable 有効フラグ
	/// @return 生成したコンポーネント型ポインタ
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* CreateComponent(const EntityID& entityID, bool isEnable)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ID生成
		InstanceID id = NONE_INSTANCE_ID;
		// 生成
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		pResult->m_instanceID = id;
		pResult->m_entityID = entityID;
		pResult->m_isEnable = isEnable;
		// 格納
		m_componentLookupTable[typeID].emplace(pCom->GetComponentID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));
		// 生成時コールバック
		pCom->OnCreate();
		// 有効フラグ
		SetComponentEnable(pCom, isEnable);

		return pResult;
	}

	/// @brief コンポーネントを削除リストに登録
	/// @param typeID コンポーネントタイプID
	/// @param componentID コンポーネントID
	void DestroyComponent(const TypeID& typeID, const ComponentID& componentID);

	/// @brief コンポーネントの検索
	/// @param typeID コンポーネントタイプID
	/// @param componentID コンポーネントID
	/// @return コンポーネントポインタ or nullptr
	Component* FindComponent(const TypeID& typeID, const ComponentID& componentID);

	/// @brief コンポーネントの検索
	/// @tparam T コンポーネント型
	/// @param componentID コンポーネントID
	/// @return コンポーネント型ポインタ or nullptr
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* FindComponent(const ComponentID& componentID)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		return static_cast<T*>(FindComponent(typeID, componentID));
	}

	/// @brief コンポーネントの有効指定
	/// @param pComponent 対象のコンポーネントポインタ
	/// @param isEnable 有効フラグ
	void SetComponentEnable(Component* pComponent, bool isEnable);

	/// @brief 削除リストの実行
	void CleanupComponent();

	/// @brief コンポーネントのシリアライズ
	void Serialize();

	/// @brief コンポーネントのデシリアライズ
	void Deserialize();

private:

	Component* RegisterComponent(const TypeID& typeID, const ComponentID& componentID, Component* pComponent);

private:
	/// @brief vectorIndex
	using Index = std::size_t;

	/// @brief コンポーネント情報
	struct ComponentInfo
	{
		ComponentID	id;		///< コンポーネントID
		TypeID		type;	///< コンポーネント型ID
	};

	//--- serialize param

	/// @brief 型ごとのコンポーネントプール
	std::unordered_map<TypeID, std::vector<std::unique_ptr<Component>>>		m_componentPool;

	//--- none serialize param

	/// @brief 所属シーン
	Scene* m_pScene;

	/// @brief コンポーネントのルックアップテーブル
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_componentLookupTable;

	/// @brief 生成リスト
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_createList;
	/// @brief 削除リスト
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_destroyList;

	/// @brief 有効コンポーネントリスト
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_enableComponents;
	/// @brief 有効コンポーネントテーブル
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_enableComponentsTable;
	/// @brief 無効コンポーネントリスト
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_disableComponents;
	/// @brief 無効コンポーネントテーブル
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_disableComponentsTable;

};

#endif // !_COMPONENT_MANAGER_
