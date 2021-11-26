/*****************************************************************//**
 * \file   EngineWindow.h
 * \brief  エンジンウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#ifndef _ENGINE_WINDOW_
#define _ENGINE_WINDOW_

#include <CoreEditor/Core/EditorWindow.h>

class EngineWindow final : public EditorWindow
{
	DECLARE_TYPE_INFO(EngineWindow);
public:
	/// @brief コンストラクタ
	explicit EngineWindow() noexcept;

	/// @brief デストラクタ
	~EngineWindow() noexcept = default;

	/// @brief GUI表示コールバック
	void OnGUI() final override;

private:

};

#endif // !_ENGINE_WINDOW_

