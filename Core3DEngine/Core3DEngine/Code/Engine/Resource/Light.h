/*****************************************************************//**
 * \file   Light.h
 * \brief  ���C�g���
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_LIGHT_
#define _CORE_LIGHT_

#include <Utils/Util_Mathf.h>

namespace Core
{
	/// @brief �f�B���N�V���i�����C�g
	struct CoreDirectionalLight
	{
		Vector4 color = Vector4(1, 1, 1, 1);				///< �F+����
		Vector4 ambient = Vector4(0.1f, 0.1f, 0.1f, 1);		///< ����
		Vector4 direction = Vector4(1.0f, -1.0f, 1.0f, 1);	///< ����
	};

	/// @brief �|�C���^���C�g
	struct CorePointLight
	{
		Vector4 color = Vector4(1, 1, 1, 1);	///< �F+����
		Vector3 position;						///< �ʒu
		float	range = 1.0f;					///< �͈�
	};

	/// @brief �X�|�b�g���C�g
	struct CoreSpotLight
	{
		Vector4 color = Vector4(1, 1, 1, 1);	///< �F+����
		Vector3 position;						///< �ʒu
		float	range = 2.0f;					///< �͈�
		Vector3 direction = Vector3(0, -1, 0);;	///< ����
		float	spot = 0.5f;					///< �~���̑傫��(0.0f~1.0f)
	};
}

#endif // !_CORE_LIGHT_

