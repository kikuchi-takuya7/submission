#include "SaveManager.h"
#include <iostream>
#include "../json-develop/include/nlohmann/json.hpp"
#include "../../TestWall.h"
#include "../../TestFloor.h"
#include "../../Room1.h"
#include "../../School.h"
#include "../MapEditor/MapData.h"
#include <fstream>

using json = nlohmann::json;
using string = std::string;


//�R���X�g���N�^
SaveManager::SaveManager(GameObject* parent)
    :GameObject(parent, "SaveManager"),fileName_{"�V�K�t�@�C��.json"}
{
}

//�f�X�g���N�^
SaveManager::~SaveManager()
{
}

//������
void SaveManager::Initialize()
{
    
}

//�X�V
void SaveManager::Update()
{

}

void SaveManager::Draw()
{
}

//�J��
void SaveManager::Release()
{
    //m_SaveObjctList_.clear();
}

void SaveManager::Save(std::list<GameObject*> list)
{

    //�t�@�C�����J��
    std::ofstream writing_file;
    writing_file.open(fileName_, std::ios::out);

    for (auto itr = list.begin(); itr != list.end();itr++) {


        //���ꂼ���Transform���������ē����
        XMFLOAT3 pos = (*itr)->GetPosition();
        XMFLOAT3 rot = (*itr)->GetRotate();
        XMFLOAT3 sca = (*itr)->GetScale();

        float arr[9] = { pos.x,pos.y,pos.z,
                         rot.x,rot.y,rot.z,
                         sca.x,sca.y,sca.z };

        //string�^�ŕۑ����Ȃ��ƃ��[�h�̎������߂�ǂ������Ȃ�
        int ID = (*itr)->GetObjectID();
        std::string s = std::to_string(ID);

        json m_json = {
                {"objectName",(*itr)->GetObjectName()},
                {"Transform",arr},
                {"objectID",s} 
        };

        //��s������
        writing_file << m_json.dump() << std::endl;
    }
        
    writing_file.close();
}

void SaveManager::AddSaveObj(GameObject* obj)
{
    //m_SaveObjctList_.push_back(obj);
}

void SaveManager::Load()
{

    //�ǂݍ��݂Ɏ��s�����ꍇ�̓G���[��\������
    std::ifstream ifs(fileName_);

    //eof����肭�g���Ȃ�����t�@�C���̍s����������ɂ�������
    int fileLine = 0;

    //�ǂݍ��߂Ȃ�������Ԃ�
    if (!ifs)
        return;

    while (true)
    {
        string line;
        // 1�s�ǂݎ��B
        getline(ifs, line);
        fileLine++;

        // �t�@�C�����I�[�܂ŗ�����break 
        if (ifs.eof())
            break;
    }

    //���t�@�C���ǂݍ��݂��񂵂������U����
    ifs.close();

    //���͂̎��ɉ��s���Ă邩�����炷
    fileLine--;

    ifs.open(fileName_, std::ios::in);

    //�t�@�C���̃��C���̐�������
    for (int i = 0; i < fileLine;i++) {
        json m_json;
        ifs >> m_json;

        //�v�f����Ȃ��߂�
        if (m_json["objectName"].empty() || m_json["Transform"].empty() || m_json["objectID"].empty())
            continue;

        GameObject* object = CreateObj(m_json["objectName"]);
            
        //�ǂݍ��񂾃f�[�^���I�u�W�F�N�g�ɓ����
        Transform objTrans;
        objTrans.position_.x = m_json["Transform"].at(0);
        objTrans.position_.y = m_json["Transform"].at(1);
        objTrans.position_.z = m_json["Transform"].at(2);
        objTrans.rotate_.x = m_json["Transform"].at(3);
        objTrans.rotate_.y = m_json["Transform"].at(4);
        objTrans.rotate_.z = m_json["Transform"].at(5);
        objTrans.scale_.x = m_json["Transform"].at(6);
        objTrans.scale_.y = m_json["Transform"].at(7);
        objTrans.scale_.z = m_json["Transform"].at(8);

        object->SetTransform(objTrans);

        //String��int�ɕς��ĕۑ�
        std::string tmpString = m_json["objectID"];

        object->SetObjectID(std::stoi(tmpString));

    }

    ifs.close();
}

GameObject* SaveManager::CreateObj(std::string className)
{
    //���[�h����objectName�ɑΉ�����I�u�W�F�N�g���쐬���ASaveManager���Ăяo�����̂�MapData�Ȃ�createObject�ɓ����
    if (className == "TestWall") {
        TestWall* object = CreateObject<TestWall>();
        return object;
    }
    else if (className == "TestFloor") {
        TestFloor* object = CreateObject<TestFloor>();
        return object;
    }
    else if (className == "Room1") {
        Room1* object = CreateObject<Room1>();
        return object;
    }
    else if (className == "School") {
        School* object = CreateObject<School>();
        return object;
    }
    return NULL;   // �w��̃N���X������
}

void SaveManager::OpenFile()
{

    //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
    OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
    ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
    ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
    ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.json)\0*.json\0")        //�����t�@�C���̎��
        TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
    ofn.lpstrFile = fileName_;               	//�t�@�C����
    ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
    ofn.Flags = OFN_FILEMUSTEXIST;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
    ofn.lpstrDefExt = "json";                  	//�f�t�H���g�g���q

    //�u�t�@�C����ۑ��v�_�C�A���O
    BOOL selFile;
    selFile = GetOpenFileName(&ofn);

    //�L�����Z�������璆�f
    if (selFile == FALSE) return;

}

void SaveManager::NewCreateFile()
{
    //�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
    OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
    ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
    ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
    ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.json)\0*.json\0")        //�����t�@�C���̎��
        TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
    ofn.lpstrFile = fileName_;               	//�t�@�C����
    ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
    ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
    ofn.lpstrDefExt = "json";                  	//�f�t�H���g�g���q

    //�u�t�@�C����ۑ��v�_�C�A���O
    BOOL selFile;
    selFile = GetSaveFileName(&ofn);

    //�L�����Z�������璆�f
    if (selFile == FALSE) return;
}

