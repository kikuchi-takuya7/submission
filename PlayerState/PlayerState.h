#pragma once
#include "../Engine/GameObject.h"
#include "StateAction.h"
#include "StateMove.h"
#include "StateAnimation.h"
#include "StateIdle.h"

//���������Ǘ�����N���X
class PlayerState : public GameObject
{

public:
    //�R���X�g���N�^
    PlayerState(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerState();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:
    
    
};