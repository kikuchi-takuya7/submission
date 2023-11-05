#pragma once
#include "../GameObject.h"
#include <stack>
#include <vector>

class SaveManager;

//�V�����t�@�C����ǉ�������A������CreateObject�ɗv�f���蓮�Œǉ�����
enum FBXPATTERN {
	//SCHOOL,
	ROOM_1,
	TESTFLOOR,
	TESTWALL,
	PATTERN_END
};

struct BACKUPDATA {
	std::string objectName;
	int objectId;
	Transform objectTrans;
};

//�����V�[�����Ǘ�����N���X
class MapData : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MapData(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Imgui_Window() override;

	std::list<GameObject*> GetCreateObjectList() { return createObjectList_; }

	/// <summary>
	/// selecting_object�ɑΉ������I�u�W�F�N�g���쐬����
	/// </summary>
	/// <returns>�쐬�����I�u�W�F�N�g</returns>
	GameObject* CreateObject();

	//createObjectList�ɓ����
	void AddCreateObject(GameObject* object);

	//�f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l��
	std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);

	//createObject�̒���delete���ꂽ�I�u�W�F�N�g�����邩
	void CheckDeleteObject();

	void AllDeleteCreateObject();

	//�I�u�W�F�N�g�̈ʒu�iCreateList�j����ɏグ��
	void ChengeUp(GameObject* pTarget);
	void ChengeDown(GameObject* pTarget);

	//���[�h�������ׂĂ�ID�𒲂ׂčő�l��m���Ă���
	int MaxObjectId();

	//�I�u�W�F�N�g���������ꂽ���Ƀo�b�N�A�b�v���Ƃ�֐�
	void BackUpSave();

private:

	std::vector<int> hModel_;
	
	//Map�t�@�C���̒��ɓ����Ă�fbx�t�@�C���̖��O������
	std::vector<std::string> fileName_;
	
	//imgui�őI������Ă���I�u�W�F�N�g
	FBXPATTERN selecting_object;

	//�쐬�����I�u�W�F�N�g���X�g
	std::list<GameObject*> createObjectList_;

	//std::pair<>

	//std::stack<BACKUPDATA> objectBackUp_;

	SaveManager* pSaveManager_;

	//�Z�[�u���邩�̃t���O
	bool isSave_;

	bool isLoad_;

	bool isNewSave_;

	int nextObjectId_;

	//�C���X�^���X���쐬����objectList�ɓ����e���v���[�g
	template <class T>
	T* CreateInstance()
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pObject->SetObjectID(nextObjectId_); //������I�u�W�F�N�g���Ɏ��ʂ��邽�߂�ID��t����
		return pObject;
	}

};