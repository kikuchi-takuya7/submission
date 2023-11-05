#pragma once
#include "Engine/GameObject.h"

class StoreScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StoreScene(GameObject* parent);
	~StoreScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hPict_;
};;

