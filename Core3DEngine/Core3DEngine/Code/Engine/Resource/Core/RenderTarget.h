/*****************************************************************//**
 * \file   RenderTarget.h
 * \brief  レンダーターゲット
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_RENDER_TARGET_
#define _CORE_RENDER_TARGET_

#include "Texture.h"

namespace Core
{
	/// @brief レンダーターゲットID
	enum class RenderTargetID : std::uint32_t {};
	/// @brief 存在しないレンダーターゲットID
	constexpr RenderTargetID NONE_RENDER_TARGET_ID = std::numeric_limits<RenderTargetID>::max();

	/// @class CoreRenderTarget
	/// @brief レンダーターゲット
	class CoreRenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param id レンダーターゲットID
		/// @param texture テクスチャ
		explicit CoreRenderTarget(const RenderTargetID& id, Core::CoreTexture& texture) :
			m_id(id), m_name(texture.m_desc.name), m_texID(texture.m_id)
		{
		}

		/// @brief デストラクタ
		virtual ~CoreRenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief レンダーターゲットID
		RenderTargetID	m_id;
		/// @brief 名前
		std::string		m_name;
		/// @brief テクスチャID
		TextureID		m_texID;

	};
}

#endif // !_CORE_RENDER_TARGET_
