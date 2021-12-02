/*****************************************************************//**
 * \file   EditorWindow.h
 * \brief  エディターウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _EDITOR_WINDOW_
#define _EDITOR_WINDOW_

#include <Core/TypeHash.h>
#include <ImGui/imgui.h>

namespace Core
{

	class EditorWindowManager;

	/// @brief エディターウィンドウ
	class EditorWindow
	{
	public:
		friend class EditorWindowManager;
		using WindowFlags = ImGuiWindowFlags;	///< ImGuiウィンドウフラグ
		using WindowFlag = ImGuiWindowFlags_;	///< ImGuiウィンドウフラグ
	public:

		/// @brief コンストラクタ
		explicit EditorWindow() noexcept;

		/// @brief デストラクタ
		virtual ~EditorWindow() noexcept = default;

		/// @brief ウィンドウの表示
		void DispWindow();

		/// @brief GUI表示コールバック
		virtual void OnGUI() = 0;


		//----- ゲッター・セッター -----

		/// @brief エディターウィンドウマネージャーの取得
		/// @return エディターウィンドウマネージャーのポインタ
		EditorWindowManager* GetEditorWindowManager() const noexcept
		{
			return m_pManager;
		}

		/// @brief ウィンドウの表示指定
		/// @param isDisp 表示フラグ
		void SetWindowDisp(bool isDisp) noexcept { m_isDisp = isDisp; }
		/// @brief ウィンドウの表示フラグの取得
		/// @return 表示フラグ
		bool GetWinodwDisp() const noexcept { return m_isDisp; }

		/// @brief ウィンドウ名の指定
		/// @param name ウィンドウ名
		void SetWindowName(std::string_view name) noexcept { m_name = name; }
		/// @brief ウィンドウ名の取得
		/// @return ウィンドウ名
		std::string_view GetWindowName() const noexcept { return m_name; }

		/// @brief ウィンドウ開閉指定
		/// @param isOpne 開閉フラグ
		void SetWindowOpen(bool isOpne) noexcept { m_isOpne = isOpne; }
		/// @brief ウィンドウ開閉フラグの取得
		/// @return 開閉フラグ
		bool GetWindowOpen() const noexcept { return m_isOpne; }

		/// @brief ウィンドウフラグの取得
		/// @param flags ウィンドウフラグ
		void SetWindowFlags(WindowFlags flags) noexcept { m_flags = flags; }
		/// @brief ウィンドウフラグの取得
		/// @return ウィンドウフラグ
		WindowFlags GetWindowFlags() const noexcept { return m_flags; }

	private:
		EditorWindowManager* m_pManager;

		bool			m_isDisp;		///< 表示フラグ

		std::string		m_name;			///< ウィンドウ名
		bool			m_isOpne;		///< 開閉フラグ
		WindowFlags		m_flags;		///< ウィンドウフラグ

		ImVec2			m_size;			///< ウィンドウのサイズ
		ImVec2			m_pos;			///< ウィンドウの座標
	};
}

#endif // !_EDITOR_WINDOW_

