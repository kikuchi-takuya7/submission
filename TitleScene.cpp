#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


const LPCSTR fileName = "SaveFile\\TitleSaveData";

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hhaikei_(-1), hTitle_(-1)
{
}

//デストラクタ
TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
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
				start_Transform_.position_.x = std::stof(tmp);
				break;
			case 1:
				start_Transform_.position_.y = std::stof(tmp);
				break;
			case 2:
				start_Transform_.position_.z = std::stof(tmp);
				break;
			case 3:
				start_Transform_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				start_Transform_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				start_Transform_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				start_Transform_.scale_.x = std::stof(tmp);
				start_Transform_.scale_.y = std::stof(tmp);
				start_Transform_.scale_.z = std::stof(tmp);
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

	

	//背景画像のロード
	hhaikei_ = Image::Load("haikei.png");
	assert(hhaikei_ >= 0);

	hTitle_ = Image::Load("Title.png");
	assert(hTitle_ >= 0);

	title_Transform_.position_.y = 0.1f;

	titleMovingUp_ = true;       //最初は上に移動
	titleMoveSpeed_ = 0.001f;    //移動速度

	start_ = Instantiate<Button>(this);
	start_->SetImage("StartTest");
	start_->SetPosition(600, 650);//ウィンドウの横幅1280,縦720
	start_->SetNextScene(SELECT);
	start_->SetIsFlash(false);
}

//更新
void TitleScene::Update()
{
	//titleの位置を更新
	if (titleMovingUp_) {
		title_Transform_.position_.y += titleMoveSpeed_;
	}
	else {
		title_Transform_.position_.y -= titleMoveSpeed_;
	}
	
	//一定の範囲で反転させる
	if (title_Transform_.position_.y > 0.1f) {
		titleMovingUp_ = false;
	}
	else if (title_Transform_.position_.y < -0.1f) {
		titleMovingUp_ = true;
	}


	XMFLOAT3 pos = Input::GetMousePosition();
	if (start_->MouseInArea(pos)) {
		start_->Push(true);
		

	} else {
		start_->Push(false);

	}

}

//描画
void TitleScene::Draw()
{

	Image::SetTransform(hhaikei_, transform_);
	Image::Draw(hhaikei_);

	Image::SetTransform(hTitle_, title_Transform_);
	Image::Draw(hTitle_);


}

//開放
void TitleScene::Release()
{
}

void TitleScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Title"))
	{
		//Setting_Transform(start_Transform_, -1, 1, 0, 10, "Title");
		
	}
	ImGui::End();

	if (Input::IsKey(DIK_S) && Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_S) && Input::IsKey(DIK_RSHIFT)) {

		//Save_Transform_File(hFile_, fileName);

		hFile_ = CreateFile(
			fileName,                 //ファイル名
			GENERIC_WRITE,           //アクセスモード（書き込み用）
			0,                      //共有（なし）
			NULL,                   //セキュリティ属性（継承しない）
			CREATE_ALWAYS,           //作成方法
			FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
			NULL);                  //拡張属性（なし


		float* save[] = { &start_Transform_.position_.x, &start_Transform_.position_.y, &start_Transform_.position_.z,
						  &start_Transform_.rotate_.x, &start_Transform_.rotate_.y, &start_Transform_.rotate_.z,
						  &start_Transform_.scale_.x };

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
