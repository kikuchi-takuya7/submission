#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

const LPCSTR fileName = "SaveFile\\SplashSaveData";

//コンストラクタ
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), hdenshi_logo_(-1), hsos_logo_(-1), alpha_(0), alphaFlag_(false), countDown_(false), limitTmp_(2.0), limit_(0), time_(0)
{
}

//デストラクタ
SplashScene::~SplashScene()
{
}

//初期化
void SplashScene::Initialize()
{

	hFile_ = CreateFile(
		fileName,                 //ファイル名
		GENERIC_READ,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		OPEN_ALWAYS,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);

	//ファイルのサイズを取得
	DWORD fileSize = GetFileSize(hFile_, NULL);

	//ファイルのサイズ分メモリを確保
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置

	ReadFile(
		hFile_,     //ファイルハンドル
		data,      //データを入れる変数
		fileSize,  //読み込むサイズ
		&dwBytes,  //読み込んだサイズ
		NULL);     //オーバーラップド構造体（今回は使わない）


	char* tmp = new char[fileSize];
	int c = 0, sw = 0;

	//新しくロードするデータを増やしたい場合はcaseを一つ増やしてその変数にtmpの内容をstofなりで入れればいい
	for (DWORD i = 0; i < fileSize; i++) {

		if (data[i] == ' ') {
			switch (sw)
			{
			case 0:
				sos_Trans_.position_.x = std::stof(tmp);
				break;
			case 1:
				sos_Trans_.position_.y = std::stof(tmp);
				break;
			case 2:
				sos_Trans_.position_.z = std::stof(tmp);
				break;
			case 3:
				sos_Trans_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				sos_Trans_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				sos_Trans_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				sos_Trans_.scale_.x = std::stof(tmp);
				sos_Trans_.scale_.y = std::stof(tmp);
				sos_Trans_.scale_.z = std::stof(tmp);
				break;
				//東北電子ロゴ用のロードするコードを描く。上に書いたように書けば行けるはず
			case 7:
				Denshi_Trams_.position_.x = std::stof(tmp);
				break;
			case 8:
				Denshi_Trams_.position_.y = std::stof(tmp);
				break;
			case 9:
				Denshi_Trams_.position_.z = std::stof(tmp);
				break;
			case 10:
				Denshi_Trams_.rotate_.x = std::stof(tmp);
				break;
			case 11:
				Denshi_Trams_.rotate_.y = std::stof(tmp);
				break;
			case 12:
				Denshi_Trams_.rotate_.z = std::stof(tmp);
				break;
			case 13:
				Denshi_Trams_.scale_.x = std::stof(tmp);
				Denshi_Trams_.scale_.y = std::stof(tmp);
				Denshi_Trams_.scale_.z = std::stof(tmp);
				break;
			case 14:
				alpha_ = std::stoi(tmp);
				break;
			case 15:
				limitTmp_ = std::stof(tmp);
				break;
			default:
				break;
			}
			sw++;
			c = 0;
			continue;
		}
		tmp[c] = data[i];
		c++;
	}
	delete[] tmp;
	delete[] data;

	CloseHandle(hFile_);

	//クラス変数に宣言 
	//Transform rogTransform_;

	//Setting_Transform(rogTransform_, );//-0.413,0,0,0,1.0f,255
	
	//sos画像データのロード
	hsos_logo_ = Image::Load("sos_logo.png");
	assert(hsos_logo_ >= 0);
	//東北電子画像データのロード
	hdenshi_logo_ = Image::Load("Tohokudenshi_logo.png");
	assert(hdenshi_logo_ >= 0);

	limit_ = limitTmp_ * 60 + 1;//時間をフレームに

	Leave();
}

//更新
void SplashScene::Update()
{
	//一年生がいじりやすいようにしたけど実際にゲームプレイするときはここはコメントアウトしないとだめ
	if(!IsEntered())
		return;

	if (alphaFlag_ == false) {
		alpha_ += 3;
	}
	else {
		time_++;
	}

	if (alpha_ >= 255) {
		alpha_ = 255;
		alphaFlag_ = true;
	}

	if (time_ >= limit_)
		alpha_ -= 3;


	if (alpha_ < 0) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	Image::SetAlpha(hsos_logo_, alpha_);
	Image::SetAlpha(hdenshi_logo_, alpha_);


}

//描画
void SplashScene::Draw()
{
	Image::SetTransform(hsos_logo_, sos_Trans_);
	Image::Draw(hsos_logo_);

	Image::SetTransform(hdenshi_logo_, Denshi_Trams_);//東北電子ロゴ用のTransform変数に変える
	Image::Draw(hdenshi_logo_);

	

	
}

//開放
void SplashScene::Release()
{
}

void SplashScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Splash"))
	{

		Setting_Transform(sos_Trans_, -1.0f, 1.0f, 365.0f, 5.0f, "SOS");
		//ここに東北電子ロゴ用のSetting_Transformを描く
		Setting_Transform(Denshi_Trams_, -1.0f, 1.0f, 365.0f, 5.0f, "DENSHI");

		ImGui::SliderInt("Startalpha", &alpha_, 0, 255);

		ImGui::SliderFloat("StaySecond", &limitTmp_, 0, 5);

		if (ImGui::Button("Start")) {
			//Initialize();
			Enter();
		}
			
			//updateStop_ = false;
	}
	ImGui::End();


	if (Input::IsKey(DIK_S) && Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_S) && Input::IsKey(DIK_RSHIFT) ) {

		//Save_Transform_File(hFile_, fileName);
		
		hFile_ = CreateFile(
			fileName,                 //ファイル名
			GENERIC_WRITE,           //アクセスモード（書き込み用）
			0,                      //共有（なし）
			NULL,                   //セキュリティ属性（継承しない）
			CREATE_ALWAYS,           //作成方法
			FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
			NULL);                  //拡張属性（なし

		float tmp = alpha_;

		//新しく変数をセーブしたい場合はここの後ろに変数を＆を付けて入れるだけ。ロードも忘れずに
		//sosロゴ用のセーブは書いたから、同じように東北電子用のロゴのセーブもする。ロードの順番と同じになるように注意
		float* save[] = { &sos_Trans_.position_.x, &sos_Trans_.position_.y, &sos_Trans_.position_.z,
						  &sos_Trans_.rotate_.x, &sos_Trans_.rotate_.y, &sos_Trans_.rotate_.z,
						  &sos_Trans_.scale_.x ,
						  &Denshi_Trams_.position_.x,& Denshi_Trams_.position_.y,& Denshi_Trams_.position_.z,
						  &Denshi_Trams_.rotate_.x,& Denshi_Trams_.rotate_.y,& Denshi_Trams_.rotate_.z,
						  &Denshi_Trams_.scale_.x, &tmp, &limitTmp_};

		const int size = sizeof(save) / sizeof(save[0]);
		
		std::string s[size];
		

		for (int i = 0; i < size; i++) {
			s[i] = std::to_string(*save[i]) + " ";
		}

		
		DWORD dwBytes = 0;  //書き込み位置

		for (int i = 0; i < size; i++) {

			WriteFile(
				hFile_,                   //ファイルハンドル
				s[i].c_str(),                  //保存するデータ（文字列）
				(DWORD)strlen(s[i].c_str()),   //書き込む文字数
				&dwBytes,                //書き込んだサイズを入れる変数
				NULL);                   //オーバーラップド構造体（今回は使わない）

		}

		

		CloseHandle(hFile_);

	}

}
