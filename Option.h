#pragma once
#include "Engine/GameObject.h"

class Option : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Option(GameObject* parent);
	~Option();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};