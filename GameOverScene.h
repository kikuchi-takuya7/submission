#pragma once
#include "Engine/GameObject.h"
#include "Engine/Button.h"

class GameOverScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameOverScene(GameObject* parent);
	~GameOverScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	Transform hk;
	Transform ht;

	int hPict_;    //�摜�ԍ�

	Button* backmenu_;
};