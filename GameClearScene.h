#pragma once
#include "Engine/GameObject.h"

class GameClearScene : public GameObject
{
	int hPict_;    //�摜�ԍ�

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameClearScene(GameObject* parent);
	~GameClearScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};