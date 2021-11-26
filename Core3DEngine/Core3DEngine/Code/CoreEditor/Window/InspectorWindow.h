/*****************************************************************//**
 * \file   InspectorWindow.h
 * \brief  インスペクターウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/25
 *********************************************************************/
#ifndef _INSPECTOR_WINDOW_
#define _INSPECTOR_WINDOW_

#include <CoreEditor/Core/EditorWindow.h>

class InspectorWindow final : public EditorWindow
{
	DECLARE_TYPE_INFO(InspectorWindow);
public:
	/// @brief コンストラクタ
	explicit InspectorWindow() noexcept;

	/// @brief デストラクタ
	~InspectorWindow() noexcept = default;

	/// @brief GUI表示コールバック
	void OnGUI() final override;

private:

};

#endif // !_INSPECTOR_WINDOW_


