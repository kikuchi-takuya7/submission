#pragma once
#include "Engine/GameObject.h"

class StoreScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StoreScene(GameObject* parent);
	~StoreScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hPict_;
};;

