/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  エンティティマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/17
 *********************************************************************/

#include "EntityManager.h"

 /// @brief エンティティの生成
 /// @param name エンティティ名
 /// @param bActive アクティブ指定
 /// @param bStatic 静的指定
 /// @return エンティティポインタ
Entity* CreateEntity(std::string_view name, bool bActive = true, bool bStatic = false);

/// @brief エンティティの削除
/// @param instanceID インスタンスID
void DestroyEntity(const InstanceID& instanceID);