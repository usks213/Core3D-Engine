/*****************************************************************//**
 * \file   RenderingManager.h
 * \brief  �����_�����O�}�l�[�W���[�N���X
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
	/// @brief �����_�����O�}�l�[�W���[�N���X
	class RenderingManager
	{
	public:
		/// @brief �R���X�g���N�^
		/// @param pEngine �G���W���|�C���^
		explicit RenderingManager(Engine* pEngine) noexcept :
			m_pEngine(nullptr)
		{
		}

		/// @brief �f�X�g���N�^
		~RenderingManager() noexcept = default;

		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		Engine* GetEngine() const noexcept { return m_pEngine; }

	private:
		Engine* m_pEngine;	///< �G���W���|�C���^

	};
}

#endif // !_RENDERING_MANAGER_

