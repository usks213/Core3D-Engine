/*****************************************************************//**
 * \file   System.h
 * \brief  システム
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _SYSTEM_
#define _SYSTEM_

#include "TypeHash.h"
#include "TypeID.h"
#include <memory>

class SystemManager;

 /// @brief システムの型情報付加
#define DECLARE_SYSTEM_INFO(T)											\
DECLARE_TYPE_INFO( T );													\
[[nodiscard]] SystemID GetSystemID() override {							\
	return static_cast<SystemID>(GetTypeHash());						\
}																		\
[[nodiscard]] std::string_view GetSystemName() override {				\
	return GetTypeString();												\
}																		\
static std::unique_ptr<System> Create(SystemManager* pSystemManager) {	\
	return std::move(std::make_unique<T>(pSystemManager));				\
}																		\
void _dumyFunction2() = delete


/// @brief システムクラス
class System
{
public:
	/// @brief コンストラクタ
	/// @param pSystemManager システムマネージャー
	explicit System(SystemManager* pSystemManager) :
		m_pSystemManager(pSystemManager)
	{
	}

	/// @brief デストラクタ
	virtual ~System() noexcept = default;

	/// @brief 更新
	virtual void OnUpdate() = 0;

	/// @brief ギズモ表示
	virtual void OnGizmo() {};

	/// @brief システムID取得
	/// @return システムID	
	[[nodiscard]] virtual SystemID GetSystemID() = 0;

	/// @brief システム名取得
	/// @return システム名
	[[nodiscard]] virtual std::string_view GetSystemName() = 0;

	/// @brief システムマネージャー取得
	/// @return システムマネージャーポインタ
	[[nodiscard]] SystemManager* GetSystemManager() { return m_pSystemManager; }

private:
	/// @brief システムマネージャー
	SystemManager* m_pSystemManager;
};

#endif // !_SYSTEM_

