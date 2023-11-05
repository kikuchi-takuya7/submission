#include "MapEditorScene.h"
#include "MapController.h"
#include "MapData.h"

//�R���X�g���N�^
MapEditorScene::MapEditorScene(GameObject* parent)
	: GameObject(parent, "MapEditorScene")
{
}

//������
void MapEditorScene::Initialize()
{
	Instantiate<MapController>(this);
	Instantiate<MapData>(this);
}

//�X�V
void MapEditorScene::Update()
{
}

//�`��
void MapEditorScene::Draw()
{
}

//�J��
void MapEditorScene::Release()
{
}

void MapEditorScene::Imgui_Window()
{
}
