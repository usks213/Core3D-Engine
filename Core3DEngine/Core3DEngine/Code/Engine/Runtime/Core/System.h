/*****************************************************************//**
 * \file   System.h
 * \brief  �V�X�e��
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

 /// @brief �V�X�e���̌^���t��
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


/// @brief �V�X�e���N���X
class System
{
public:
	/// @brief �R���X�g���N�^
	/// @param pSystemManager �V�X�e���}�l�[�W���[
	explicit System(SystemManager* pSystemManager) :
		m_pSystemManager(pSystemManager)
	{
	}

	/// @brief �f�X�g���N�^
	virtual ~System() noexcept = default;

	/// @brief �X�V
	virtual void OnUpdate() = 0;

	/// @brief �M�Y���\��
	virtual void OnGizmo() {};

	/// @brief �V�X�e��ID�擾
	/// @return �V�X�e��ID	
	[[nodiscard]] virtual SystemID GetSystemID() = 0;

	/// @brief �V�X�e�����擾
	/// @return �V�X�e����
	[[nodiscard]] virtual std::string_view GetSystemName() = 0;

	/// @brief �V�X�e���}�l�[�W���[�擾
	/// @return �V�X�e���}�l�[�W���[�|�C���^
	[[nodiscard]] SystemManager* GetSystemManager() { return m_pSystemManager; }

private:
	/// @brief �V�X�e���}�l�[�W���[
	SystemManager* m_pSystemManager;
};

#endif // !_SYSTEM_

