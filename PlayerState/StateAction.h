#pragma once
#include "../Engine/GameObject.h"
#include "PlayerState.h"

//���������Ǘ�����N���X
class StateAction : public GameObject
{

public:
    //�R���X�g���N�^
    StateAction(GameObject* parent);

    //�f�X�g���N�^
    ~StateAction();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};