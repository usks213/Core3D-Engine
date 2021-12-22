/*****************************************************************//**
 * \file   RHI_GPUBuffer.h
 * \brief  バッファ
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
	/// @brief バッファ
	class GPUBuffer : public Resource
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param desc リソースDesc
		GPUBuffer(const ResourceDesc& desc) :
			Resource(desc)
		{
		}

		/// @brief デストラクタ
		virtual ~GPUBuffer() noexcept = default;

	};
}

#endif // !_RHI_GPU_BUFFER_
