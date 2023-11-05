#include "StageMap.h"
#include "Engine/SaveManager/SaveManager.h"

//�R���X�g���N�^
StageMap::StageMap(GameObject* parent)
    :GameObject(parent, "StageMap")
{
}

//�f�X�g���N�^
StageMap::~StageMap()
{
}

//������
void StageMap::Initialize()
{
    SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->OpenFile();
    pSaveManager->Load();
}

//�X�V
void StageMap::Update()
{
}

//�`��
void StageMap::Draw()
{
}

//�J��
void StageMap::Release()
{
}