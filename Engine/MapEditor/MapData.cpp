#include "MapData.h"
#include "../Model.h"
#include "../Input.h"
#include "../Camera.h"
#include "../SaveManager/SaveManager.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../Global.h"
#include "../../TestWall.h"
#include "../../TestFloor.h"
#include "../../Room1.h"
#include "../../School.h"


//�R���X�g���N�^
MapData::MapData(GameObject* parent)
	: GameObject(parent, "MapData"),selecting_object(PATTERN_END),isSave_(false),nextObjectId_(0),isNewSave_(false),isLoad_(false)
{

    
}

//������
void MapData::Initialize()
{
    //�t�@�C���̒��ɓ����Ă邷�ׂĂ�fbx�t�@�C���̖��O�̎擾
    fileName_ = get_file_path_in_dir("./Map/", "fbx");
    
    //fileName�̌����̗v�f�����m��
    hModel_.assign(fileName_.size(),-1);

    for (int i = 0; i < hModel_.size(); i++) {
        std::string dir = "Map/";
        hModel_.at(i) = Model::Load(dir + fileName_.at(i));
        assert(hModel_.at(i) >= 0);
    }
    
    pSaveManager_ = Instantiate<SaveManager>(this);
    pSaveManager_->OpenFile();
    pSaveManager_->Load();

    CheckDeleteObject();
    nextObjectId_ = MaxObjectId();
    nextObjectId_++;
}

//�X�V
void MapData::Update()
{
    //����`�F�b�N���Ȃ��ƃf���[�g�����^�C�~���O�ŃG���[�o��B����RootObject��Update�ŏ����ꂽ���ǂ����m�F���Ă邩��
    CheckDeleteObject();



    //float w = (float)(Direct3D::screenWidth_ / 2.0f);
    //float h = (float)(Direct3D::screenHeight_ / 2.0f);
    //float offsetX = 0;
    //float offsetY = 0;
    //float minZ = 0;
    //float maxZ = 1;

    ////�r���[�|�[�g�쐬
    //XMMATRIX vp =
    //{
    //    w                ,0                ,0           ,0,
    //    0                ,-h               ,0           ,0,
    //    0                ,0                ,maxZ - minZ ,0,
    //    offsetX + w      ,offsetY + h      ,minZ        ,1
    //};

    ////�r���[�|�[�g���t�s���
    //XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    ////�v���W�F�N�V�����ϊ�
    //XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    ////�т�[�ϊ�
    //XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    //XMFLOAT3 mousePosFront = Input::GetMousePosition();
    //mousePosFront.z = 0.0;
    //XMFLOAT3 mousePosBack = Input::GetMousePosition();
    //mousePosBack.z = 1.0f;

    ////1,mousePosFront���x�N�g���ɕϊ�
    //XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    ////2. 1��invVP,invPrj,invView��������
    //vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    ////3,mousePosBack���x�N�g���ɕϊ�
    //XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    ////4,3��invVP,invPrj,invVeew��������
    //vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
    ////5,2����4�Ɍ������ă��C��łi�Ƃ肠�����j

    //int changeX = 0;
    //int	changeZ = 0;
    //float minDist = 9999;


    //RayCastData data;
    //XMStoreFloat3(&data.start, vMouseFront);
    //XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);

    //Model::RayCast(hModel_[0], &data);

    //if (data.hit) {
    //    data.hit = false;

    //}

    //Transform objPos;
    //objPos.position_.y = 1.0f;

    //���N���b�N���ꂽ
    if (Input::IsMouseButtonDown(0))
    {
        //���炩�̏���
        CreateObject();
    }
}

//�`��
void MapData::Draw()
{

    if (selecting_object == PATTERN_END)
        return;

    Transform objPos;
    //objPos.position_.y = 1.0f;
    Model::SetTransform(hModel_.at(selecting_object), objPos);
    Model::Draw(hModel_.at(selecting_object));
}

//�J��
void MapData::Release()
{
}

void MapData::Imgui_Window()
{
    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {

        if (ImGui::TreeNode("Object")){//Object�̃c���[���N���b�N�����

            int tmp = selecting_object;
            for (int i = 0; i < fileName_.size(); i++) { //fileName���������̖��O�̃��W�I�{�^�����o��悤�ɁBi��selecting_object����v�����炻�������I���ł���
                ImGui::RadioButton(fileName_.at(i).c_str(), &tmp, i);
            }

            ImGui::RadioButton("stay", &tmp, PATTERN_END);//�����I�����Ă��Ȃ���Ԃɂ��������p
            selecting_object = static_cast<FBXPATTERN>(tmp);//int����enum��
            ImGui::TreePop();
        }

        //�V�K�쐬
        if (ImGui::Button("CreateNewFile")) {
            isNewSave_ = true;
        }

        //���[�h
        if (ImGui::Button("Load")) {
            isLoad_ = true;
        }
        
        //�Z�[�u
        if (ImGui::Button("Save")) {
            isSave_ = true;
        }

        //�V�K�쐬
        if (isNewSave_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("CreateNewFile?", &isNewSave_);
            if (ImGui::Button("Create")) {
                //CheckDeleteObject();
                AllDeleteCreateObject();
                pSaveManager_->NewCreateFile();
                pSaveManager_->Save(createObjectList_);
                isNewSave_ = false;
            }
            ImGui::End();
        }

        //���[�h
        if (isLoad_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("LoadOk?", &isSave_);
            if (ImGui::Button("Load")) {
                AllDeleteCreateObject();
                pSaveManager_->OpenFile();
                pSaveManager_->Load();
                isLoad_ = false;
            }
            ImGui::End();
        }

        //Save�������ꂽ�炱�����\�������
        if (isSave_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("SaveOk?",&isSave_);
            if (ImGui::Button("Save")) {
                //CheckDeleteObject();
                pSaveManager_->Save(createObjectList_);
                isSave_ = false;
            }
            ImGui::End();
        }

        
    }


    //�����Ɋe�I�u�W�F�N�g��Transform�Ƃ��܂Ƃ߂ď����������������ǁAlist��GameObject�^�����炻�ꂼ���isDelete_�ƃA�N�Z�X�ł��Ȃ�����U��߂�
    if (ImGui::CollapsingHeader("ObjectData"))
    {
        if (ImGui::TreeNode("Data")) {//Object�̃c���[���N���b�N�����

            //���ꂼ��̃I�u�W�F�N�g����vector�C���X�^���X�����Ă����Γ�dfor���ł킴�킴GameObject�^�Ɋ֐����Ȃ��Ă��s����񂶂�ˁH
            for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
            
            

                (*itr)->Imgui_Data_Edit();
                
            }

            ImGui::TreePop();
        }
    }
    ImGui::End();
}

