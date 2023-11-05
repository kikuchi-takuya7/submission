#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class StateAnimation : public GameObject
{

public:
    //�R���X�g���N�^
    StateAnimation(GameObject* parent);

    //�f�X�g���N�^
    ~StateAnimation();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};