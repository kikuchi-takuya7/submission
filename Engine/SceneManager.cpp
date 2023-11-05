#include "sceneManager.h"

#include "../SplashScene.h"
#include "../TitleScene.h"
#include "../SelectScene.h"
#include "../MainGameScene.h"
#include "../GameClearScene.h"
#include "../GameOverScene.h"
#include "../ResultScene.h"
#include "../DevelopSelectScene.h"
#include "../StoreScene.h"
#include "MapEditor/MapEditorScene.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"


//�R���X�g���N�^
SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_DEVELOP_SELECT;
	nextSceneID_ = currentSceneID_;
	Instantiate<DevelopSelectScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_SPLASH: Instantiate<SplashScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_SELECT: Instantiate<SelectScene>(this); break;
		case SCENE_ID_MAIN: Instantiate<MainGameScene>(this); break;
		case SCENE_ID_GAMECLEAR: Instantiate<GameClearScene>(this); break;
		case SCENE_ID_GAMEOVER: Instantiate<GameOverScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		case SCENE_ID_MAPEDITOR: Instantiate<MapEditorScene>(this); break;
		case SCENE_ID_DEVELOP_SELECT: Instantiate<DevelopSelectScene>(this); break;
		case SCENE_ID_STORE: Instantiate<StoreScene>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}