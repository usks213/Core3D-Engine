/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  �q�G�����L�[�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "HierarchyWindow.h"


 /// @brief �R���X�g���N�^
HierarchyWindow::HierarchyWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("�q�G�����L�[");
	SetWindowOpen(true);
	SetWindowFlags(
		WindowFlags::ImGuiWindowFlags_HorizontalScrollbar
	);
}

/// @brief GUI�\���R�[���o�b�N
void HierarchyWindow::OnGUI()
{
	// ���݃V�[���̎擾

}