GameObject* MapData::CreateObject()
{

    //for�ŉ񂵂�FBXPATTERN��filename�̗v�f�̏��Ԃ���v�����Ƃ���ŃI�u�W�F�N�g�����̂��z�肵������objectName�Ƃ����߂�ǂ������Ȃ邩�疳��
    //�Ή�����enum�^�̐����ɂȂ����炻�̃I�u�W�F�N�g���쐬����createObject�Ƀv�b�V���o�b�N����

    //���ꂼ��̃I�u�W�F�N�g�̃C���X�^���X���N���X�ϐ���vector�Ŏ����āA���[�����[������΂Ȃ񂩂����Ɗy�ł���������ˁH
    switch (selecting_object)
    {
    //case SCHOOL: {
    //    School* pSchool = Instantiate<School>(this);
    //    AddCreateObject(pSchool);
    //    pSchool->SetObjectID(nextObjectId_); //������I�u�W�F�N�g���Ɏ��ʂ��邽�߂�ID��t����
    //    return pSchool;
    //    break;
    //}
    case ROOM_1: {
        Room1* pObject = CreateInstance<Room1>();
        return pObject;
        break;
    }
    case TESTFLOOR: {
        TestFloor* pObject = CreateInstance<TestFloor>();
        return pObject;
        break;
    }
    case TESTWALL: {
        TestWall* pObject = CreateInstance<TestWall>();
        return pObject;
        break;
    }
    case PATTERN_END: {
        break;
    }
    default:
        break;
    }

    return NULL;   // �w��̃N���X������
}

void MapData::AddCreateObject(GameObject* object)
{
    //CheckDeleteObject();
    createObjectList_.push_back(object);
    nextObjectId_++;
}

std::vector<std::string> MapData::get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
{
    HANDLE hFind;
    WIN32_FIND_DATA win32fd;//defined at Windwos.h
    std::vector<std::string> file_names;

    //�g���q�̐ݒ�
    std::string search_name = dir_name + "*." + extension;

    hFind = FindFirstFile(search_name.c_str(), &win32fd);

    if (hFind == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("file not found");
    }

    do {
        if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        }
        else {
            file_names.push_back(win32fd.cFileName);
            printf("%s\n", file_names.back().c_str());

        }
    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return file_names;
}

void MapData::CheckDeleteObject()
{

    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end();) {
        if ((*itr)->IsDead()) {
            itr = createObjectList_.erase(itr);
        }
        else {
            itr++;
        }
    }

}

void MapData::AllDeleteCreateObject()
{
    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end();itr++) {
        (*itr)->KillMe();
    }

    createObjectList_.clear();
}

void MapData::ChengeUp(GameObject* pTarget)
{

    auto itr = createObjectList_.begin();

    //���ɐ擪�Ȃ�
    if ((*itr) == pTarget)
        return;

    for (itr ; itr != createObjectList_.end(); itr++) {
        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, -1), createObjectList_, itr);
            break;
        }
    }

    //isUp_ = true;

    /*SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->Save("SaveFile/SaveTest.json", createObjectList_);*/
    /*KillAllChildren();
    createObjectList_.clear();
    SaveManager* pSaveManager2 = Instantiate<SaveManager>(this);
    pSaveManager2->Load("SaveFile/SaveTest.json");*/

    //���̊֐����q����Ăяo���Ă�̂�KillAllChildren�łԂ��E���Ă邩��G���[�ɂȂ�
    //bool�^�ϐ��������true�Ȃ炱������UpDate���ɏ�̏���������z���l�������ǃt�@�C���̃��[�h����肭�ł��ĂȂ������B�v���W�F�N�g���s���̓t�@�C�����������Ă����s���ɂ͐V�����f�[�^�����[�h�ł��Ȃ��H
}

void MapData::ChengeDown(GameObject* pTarget)
{

    auto itr = createObjectList_.end();

    itr--;
    //���Ɉ�Ԍ��Ȃ�
    if ((*itr) == pTarget)
        return;

    while(itr!=createObjectList_.begin()) {

        itr--;

        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, 2), createObjectList_, itr);
            break;
        }
    }

}

int MapData::MaxObjectId()
{
    int ID = 0;
    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
        int tmp = (*itr)->GetObjectID();
        if (ID < tmp) {
            ID = tmp;
        }
    }

    return ID;
}

void MapData::BackUpSave()
{

}
