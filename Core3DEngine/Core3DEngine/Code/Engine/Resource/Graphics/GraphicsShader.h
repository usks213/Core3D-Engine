/*****************************************************************//**
 * \file   GraphicsShader.h
 * \brief  グラフィックスシェーダー
 * 
 * \author USAMI KOSHI
 * \date   2021/12/16
 *********************************************************************/
#ifndef _GRAPHICS_SHADER_
#define _GRAPHICS_SHADER_

#include <Resource\Core\Resource.h>
#include <RHI\Core\RHI_GraphicsShader.h>

namespace Core
{
	/// @brief グラフィックスシェーダー
	class GraphicsShader : public Resource
	{
		DECLARE_RESOURCE_INFO(GraphicsShader);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		GraphicsShader() :
			m_pRHIGraphicsShader(nullptr)
		{
		}

		/// @brief デストラクタ
		~GraphicsShader() noexcept = default;

		/// @brief RHIグラフィックスシェーダーの取得
		/// @return RHIグラフィックスシェーダーのスマートポインタ
		std::shared_ptr<RHI::GraphicsShader> GetRHIGraphicsShader()
		{
			return m_pRHIGraphicsShader;
		}

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		std::shared_ptr<RHI::GraphicsShader> m_pRHIGraphicsShader;	///< RHIグラフィックスシェーダー

	};
}

#endif // !_GRAPHICS_SHADER_
