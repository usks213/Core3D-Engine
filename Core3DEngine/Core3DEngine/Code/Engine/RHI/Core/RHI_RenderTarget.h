/*****************************************************************//**
 * \file   RHI_RenderTarget.h
 * \brief  レンダーターゲット
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_RENDER_TARGET_
#define _CORE_RENDER_TARGET_

#include "RHI_Texture.h"

namespace Core::RHI
{
	/// @class RenderTarget
	/// @brief レンダーターゲット
	class RenderTarget :public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ(ファイル読み込み)
		/// @param id テクスチャID
		/// @param filepath ファイルパス
		explicit RenderTarget(const std::string& filepath) :
			Texture(filepath)
		{}

		/// @brief コンストラクタ(Descから生成)
		/// @param id テクスチャID
		/// @param desc テクスチャDesc
		explicit RenderTarget(TextureDesc& desc, const TextureData* pData = nullptr) :
			Texture(desc, pData)
		{}

		/// @brief デストラクタ
		virtual ~RenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_CORE_RENDER_TARGET_
