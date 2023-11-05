#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Room1 : public GameObject
{
    int hModel_;    //���f���ԍ�
    //char objectID_; //�ǂ̃I�u�W�F�N�g��imgui�����ʂ��邽�߂̃I�u�W�F�N�g
    bool isDelete_;

    bool isClose_;

public:
    //�R���X�g���N�^
    Room1(GameObject* parent);

    //�f�X�g���N�^
    ~Room1();

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