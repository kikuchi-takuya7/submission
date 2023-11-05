#include "MainGameScene.h"
#include "Player.h"
#include "StageMap.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//デストラクタ
MainGameScene::~MainGameScene()
{
}

//初期化
void MainGameScene::Initialize()
{
	Player* pPlayer = Instantiate<Player>(this);
	//StageMap* pStageMap = Instantiate<StageMap>(this);

}

//更新
void MainGameScene::Update()
{
	if(Input::IsMouseButtonDown(0)) //左クリック
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
	if(Input::IsMouseButtonDown(1)) //右クリック
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
	}
}

//描画
void MainGameScene::Draw()
{
}

//開放
void MainGameScene::Release()
{
}