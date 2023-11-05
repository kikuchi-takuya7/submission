#pragma once
#include "Engine/GameObject.h"

class Option : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Option(GameObject* parent);
	~Option();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};