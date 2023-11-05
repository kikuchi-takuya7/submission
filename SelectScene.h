#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Button.h"

class SelectScene : public GameObject
{
private:
	int hPict_;    //画像番号
	Transform exit_Transform_;//Exitの位置を調整するための変数
	int hStore_;   //storeの画像番号
	Transform volume_Transform_;
	int hVolume_;   //volumeの画像番号
	bool Dlog_;

	Button* play_;
	Button* store_;
	Button* exit_;
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SelectScene(GameObject* parent);
	~SelectScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	bool GetDlog() const;
	BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};
