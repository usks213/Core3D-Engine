/*****************************************************************//**
 * \file   RHI_Shader.h
 * \brief  シェーダー
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_SHADER_
#define _CORE_SHADER_

#include <limits>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <array>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace Core::RHI
{
	/// @brief シェーダー生成用構造体
	struct ShaderDesc
	{
		std::uint32_t	m_stages;	// シェーダーステージフラグ
		std::string		m_name;		// シェーダー名
		// シェーダマクロ
	};

	/// @class Shader
	/// @brief シェーダ
	class Shader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit Shader(ShaderDesc shaderDesc) :
			m_desc(shaderDesc)
		{
		}

		/// @brief デストラクタ
		virtual ~Shader() noexcept = default;

	public:


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief シェーダー生成情報
		ShaderDesc  m_desc;
		/// @brief マクロのハッシュ値

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------


	};
}

#endif // !_CORE_SHADER_
