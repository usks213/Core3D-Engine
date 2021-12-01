/*****************************************************************//**
 * \file   InspectorWindow.h
 * \brief  �C���X�y�N�^�[�E�B���h�E
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
	/// @brief �R���X�g���N�^
	explicit InspectorWindow() noexcept;

	/// @brief �f�X�g���N�^
	~InspectorWindow() noexcept = default;

	/// @brief GUI�\���R�[���o�b�N
	void OnGUI() final override;

private:

};

#endif // !_INSPECTOR_WINDOW_


