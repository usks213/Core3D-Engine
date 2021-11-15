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

 /// @brief インスタンスID
enum class InstanceID : std::uint32_t;
/// @brief タイプID
enum class TypeID : std::uint32_t {};

/// @brief 最大インスタンスID
constexpr InstanceID MAX_INSTANCE_ID = std::numeric_limits<InstanceID>::max();
/// @brief 最大タイプID
constexpr TypeID MAX_TYPE_ID = std::numeric_limits<TypeID>::max();


 /// @brief オブジェクトの情報を付加
#define DECLARE_OBJECT_INFO(T)									\
DECLARE_TYPE_INFO( T );											\
[[nodiscard]] TypeID GetTypeID() override {						\
	return static_cast<TypeID>(GetTypeHash());					\
}																\
[[nodiscard]] std::string_view GetTypeName() override {			\
	return GetTypeString();										\
}																\
void _dumyFunction2() = delete



/// @brief オブジェクト
class Object
{
public:
	/// @brief コンストラクタ
	explicit Object() :
		m_instanceID(MAX_INSTANCE_ID), m_name("Object")
	{
	}

	/// @brief コンストラクタ
	/// @param name 名前
	explicit Object(std::string_view name) :
		m_instanceID(MAX_INSTANCE_ID), m_name(name)
	{
	}

	/// @brief デストラクタ
	~Object() = default;

	/// @brief タイプID取得
	/// @return ID
	[[nodiscard]] virtual TypeID GetTypeID() = 0;

	/// @brief タイプ名取得
	/// @return 名前
	[[nodiscard]] virtual std::string_view GetTypeName() = 0;

	/// @brief インスタンスID取得
	/// @return ID
	[[nodiscard]] InstanceID GetInstanceID() { return m_instanceID; }

	/// @brief 名前の取得
	/// @return 名前
	[[nodiscard]] std::string_view GetName() { return m_name; }

	///// @brief シリアライズ化
	//template<class T>
	//void serialize(T& archive)
	//{
	//	archive(CEREAL_NVP(m_instanceID), CEREAL_NVP(m_name));
	//}

protected:
	/// @brief インスタンスID
	InstanceID		m_instanceID;
	/// @brief 名前
	std::string		m_name;
};

#endif // !_OBJECT_
