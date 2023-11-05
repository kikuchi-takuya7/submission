#include "GameClearScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//コンストラクタ
GameClearScene::GameClearScene(GameObject* parent)
	: GameObject(parent, "GameClearScene"), hPict_(-1)
{
}

//デストラクタ
GameClearScene::~GameClearScene()
{
}

//初期化
void GameClearScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("ClearImage.jpg");
	assert(hPict_ >= 0);

	transform_.scale_ = XMFLOAT3(0.7f, 0.72f, 1.0f);
}

//更新
void GameClearScene::Update()
{
	//スペースキーが押されていたら
	if (Input::IsMouseButton(0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}


	
}

//描画
void GameClearScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GameClearScene::Release()
{
}