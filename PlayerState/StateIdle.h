#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class StateIdle : public GameObject
{

public:
    //�R���X�g���N�^
    StateIdle(GameObject* parent);

    //�f�X�g���N�^
    ~StateIdle();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};