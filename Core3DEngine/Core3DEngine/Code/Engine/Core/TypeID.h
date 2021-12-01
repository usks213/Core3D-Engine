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

/// @brief ����ID(�T�C�Y)
using BaseID = std::uint32_t;
/// @brief ����`BaseID
constexpr BaseID NONE_BASE_ID = std::numeric_limits<BaseID>::max();

#define NONE_TYPE_ID(Type) static_cast<Type>(NONE_BASE_ID)

/// @brief �C���X�^���XID
enum class InstanceID : BaseID {};
/// @brief ����`�C���X�^���XID
constexpr InstanceID NONE_INSTANCE_ID = NONE_TYPE_ID(InstanceID);

/// @brief �^�C�vID
enum class TypeID : BaseID {};
/// @brief ����`�^�C�vID
constexpr TypeID NONE_TYPE_ID = NONE_TYPE_ID(TypeID);

/// @brief �X�N���v�g�^�C�vID
enum class ScriptTypeID : BaseID {};
/// @brief ����`�X�N���v�g�^�C�vID
constexpr ScriptTypeID NONE_SCRIPT_ID = NONE_TYPE_ID(ScriptTypeID);

/// @brief �G���e�B�e�BID
enum class EntityID : BaseID {};
/// @brief ����`�G���e�B�e�BID
constexpr EntityID NONE_ENTITY_ID = NONE_TYPE_ID(EntityID);

/// @brief �R���|�[�l���gID
enum class ComponentID : BaseID {};
/// @brief ����`�R���|�[�l���gID
constexpr ComponentID NONE_COMPONENT_ID = NONE_TYPE_ID(ComponentID);

/// @brief �g�����X�t�H�[��ID
enum class TransformID : BaseID {};
/// @brief ����`�g�����X�t�H�[��ID
constexpr TransformID NONE_TRANSFORM_ID = NONE_TYPE_ID(TransformID);

/// @brief �V�X�e��ID
enum class SystemID : BaseID {};
/// @brief ����`�V�X�e��ID
constexpr SystemID NONE_SYSTEM_ID = NONE_TYPE_ID(SystemID);

/// @brief �p�C�v���C��ID
enum class PipelineID : BaseID {};
/// @brief ����`�p�C�v���C��ID
constexpr PipelineID NONE_PIPELINE_ID = NONE_TYPE_ID(PipelineID);

/// @brief ���\�[�XID
enum class ResourceID : BaseID {};
/// @brief ����`���\�[�XID
constexpr ResourceID NONE_RESOURCE_ID = NONE_TYPE_ID(ResourceID);


#endif // !_TYPE_ID_
