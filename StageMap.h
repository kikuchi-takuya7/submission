#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class StageMap : public GameObject
{

public:
    //�R���X�g���N�^
    StageMap(GameObject* parent);

    //�f�X�g���N�^
    ~StageMap();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};