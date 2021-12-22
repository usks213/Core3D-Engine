/*****************************************************************//**
 * \file   RHI_GPUBuffer.h
 * \brief  �o�b�t�@
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_GPU_BUFFER_
#define _RHI_GPU_BUFFER_

#include "RHI_Resource.h"


namespace Core::RHI
{
	/// @class GPUBuffer
	/// @brief �o�b�t�@
	class GPUBuffer : public Resource
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param desc ���\�[�XDesc
		GPUBuffer(const ResourceDesc& desc) :
			Resource(desc)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~GPUBuffer() noexcept = default;

	};
}

#endif // !_RHI_GPU_BUFFER_
