#pragma once
#include "../GameObject.h"

//���������Ǘ�����N���X
class MapController : public GameObject
{

public:
    //�R���X�g���N�^
    MapController(GameObject* parent);

    //�f�X�g���N�^
    ~MapController();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};