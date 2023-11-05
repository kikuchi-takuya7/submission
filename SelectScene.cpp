#include "SelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include  "resource.h"
#include <DirectXMath.h>

using namespace DirectX;

//�R���X�g���N�^
SelectScene::SelectScene(GameObject* parent)
	: GameObject(parent, "SelectScene"), hPict_(-1), hVolume_(-1)
{
}

//�f�X�g���N�^
SelectScene::~SelectScene()
{
}

//������
void SelectScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("haikei.png");
	assert(hPict_ >= 0);

	//volume�̉摜�f�[�^�̃��[�h
	hVolume_ = Image::Load("Volume.png");
	assert(hVolume_ >= 0);

	volume_Transform_.position_.y = 0.1f;

	play_ = Instantiate<Button>(this);
	play_->SetImage("Play");
	play_->SetPosition(100, 500);//�E�B���h�E�̉���1280,�c720
	play_->SetNextScene(MAIN);
	play_->SetIsFlash(false);

	store_ = Instantiate<Button>(this);
	store_->SetImage("Store");
	store_->SetPosition(1100, 230);
	store_->SetNextScene(STORE);
	store_->SetIsFlash(false);

	exit_ = Instantiate<Button>(this);
	exit_->SetImage("Exit");
	exit_->SetPosition(100, 350);
	//exit_->SetLog(false);
}

//�X�V
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);

	XMFLOAT3 pos = Input::GetMousePosition();
	if (play_->MouseInArea(pos)) {
		play_->Push(true);
		return;
	}
	else {
		play_->Push(false);

	}

	if (store_->MouseInArea(pos)) {
		store_->Push(true);
		return;
	}
	else {
		store_->Push(false);
	}

	if (exit_->MouseInArea(pos)) {
		exit_->Push(true);
		Dlog_ = true;
		return;
	}
	else {
		exit_->Push(false);
		Dlog_ = false;
	}
}

//�`��
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Image::SetTransform(hVolume_, volume_Transform_);
	Image::Draw(hVolume_);
}

//�J��
void SelectScene::Release()
{
}

bool SelectScene::GetDlog() const
{
	return Dlog_;
}

BOOL SelectScene::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//�{�^���̏����l
		SendMessage(GetDlgItem(hDlg, IDC_YES), BM_SETCHECK, BST_CHECKED, 0);
		
		return 0;
	case WM_COMMAND:
		return 0;
	}
	return 0;
}
