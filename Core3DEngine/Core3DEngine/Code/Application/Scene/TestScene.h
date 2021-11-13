/*****************************************************************//**
 * \file   TestScene.h
 * \brief  テストシーン
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _TEST_SCENE_
#define _TEST_SCENE_

#include <CoreEngine/Scene/Core_Scene.h>

class TestScene :public core::CoreScene
{
public:
	//------------------------------------------------------------------------------
	// public methods
	//------------------------------------------------------------------------------

	/// @brief コンストラクタ
	/// @param pSceneManager シーンマネージャー
	explicit TestScene(core::CoreSceneManager* pSceneManager) :
		core::CoreScene(pSceneManager)
	{
	}
	/// @brief デストラクタ
	virtual ~TestScene() noexcept = default;


	/// @brief スタート
	void Start() override;

	/// @brief システムの更新
	void Update() override;

	/// @brief パイプラインの描画
	void Render() override;

	/// @brief エンド
	void End() override;

private:

};


#endif // !_TEST_SCENE_
