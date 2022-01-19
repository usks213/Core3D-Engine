/*****************************************************************//**
 * \file   RenderingManager.h
 * \brief  レンダリングマネージャークラス
 *
 * \author USAMI KOSHI
 * \date   2022/01/19
 *********************************************************************/
#ifndef _RENDERING_MANAGER_
#define _RENDERING_MANAGER_

namespace Core
{
	class Engine;

	/// @class RenderingManager
	/// @brief レンダリングマネージャークラス
	class RenderingManager
	{
	public:
		/// @brief コンストラクタ
		/// @param pEngine エンジンポインタ
		explicit RenderingManager(Engine* pEngine) noexcept :
			m_pEngine(nullptr)
		{
		}

		/// @brief デストラクタ
		~RenderingManager() noexcept = default;

		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		Engine* GetEngine() const noexcept { return m_pEngine; }

	private:
		Engine* m_pEngine;	///< エンジンポインタ

	};
}

#endif // !_RENDERING_MANAGER_

