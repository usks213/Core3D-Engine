/*****************************************************************//**
 * \file   Texture.h
 * \brief  テクスチャ
 * 
 * \author USAMI KOSHI
 * \date   2021/12/16
 *********************************************************************/
#ifndef _TEXTURE_
#define _TEXTURE_

#include <Resource\Core\Resource.h>
#include <RHI\Core\RHI_Texture.h>

namespace Core
{
	/// @class Texture
	/// @brief テクスチャ
	class Texture : public Resource
	{
		DECLARE_RESOURCE_INFO(Texture);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		Texture() :
			m_pRHITexture(nullptr)
		{
		}

		/// @brief デストラクタ
		virtual ~Texture() noexcept = default;

		/// @brief RHIテクスチャの取得
		/// @return RHIテクスチャのスマートポインタ
		std::shared_ptr<RHI::Texture> GetRHITexture()
		{
			return m_pRHITexture;
		}

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		std::shared_ptr<RHI::Texture>	m_pRHITexture;	///< RHIテクスチャ


	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_TEXTURE_
