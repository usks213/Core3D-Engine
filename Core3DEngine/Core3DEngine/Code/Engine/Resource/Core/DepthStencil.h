/*****************************************************************//**
 * \file   DepthStencil.h
 * \brief  デプスステンシル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_DEPTH_STENCIL_
#define _CORE_DEPTH_STENCIL_

#include "Texture.h"

namespace Core
{
	/// @brief 深度ステンシルID
	enum class DepthStencilID : std::uint32_t {};
	/// @brief 存在しない深度ステンシルID
	constexpr DepthStencilID NONE_DEPTH_STENCIL_ID = std::numeric_limits<DepthStencilID>::max();

	/// @class CoreDepthStencil
	/// @brief 深度ステンシル
	class CoreDepthStencil
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param id 深度ステンシルID
		/// @param texture テクスチャ
		explicit CoreDepthStencil(const DepthStencilID& id, CoreTexture& texture) :
			m_id(id), m_name(texture.m_desc.name), m_texID(texture.m_id)
		{
		}

		/// @brief デストラクタ
		virtual ~CoreDepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		DepthStencilID	m_id;		///< 深度ステンシルID
		std::string		m_name;		///< 名前
		TextureID		m_texID;	///< テクスチャID

	};
}

#endif // !_CORE_DEPTH_STENCIL_
