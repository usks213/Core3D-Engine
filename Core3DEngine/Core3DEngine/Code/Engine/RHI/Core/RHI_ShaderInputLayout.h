/*****************************************************************//**
 * \file   RHI_ShaderInputLayout.h
 * \brief  シェーダーインプットレイアウト
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#ifndef _RHI_SHADER_INPUT_LAYOUT_
#define _RHI_SHADER_INPUT_LAYOUT_

#include <vector>
#include <string>

namespace Core::RHI
{
	class ShaderInputLayout
	{
	public:
		ShaderInputLayout();
		~ShaderInputLayout();

		/// @brief 入力レイアウト情報構造体
		struct InputLayoutVariable
		{
			std::string semanticName;		///< セマンティック名		例:TEXCOOD
			std::uint32_t semanticIndex;	///< セマンティック番号	例:TEXCOOD[0]←
			std::size_t offset;			///< 変数オフセット
			std::size_t arrayNum;			///< 配列の数 例:R32=1,R32B32=2,
			std::size_t formatWidth;		///< フォーマットの幅 例:r16=2,r32=4
			InputLayoutVariable() :
				semanticName(),
				semanticIndex(0),
				offset(0),
				arrayNum(0),
				formatWidth(0) {}
		};

		/// @brief 変数の追加
		/// @param var 入力レイアウトの変数
		void AddVariable(const InputLayoutVariable& var)
		{
			m_inputLayoutVariableList.push_back(var);
		}

		/// @brief 入力レイアウトの変数リストを取得
		/// @return 変数リスト
		std::vector<InputLayoutVariable>& GetVariableList() 
		{
			return m_inputLayoutVariableList; 
		}

	protected:

		/// @brief 入力レイアウト情報リスト
		std::vector<InputLayoutVariable> m_inputLayoutVariableList;

	};

}

#endif // !_RHI_SHADER_INPUT_LAYOUT_

