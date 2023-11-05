#pragma once
#include "Engine/GameObject.h"


class SplashScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SplashScene(GameObject* parent);
	~SplashScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Imgui_Window() override;
	
	
private:

	int hsos_logo_; //sosロゴ画像番号
	int hdenshi_logo_; //東北電子ロゴ画像番号

	Transform sos_Trans_; //sosロゴ画像のTransform
	Transform Denshi_Trams_; //東北電子ロゴのTransform

	HANDLE hFile_;        //ファイルのハンドル
	int alpha_;
	bool alphaFlag_;
	bool countDown_;
	float limitTmp_;//一年生が決める何秒とどまるかってやつ
	int limit_;//フレームに変換する
	int time_;
	
};


