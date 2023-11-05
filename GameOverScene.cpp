#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include  "resource.h"
#include <DirectXMath.h>

//コンストラクタ
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1)
{
}

//デストラクタ
GameOverScene::~GameOverScene()
{
}

//初期化
void GameOverScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("game_over_scene.png");
	assert(hPict_ >= 0);
	hk.scale_ = XMFLOAT3(1.3f, 1.5f, 1.0f);

	backmenu_ = Instantiate<Button>(this);
	backmenu_->SetImage("go_backmenu");
	backmenu_->SetPosition(1655, 680);//ウィンドウの横幅1280,縦720
	backmenu_->SetScale(1.3f, 1.5f, 1.0f);
}

//更新
void GameOverScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//描画
void GameOverScene::Draw()
{
	Image::SetTransform(hPict_, hk);
	Image::Draw(hPict_);
}

//開放
void GameOverScene::Release()
{
}