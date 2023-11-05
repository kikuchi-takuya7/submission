#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


const LPCSTR fileName = "SaveFile\\TitleSaveData";

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hhaikei_(-1), hTitle_(-1)
{
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	hFile_ = CreateFile(
		fileName,                 //�t�@�C����
		GENERIC_READ,           //�A�N�Z�X���[�h�i�������ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		OPEN_ALWAYS,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);

	//�t�@�C���̃T�C�Y���擾
	DWORD fileSize = GetFileSize(hFile_, NULL);

	//�t�@�C���̃T�C�Y�����������m��
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //�ǂݍ��݈ʒu

	ReadFile(
		hFile_,     //�t�@�C���n���h��
		data,      //�f�[�^������ϐ�
		fileSize,  //�ǂݍ��ރT�C�Y
		&dwBytes,  //�ǂݍ��񂾃T�C�Y
		NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j


	char* tmp = new char[fileSize];
	int c = 0, sw = 0;

	//�V�������[�h����f�[�^�𑝂₵�����ꍇ��case������₵�Ă��̕ϐ���tmp�̓��e��stof�Ȃ�œ����΂���
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

	

	//�w�i�摜�̃��[�h
	hhaikei_ = Image::Load("haikei.png");
	assert(hhaikei_ >= 0);

	hTitle_ = Image::Load("Title.png");
	assert(hTitle_ >= 0);

	title_Transform_.position_.y = 0.1f;

	titleMovingUp_ = true;       //�ŏ��͏�Ɉړ�
	titleMoveSpeed_ = 0.001f;    //�ړ����x

	start_ = Instantiate<Button>(this);
	start_->SetImage("StartTest");
	start_->SetPosition(600, 650);//�E�B���h�E�̉���1280,�c720
	start_->SetNextScene(SELECT);
	start_->SetIsFlash(false);
}

//�X�V
void TitleScene::Update()
{
	//title�̈ʒu���X�V
	if (titleMovingUp_) {
		title_Transform_.position_.y += titleMoveSpeed_;
	}
	else {
		title_Transform_.position_.y -= titleMoveSpeed_;
	}
	
	//���͈̔͂Ŕ��]������
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

//�`��
void TitleScene::Draw()
{

	Image::SetTransform(hhaikei_, transform_);
	Image::Draw(hhaikei_);

	Image::SetTransform(hTitle_, title_Transform_);
	Image::Draw(hTitle_);


}

//�J��
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
			fileName,                 //�t�@�C����
			GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
			0,                      //���L�i�Ȃ��j
			NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
			CREATE_ALWAYS,           //�쐬���@
			FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
			NULL);                  //�g�������i�Ȃ�


		float* save[] = { &start_Transform_.position_.x, &start_Transform_.position_.y, &start_Transform_.position_.z,
						  &start_Transform_.rotate_.x, &start_Transform_.rotate_.y, &start_Transform_.rotate_.z,
						  &start_Transform_.scale_.x };

		const int size = sizeof(save) / sizeof(save[0]);

		std::string s[size];


		for (int i = 0; i < size; i++) {
			s[i] = std::to_string(*save[i]) + " ";
		}


		DWORD dwBytes = 0;  //�������݈ʒu

		for (int i = 0; i < size; i++) {

			WriteFile(
				hFile_,                   //�t�@�C���n���h��
				s[i].c_str(),                  //�ۑ�����f�[�^�i������j
				(DWORD)strlen(s[i].c_str()),   //�������ޕ�����
				&dwBytes,                //�������񂾃T�C�Y������ϐ�
				NULL);                   //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

		}



		CloseHandle(hFile_);

	}
}
