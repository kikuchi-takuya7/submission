#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class TestFloor : public GameObject
{
    int hModel_;    //���f���ԍ�
    //char objectID_; //�ǂ̃I�u�W�F�N�g��imgui�����ʂ��邽�߂̃I�u�W�F�N�g
    bool isDelete_;

    bool isClose_;

public:
    //�R���X�g���N�^
    TestFloor(GameObject* parent);

    //�f�X�g���N�^
    ~TestFloor();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Imgui_Window() override;

    void Imgui_Data_Edit() override;

    bool IsKillCheck();

    void DeleteMe();

    void DeleteStop();

};