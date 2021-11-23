/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  �q�G�����L�[�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _HIERARCHY_WINDOW_
#define _HIERARCHY_WINDOW_

#include <CoreEditor/Core/EditorWindow.h>

class HierarchyWindow final : public EditorWindow
{
public:
	/// @brief �R���X�g���N�^
	explicit HierarchyWindow() noexcept;

	/// @brief �f�X�g���N�^
	~HierarchyWindow() noexcept = default;

	/// @brief GUI�\���R�[���o�b�N
	void OnGUI() final override;

private:

};


#endif // !_HIERARCHY_WINDOW_

