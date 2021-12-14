/*****************************************************************//**
 * \file   RHI_GraphicsShader.h
 * \brief  グラフィックスシェーダー
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_GRAPHICS_SHADER_
#define _RHI_GRAPHICS_SHADER_

#include <limits>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <array>

#include "RHI_ShaderCBufferLayout.h"
#include "RHI_ShaderInputLayout.h"
#include "RHI_ShaderResourceLayout.h"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace Core::RHI
{
	/// @brief シェーダー生成用構造体
	struct GraphicsShaderDesc
	{
		std::uint32_t	m_stages;	// シェーダーステージフラグ
		std::string		m_name;		// シェーダー名
		// シェーダマクロ
	};

	/// @class GraphicsShader
	/// @brief シェーダ
	class GraphicsShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit GraphicsShader(GraphicsShaderDesc shaderDesc) :
			m_desc(shaderDesc)
		{
		}

		/// @brief デストラクタ
		virtual ~GraphicsShader() noexcept = default;


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		/// @brief シェーダー生成情報
		GraphicsShaderDesc  m_desc;
		/// @brief シェーダーマクロのハッシュ値


		/// @brief インプットレイアウト
		ShaderInputLayout								m_inputLayout;
		/// @brief リソーステーブル
		ShaderResourceLayout							m_resourceLayout[static_cast<std::size_t>(GraphicsShaderStage::MAX)];
		/// @brief CBufferレイアウト
		std::unordered_map<Slot, ShaderCBufferLayout>	m_cbufferLayout[static_cast<std::size_t>(GraphicsShaderStage::MAX)];

	};
}

#endif // !_RHI_GRAPHICS_SHADER_
