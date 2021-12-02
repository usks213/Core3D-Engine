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
#include <limits>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace Core
{
	/// @brief 基底のID(サイズ)
	using BaseID = std::uint32_t;
	/// @brief 未定義BaseID
	constexpr BaseID NONE_BASE_ID = std::numeric_limits<BaseID>::max();

#define NONE_TYPE_ID(Type) static_cast<Type>(NONE_BASE_ID)

	/// @brief インスタンスID
	enum class InstanceID : BaseID {};
	/// @brief 未定義インスタンスID
	constexpr InstanceID NONE_INSTANCE_ID = NONE_TYPE_ID(InstanceID);

	/// @brief タイプID
	enum class TypeID : BaseID {};
	/// @brief 未定義タイプID
	constexpr TypeID NONE_TYPE_ID = NONE_TYPE_ID(TypeID);

	/// @brief スクリプトタイプID
	enum class ScriptTypeID : BaseID {};
	/// @brief 未定義スクリプトタイプID
	constexpr ScriptTypeID NONE_SCRIPT_ID = NONE_TYPE_ID(ScriptTypeID);

	/// @brief エンティティID
	enum class EntityID : BaseID {};
	/// @brief 未定義エンティティID
	constexpr EntityID NONE_ENTITY_ID = NONE_TYPE_ID(EntityID);

	/// @brief コンポーネントID
	enum class ComponentID : BaseID {};
	/// @brief 未定義コンポーネントID
	constexpr ComponentID NONE_COMPONENT_ID = NONE_TYPE_ID(ComponentID);

	/// @brief トランスフォームID
	enum class TransformID : BaseID {};
	/// @brief 未定義トランスフォームID
	constexpr TransformID NONE_TRANSFORM_ID = NONE_TYPE_ID(TransformID);

	/// @brief システムID
	enum class SystemID : BaseID {};
	/// @brief 未定義システムID
	constexpr SystemID NONE_SYSTEM_ID = NONE_TYPE_ID(SystemID);

	/// @brief パイプラインID
	enum class PipelineID : BaseID {};
	/// @brief 未定義パイプラインID
	constexpr PipelineID NONE_PIPELINE_ID = NONE_TYPE_ID(PipelineID);

	/// @brief リソースID
	enum class ResourceID : BaseID {};
	/// @brief 未定義リソースID
	constexpr ResourceID NONE_RESOURCE_ID = NONE_TYPE_ID(ResourceID);
}

#endif // !_TYPE_ID_

