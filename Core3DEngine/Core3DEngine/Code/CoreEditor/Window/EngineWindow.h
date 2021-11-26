/*****************************************************************//**
 * \file   EngineWindow.h
 * \brief  �G���W���E�B���h�E
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
	/// @brief �R���X�g���N�^
	explicit EngineWindow() noexcept;

	/// @brief �f�X�g���N�^
	~EngineWindow() noexcept = default;

	/// @brief GUI�\���R�[���o�b�N
	void OnGUI() final override;

private:

};

#endif // !_ENGINE_WINDOW_

