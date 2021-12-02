/*****************************************************************//**
 * \file   TransformSystem.h
 * \brief  トランスフォームシステム
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _TRANSFORM_SYSTEM_
#define _TRANSFORM_SYSTEM_

#include "../Core/System.h"

namespace Core
{
	class TransformSystem final : public System
	{
	public:
		DECLARE_SYSTEM_INFO(TransformSystem);
	public:
		/// @brief コンストラクタ
		/// @param pSystemManafer システムマネージャー
		explicit TransformSystem(SystemManager* pSystemManafer);

		/// @brief デストラクタ
		~TransformSystem() noexcept = default;

		/// @brief 更新
		void OnUpdate() override;

		/// @brief ギズモ表示
		void OnGizmo() override;

	private:

	};
}

#endif // !_TRANSFORM_SYSTEM_



