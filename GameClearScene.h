#pragma once
#include "Engine/GameObject.h"

class GameClearScene : public GameObject
{
	int hPict_;    //画像番号

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameClearScene(GameObject* parent);
	~GameClearScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};