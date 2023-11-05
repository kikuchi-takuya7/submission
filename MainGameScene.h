#pragma once
#include "Engine/GameObject.h"

class MainGameScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MainGameScene(GameObject* parent);
	~MainGameScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hPict_;
};