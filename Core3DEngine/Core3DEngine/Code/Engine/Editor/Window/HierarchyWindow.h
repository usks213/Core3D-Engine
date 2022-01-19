/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  ヒエラルキーウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _HIERARCHY_WINDOW_
#define _HIERARCHY_WINDOW_

#include <Editor/Core/EditorWindow.h>
#include <Core\Engine.h>

namespace Core
{
	class HierarchyWindow final : public EditorWindow
	{
		DECLARE_TYPE_INFO(HierarchyWindow);
	public:
		/// @brief コンストラクタ
		explicit HierarchyWindow() noexcept;

		/// @brief デストラクタ
		~HierarchyWindow() noexcept = default;

		/// @brief GUI表示コールバック
		void OnGUI() final override;

	private:

		void DispEntity(TransformManager* pTransformManager, const Transform::ID& parentID);

	};
}


#endif // !_HIERARCHY_WINDOW_

