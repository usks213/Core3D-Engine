/*****************************************************************//**
 * \file   RHI_DepthStencil.h
 * \brief  デプスステンシル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_DEPTH_STENCIL_
#define _CORE_DEPTH_STENCIL_

#include "RHI_Texture.h"

namespace Core::RHI
{
	/// @class DepthStencil
	/// @brief 深度ステンシル
	class DepthStencil : public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ(ファイル読み込み)
		/// @param id テクスチャID
		/// @param filepath ファイルパス
		explicit DepthStencil(const std::string& filepath) :
			Texture(filepath)
		{}

		/// @brief コンストラクタ(Descから生成)
		/// @param id テクスチャID
		/// @param desc テクスチャDesc
		explicit DepthStencil(TextureDesc& desc, const TextureData* pData = nullptr) : 
			Texture(desc, pData)
		{}

		/// @brief デストラクタ
		virtual ~DepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_CORE_DEPTH_STENCIL_
