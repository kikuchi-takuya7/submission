#pragma once
#include "Engine/GameObject.h"

class MainGameScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MainGameScene(GameObject* parent);
	~MainGameScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hPict_;
};