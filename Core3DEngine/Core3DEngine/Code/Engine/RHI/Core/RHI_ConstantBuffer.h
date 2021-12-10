/*****************************************************************//**
 * \file   RHI_ConstantBuffer.h
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
	class ConstantBuffer;

	/// @brief コンスタントバッファレイアウト
	class ConstantBufferLayout
	{
		friend class ConstantBuffer;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		ConstantBufferLayout() :
			m_name(), m_slot(0), m_size(0), m_variables() 
		{}

		/// @brief コンストラクタ
		/// @param slot スロット
		/// @param name 名前
		/// @param size サイズ
		ConstantBufferLayout(const std::uint32_t& slot, const std::string& name, const std::size_t& size) :
			m_slot(slot), m_name(name), m_size(size), m_variables() 
		{}

		/// @brief デストラクタ
		~ConstantBufferLayout() = default;

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

	/// @brief コンスタントバッファ
	class ConstantBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		ConstantBuffer() : 
			m_data(),m_layout(), m_isDitry(false)
		{}

		/// @brief コンストラクタ
		/// @param layout コンスタントバッファレイアウト
		explicit ConstantBuffer(const ConstantBufferLayout& layout);

		/// @brief デストラクタ
		~ConstantBuffer() = default;

		/// @brief uint設定
		bool SetUint(const char* name, const unsigned int& data) { return SetData(name, &data); }

		/// @brief VectorUint2設定
		bool SetVectorUint2(const char* name, const VectorUint2& data) { return SetData(name, &data); }

		/// @brief VectorUint3設定
		bool SetVectorUint3(const char* name, const VectorUint3& data) { return SetData(name, &data); }

		/// @brief VectorUint4設定
		bool SetVectorUint4(const char* name, const VectorUint4& data) { return SetData(name, &data); }

		/// @brief float設定
		bool SetFloat(const char* name, const float& data) { return SetData(name, &data); }

		/// @brief Vector2設定
		bool SetVector2(const char* name, const Vector2& data) { return SetData(name, &data); }

		/// @brief Vector3設定
		bool SetVector3(const char* name, const Vector3& data) { return SetData(name, &data); }

		/// @brief Vector4設定
		bool SetVector4(const char* name, const Vector4& data) { return SetData(name, &data); }

		/// @brief Matrix設定
		bool SetMatrix(const char* name, const Matrix& data) { return SetData(name, &data); }

		/// @brief Struct設定
		bool SetStruct(const char* name, const void* data) { return SetData(name, &data); }

		/// @brief データ取得
		template<class T>
		T GetData(const char* name)
		{
			auto itr = m_layout.m_variables.find(name);
			if (m_layout.m_variables.end() == itr) return T();

			return *(T*)(m_data.data() + itr->second.offset);
		}

	protected:
		//------------------------------------------------------------------------------
		// protected methods
		//------------------------------------------------------------------------------

		/// @brief データ設定
		bool SetData(const char* name, const void* data);

	private:
		ConstantBufferLayout	m_layout;
		std::vector<std::byte>	m_data;
		bool					m_isDitry;
	};
}


#endif // !_RHI_CONSTANT_BUFFER_

