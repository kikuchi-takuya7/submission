#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class StateMove : public GameObject
{

public:
    //�R���X�g���N�^
    StateMove(GameObject* parent);

    //�f�X�g���N�^
    ~StateMove();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};