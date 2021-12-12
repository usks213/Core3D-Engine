/*****************************************************************//**
 * \file   RHI_ShaderCBufferLayout.h
 * \brief  コンスタントバッファ
 *
 * \author USAMI KOSHI
 * \date   2021/12/04
 *********************************************************************/
#ifndef _RHI_CONSTANT_BUFFER_
#define _RHI_CONSTANT_BUFFER_

#include <vector>
#include <unordered_map>
#include <Utils\Util_Mathf.h>

namespace Core::RHI
{
	/// @brief コンスタントバッファレイアウト
	class ShaderCBufferLayout
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		ShaderCBufferLayout() :
			m_name(), m_slot(0), m_size(0), m_variables() 
		{}

		/// @brief コンストラクタ
		/// @param slot スロット
		/// @param name 名前
		/// @param size サイズ
		ShaderCBufferLayout(const std::uint32_t& slot, const std::string& name, const std::size_t& size) :
			m_slot(slot), m_name(name), m_size(size), m_variables() 
		{}

		/// @brief デストラクタ
		~ShaderCBufferLayout() = default;

	public:
		/// @brief CBufferの変数情報
		struct CBufferVariable
		{
			//std::string		name;			///< 変数名
			std::size_t		size	= 0;		///< 型サイズ
			std::size_t		offset	= 0;		///< 変数オフセット
			std::uint8_t	stage	= 0;		///< ステージ
			std::uint8_t	slot	= 0;		///< スロット
			std::vector<std::byte> defaultVal;	///< デフォルト値
		};

	private:
		//------------------------------------------------------------------------------
		// private variabes
		//------------------------------------------------------------------------------

		std::string						m_name;			///< cbuffer宣言名
		std::uint32_t					m_slot;			///< レジスタスロット
		std::size_t						m_size;			///< cbufferサイズ
		std::unordered_map<std::string, CBufferVariable>	m_variables;	///< 変数データ
	};

	///// @brief コンスタントバッファ
	//class ShaderCBufferLayout
	//{
	//public:
	//	//------------------------------------------------------------------------------
	//	// public methods
	//	//------------------------------------------------------------------------------

	//	/// @brief コンストラクタ
	//	ShaderCBufferLayout() : 
	//		m_data(),m_layout(), m_isDitry(false)
	//	{}

	//	/// @brief コンストラクタ
	//	/// @param layout コンスタントバッファレイアウト
	//	explicit ShaderCBufferLayout(const ShaderCBufferLayoutLayout& layout);

	//	/// @brief デストラクタ
	//	~ShaderCBufferLayout() = default;

	//	/// @brief データ取得
	//	template<class T>
	//	T GetData(const char* name)
	//	{
	//		auto itr = m_layout.m_variables.find(name);
	//		if (m_layout.m_variables.end() == itr) return T();

	//		return *(T*)(m_data.data() + itr->second.offset);
	//	}

	//	/// @brief データ設定
	//	bool SetData(const char* name, const void* data);

	//protected:
	//	//------------------------------------------------------------------------------
	//	// protected methods
	//	//------------------------------------------------------------------------------

	//private:
	//	ShaderCBufferLayoutLayout	m_layout;
	//	std::vector<std::byte>	m_data;
	//	bool					m_isDitry;
	//};
}


#endif // !_RHI_CONSTANT_BUFFER_

