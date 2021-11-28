/*****************************************************************//**
 * \file   Object.h
 * \brief  オブジェクト
 * \detail インスペクターに表示可能
 * 
 * \author USAMI KOSHI
 * \date   2021/011/13
 *********************************************************************/
#ifndef _OBJECT_
#define _OBJECT_

#include "TypeHash.h"
#include "TypeID.h"

 /// @brief オブジェクトの情報を付加
#define DECLARE_OBJECT_INFO(T)									\
DECLARE_TYPE_INFO( T );											\
[[nodiscard]] TypeID GetTypeID() noexcept override {			\
	return static_cast<TypeID>(GetTypeHash());					\
}																\
[[nodiscard]] std::string_view GetTypeName() noexcept override {\
	return GetTypeString();										\
}																\
void _dumyFunction2() = delete



/// @brief オブジェクト
class Object
{
public:
	/// @brief コンストラクタ
	explicit Object() noexcept :
		m_instanceID(NONE_INSTANCE_ID)
	{
	}

	/// @brief コンストラクタ
	/// @param name 名前
	explicit Object(const InstanceID& id) noexcept :
		m_instanceID(id)
	{
	}

	/// @brief デストラクタ
	virtual ~Object() noexcept = default;

	/// @brief タイプID取得
	/// @return ID
	[[nodiscard]] virtual TypeID GetTypeID() noexcept = 0;

	/// @brief タイプ名取得
	/// @return 名前
	[[nodiscard]] virtual std::string_view GetTypeName() noexcept = 0;

	/// @brief インスタンスID取得
	/// @return ID
	[[nodiscard]] InstanceID GetInstanceID() noexcept { return m_instanceID; }

	/// @brief インスペクター表示
	virtual void OnInspectorGUI() = 0;
	
	///// @brief シリアライズ化
	//template<class T>
	//void serialize(T& archive)
	//{
	//	archive(CEREAL_NVP(m_instanceID), CEREAL_NVP(m_name));
	//}

protected:

	//--- serialize param

	/// @brief インスタンスID
	InstanceID		m_instanceID;

};

#endif // !_OBJECT_
