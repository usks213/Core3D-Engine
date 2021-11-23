/*****************************************************************//**
 * \file   Core_Editor.h
 * \brief  �R�A�G�f�B�^�[
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _CORE_EDITOR_
#define _CORE_EDITOR_

#include "Core/EditorWindowManager.h"

/// @brief �R�A�G�f�B�^�[�N���X
class CoreEditor final
{
public:

	explicit CoreEditor() noexcept
	{
	}

	~CoreEditor() noexcept = default;

private:

	std::unique_ptr<EditorWindowManager>	m_pEditorWindowManager;

};


#endif // !_CORE_EDITOR_
