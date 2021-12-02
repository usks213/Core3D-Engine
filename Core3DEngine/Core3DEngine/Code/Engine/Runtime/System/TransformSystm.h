/*****************************************************************//**
 * \file   TransformSystem.h
 * \brief  �g�����X�t�H�[���V�X�e��
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _TRANSFORM_SYSTEM_
#define _TRANSFORM_SYSTEM_

#include "../Core/System.h"

namespace Core
{
	class TransformSystem final : public System
	{
	public:
		DECLARE_SYSTEM_INFO(TransformSystem);
	public:
		/// @brief �R���X�g���N�^
		/// @param pSystemManafer �V�X�e���}�l�[�W���[
		explicit TransformSystem(SystemManager* pSystemManafer);

		/// @brief �f�X�g���N�^
		~TransformSystem() noexcept = default;

		/// @brief �X�V
		void OnUpdate() override;

		/// @brief �M�Y���\��
		void OnGizmo() override;

	private:

	};
}

#endif // !_TRANSFORM_SYSTEM_



