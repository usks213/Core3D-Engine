/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  �q�G�����L�[�E�B���h�E
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
		/// @brief �R���X�g���N�^
		explicit HierarchyWindow() noexcept;

		/// @brief �f�X�g���N�^
		~HierarchyWindow() noexcept = default;

		/// @brief GUI�\���R�[���o�b�N
		void OnGUI() final override;

	private:

		void DispEntity(TransformManager* pTransformManager, const Transform::ID& parentID);

	};
}


#endif // !_HIERARCHY_WINDOW_

