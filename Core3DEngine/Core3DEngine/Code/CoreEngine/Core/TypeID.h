/*****************************************************************//**
 * \file   TypeID.h
 * \brief  TypeID
 *
 * \author USAMI KOSHI
 * \date   2021/011/19
 *********************************************************************/
#ifndef _TYPE_ID_
#define _TYPE_ID_

#include <numeric>

/// @brief 基底のID(サイズ)
using BaseID = std::uint32_t;

/// @brief インスタンスID
enum class InstanceID : BaseID;
/// @brief 未定義インスタンスID
constexpr InstanceID NONE_INSTANCE_ID = std::numeric_limits<InstanceID>::max();

/// @brief タイプID
enum class TypeID : BaseID {};
/// @brief 未定義タイプID
constexpr TypeID NONE_TYPE_ID = std::numeric_limits<TypeID>::max();

/// @brief エンティティID
enum class EntityID : BaseID {};
/// @brief 未定義エンティティID
constexpr EntityID NONE_ENTITY_ID = std::numeric_limits<EntityID>::max();

/// @brief コンポーネントID
enum class ComponentID : BaseID {};
/// @brief 未定義コンポーネントID
constexpr ComponentID NONE_COMPONENT_ID = std::numeric_limits<ComponentID>::max();

/// @brief スクリプトID
enum class ScriptID : BaseID {};
/// @brief 未定義スクリプトID
constexpr ScriptID NONE_SCRIPT_ID = std::numeric_limits<ScriptID>::max();

/// @brief トランスフォームID
enum class TransformID : BaseID {};
/// @brief 未定義トランスフォームID
constexpr TransformID NONE_TRANSFORM_ID = std::numeric_limits<TransformID>::max();


#endif // !_TYPE_ID_

