/*****************************************************************//**
 * \file   RHI_ConstantBuffer.h
 * \brief  コンスタントバッファ
 *
 * \author USAMI KOSHI
 * \date   2021/12/04
 *********************************************************************/

#include "RHI_ConstantBuffer.h"

using namespace Core::RHI;

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief コンストラクタ
/// @param layout コンスタントバッファレイアウト
ConstantBuffer::ConstantBuffer(const ConstantBufferLayout& layout) :
	m_data(layout.m_size), m_layout(layout), m_isDitry(true)
{
	// 変数データ格納
	for (const auto& var : m_layout.m_variables)
	{
		// 初期化子データがある場合は初期化する
		if (var.second.defaultVal.size() > 0)
		{
			std::memcpy(m_data.data() + var.second.offset,
				var.second.defaultVal.data(), var.second.size);	// 怪しい…
		}
		else
		{
			std::memset(m_data.data() + var.second.offset, 0, var.second.size);
		}
	}
}


//------------------------------------------------------------------------------
// protected methods
//------------------------------------------------------------------------------

/// @brief データ設定
bool ConstantBuffer::SetData(const char* name, const void* data)
{
	auto itr = m_layout.m_variables.find(name);
	if (m_layout.m_variables.end() == itr) return false;

	std::memcpy(m_data.data() + itr->second.offset, data, itr->second.size);
	m_isDitry = true;

	return true;
}
