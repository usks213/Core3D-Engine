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

/// @brief ����ID(�T�C�Y)
using BaseID = std::uint32_t;

/// @brief �C���X�^���XID
enum class InstanceID : BaseID;
/// @brief ����`�C���X�^���XID
constexpr InstanceID NONE_INSTANCE_ID = std::numeric_limits<InstanceID>::max();

/// @brief �^�C�vID
enum class TypeID : BaseID {};
/// @brief ����`�^�C�vID
constexpr TypeID NONE_TYPE_ID = std::numeric_limits<TypeID>::max();

/// @brief �G���e�B�e�BID
enum class EntityID : BaseID {};
/// @brief ����`�G���e�B�e�BID
constexpr EntityID NONE_ENTITY_ID = std::numeric_limits<EntityID>::max();

/// @brief �R���|�[�l���gID
enum class ComponentID : BaseID {};
/// @brief ����`�R���|�[�l���gID
constexpr ComponentID NONE_COMPONENT_ID = std::numeric_limits<ComponentID>::max();

/// @brief �X�N���v�gID
enum class ScriptID : BaseID {};
/// @brief ����`�X�N���v�gID
constexpr ScriptID NONE_SCRIPT_ID = std::numeric_limits<ScriptID>::max();

/// @brief �g�����X�t�H�[��ID
enum class TransformID : BaseID {};
/// @brief ����`�g�����X�t�H�[��ID
constexpr TransformID NONE_TRANSFORM_ID = std::numeric_limits<TransformID>::max();


#endif // !_TYPE_ID_

