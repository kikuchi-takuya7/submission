#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include  "resource.h"
#include <DirectXMath.h>

//�R���X�g���N�^
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1)
{
}

//�f�X�g���N�^
GameOverScene::~GameOverScene()
{
}

//������
void GameOverScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("game_over_scene.png");
	assert(hPict_ >= 0);
	hk.scale_ = XMFLOAT3(1.3f, 1.5f, 1.0f);

	backmenu_ = Instantiate<Button>(this);
	backmenu_->SetImage("go_backmenu");
	backmenu_->SetPosition(1655, 680);//�E�B���h�E�̉���1280,�c720
	backmenu_->SetScale(1.3f, 1.5f, 1.0f);
}

//�X�V
void GameOverScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//�`��
void GameOverScene::Draw()
{
	Image::SetTransform(hPict_, hk);
	Image::Draw(hPict_);
}

//�J��
void GameOverScene::Release()
{
}