#include "gameObject.h"
#include <assert.h>
#include "global.h"

//�R���X�g���N�^�i�e�����O���Ȃ��j
GameObject::GameObject(void) :
	GameObject(nullptr, "")
{

}

//�R���X�g���N�^�i���O�Ȃ��j
GameObject::GameObject(GameObject* parent) :
	GameObject(parent, "")
{
}

//�R���X�g���N�^�i�W���j
GameObject::GameObject(GameObject* parent, const std::string& name)
	: pParent_(parent), objectName_(name), objectID_('N')
{
	childList_.clear();
	state_ = { 0, 1, 1, 0 };

	if (parent)
		transform_.pParent_ = &parent->transform_;

}

//�f�X�g���N�^
GameObject::~GameObject()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}

// �폜���邩�ǂ���
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

// �������폜����
void GameObject::KillMe()
{
	state_.dead = 1;
}

// Update������
void GameObject::Enter()
{
	state_.entered = 1;
}

// Update������
void GameObject::Leave()
{
	state_.entered = 0;
}

// Draw������
void GameObject::Visible()
{
	state_.visible = 1;
}

// Draw������
void GameObject::Invisible()
{
	state_.visible = 0;
}

// �������ς݂��ǂ���
bool GameObject::IsInitialized()
{
	return (state_.initialized != 0);
}

// �������ς݂ɂ���
void GameObject::SetInitialized()
{
	state_.initialized = 1;
}

// Update���s���Ă�����
bool GameObject::IsEntered()
{
	return (state_.entered != 0);
}

// Draw���s���Ă�����
bool GameObject::IsVisibled()
{
	return (state_.visible != 0);
}

//�q�I�u�W�F�N�g���X�g���擾
std::list<GameObject*>* GameObject::GetChildList()
{
	return &childList_;
}

//�e�I�u�W�F�N�g���擾
GameObject* GameObject::GetParent(void)
{
	return pParent_;
}

//���O�ŃI�u�W�F�N�g�������i�Ώۂ͎����̎q���ȉ��j
GameObject* GameObject::FindChildObject(const std::string& name)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return nullptr;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g����T��
	while (it != end) {
		//�������O�̃I�u�W�F�N�g���������炻���Ԃ�
		if ((*it)->GetObjectName() == name)
			return *it;

		//���̎q���i���j�ȍ~�ɂ��Ȃ����T��
		GameObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr)
		{
			return obj;
		}

		//���̎q��
		it++;
	}

	//������Ȃ�����
	return nullptr;
}

//�I�u�W�F�N�g�̖��O���擾
const std::string& GameObject::GetObjectName(void) const
{
	return objectName_;
}

//�q�I�u�W�F�N�g��ǉ��i���X�g�̍Ō�ցj
void GameObject::PushBackChild(GameObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);
}

//�q�I�u�W�F�N�g��ǉ��i���X�g�̐擪�ցj
void GameObject::PushFrontChild(GameObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_front(obj);
}

//�q�I�u�W�F�N�g��S�č폜
void GameObject::KillAllChildren(void)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g��1���폜
	while (it != end)
	{
		KillObjectSub(*it);
		delete* it;
		it = childList_.erase(it);
	}

	//���X�g���N���A
	childList_.clear();
}

//�I�u�W�F�N�g�폜�i�ċA�j
void GameObject::KillObjectSub(GameObject* obj)
{
	if (!childList_.empty())
	{
		auto list = obj->GetChildList();
		auto it = list->begin();
		auto end = list->end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete* it;
			it = list->erase(it);
		}
		list->clear();
	}
	obj->Release();
}



//�R���C�_�[�i�Փ˔���j��ǉ�����
void GameObject::AddCollider(Collider* collider)
{
	collider->SetGameObject(this);
	colliderList_.push_back(collider);
}

//�R���C�_�[�i�Փ˔���j���폜
void GameObject::ClearCollider()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}

//�Փ˔���
void GameObject::Collision(GameObject* pTarget)
{
	//�������m�̓����蔻��͂��Ȃ�
	if (pTarget == nullptr || this == pTarget)
	{
		return;
	}

	//������pTarget�̃R���W���������g���ē����蔻��
	//1�̃I�u�W�F�N�g�������̃R���W�������������Ă�ꍇ������̂œ�d���[�v
	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		for (auto j = pTarget->colliderList_.begin(); j != pTarget->colliderList_.end(); j++)
		{
			if ((*i)->IsHit(*j))
			{
				//��������
				this->OnCollision(pTarget);
			}
		}
	}

	//�q�������Ȃ��Ȃ�I���
	if (pTarget->childList_.empty())
		return;

	//�q���������蔻��
	for (auto i = pTarget->childList_.begin(); i != pTarget->childList_.end(); i++)
	{
		Collision(*i);
	}
}


//�e�X�g�p�̏Փ˔���g��\��
void GameObject::CollisionDraw()
{
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);

	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		(*i)->Draw(GetWorldPosition());
	}

	Direct3D::SetShader(Direct3D::SHADER_3D);
}

//RootJob���擾
GameObject* GameObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}




void GameObject::UpdateSub()
{
	Update();
	Transform();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}

	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			//�����蔻��
			(*it)->Collision(GetParent());
			it++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();


	//�����[�X���͍폜
#ifdef _DEBUG
		//�R���W�����̕`��
	if (Direct3D::isDrawCollision_)
	{
		CollisionDraw();
	}
#endif

	//���̎q�I�u�W�F�N�g�̕`�揈��
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	//�R���C�_�[���폜
	ClearCollider();


	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
	}

	Release();
}

void GameObject::Imgui_WindowSub()
{

	Imgui_Window();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->Imgui_WindowSub();
	}
}




////���[�J���s��̎擾�i���̃I�u�W�F�N�g�̍s��j
//XMMATRIX GameObject::GetLocalMatrix(void)
//{
//	return transform_.GetWorldMatrix();
//}

//���[���h�s��̎擾�i�e�̉e�����󂯂��ŏI�I�ȍs��j
XMMATRIX GameObject::GetWorldMatrix(void)
{
	return transform_.GetWorldMatrix();
}

void GameObject::Setting_Transform(Transform& _transform, float posmin, float posmax, float rot, float scl, std::string str)
{

	float* p[] = { &_transform.position_.x ,&_transform.position_.y, &_transform.position_.z };
	float* r[] = { &_transform.rotate_.x ,&_transform.rotate_.y, &_transform.rotate_.z };
	float s = _transform.scale_.x;

	std::string tmpString = str;
	tmpString = str + "sPosition.x";
	char* c = new char[tmpString.size() + 1];
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, p[0], posmin, posmax);

	tmpString = str + "sPosition.y";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, p[1], posmin, posmax);

	tmpString = str + "sPosition.z";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, p[2], posmin, posmax);

	tmpString = str + "sRotate";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat3(c, *r, 0.0f, rot);

	tmpString = str + "sScale";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, &s, 0.0f, scl);

	_transform.scale_.x = s;
	_transform.scale_.y = s;
	_transform.scale_.z = s;


	delete[] c;

}

void GameObject::Save_Transform_File(Transform _transform, HANDLE hFile, LPCSTR fileName)
{
	hFile = CreateFile(
		fileName,                 //�t�@�C����
		GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		CREATE_ALWAYS,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);                  //�g�������i�Ȃ�


	float* save[] = { &_transform.position_.x, &_transform.position_.y, &_transform.position_.z,
					  &_transform.rotate_.x, &_transform.rotate_.y, &_transform.rotate_.z,
					  &_transform.scale_.x };

	const int size = sizeof(save) / sizeof(save[0]);

	std::string s[size];

	for (int i = 0; i < size; i++) {
		s[i] = std::to_string(*save[i]) + " ";
	}

	DWORD dwBytes = 0;  //�������݈ʒu

	for (int i = 0; i < size; i++) {

		WriteFile(
			hFile,                   //�t�@�C���n���h��
			s[i].c_str(),                  //�ۑ�����f�[�^�i������j
			(DWORD)strlen(s[i].c_str()),   //�������ޕ�����
			&dwBytes,                //�������񂾃T�C�Y������ϐ�
			NULL);                   //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

	}

	CloseHandle(hFile);
}

void GameObject::Load_Transform_File(HANDLE hFile, LPCSTR fileName)
{
	hFile = CreateFile(
		fileName,                 //�t�@�C����
		GENERIC_READ,           //�A�N�Z�X���[�h�i�������ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		OPEN_ALWAYS,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);

	//�t�@�C���̃T�C�Y���擾
	DWORD fileSize = GetFileSize(hFile, NULL);

	//�t�@�C���̃T�C�Y�����������m��
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //�ǂݍ��݈ʒu

	ReadFile(
		hFile,     //�t�@�C���n���h��
		data,      //�f�[�^������ϐ�
		fileSize,  //�ǂݍ��ރT�C�Y
		&dwBytes,  //�ǂݍ��񂾃T�C�Y
		NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

	//�����Ńt�@�C���T�C�Y���J��Ԃ��āA�󔒂��o���炻��܂ł̒l���|�W�V�����Ȃ�ɓ����Ƃ����悳����
	//�ŏ���char�^��tmp�ɓ���Ƃ��Č��string�ɓ���Ȃ����Ƃ��ł��悳����
	char* tmp = new char[fileSize];
	int c = 0, sw = 0;
	for (DWORD i = 0; i < fileSize; i++) {

		if (data[i] == ' ') {
			switch (sw)
			{
			case 0:
				transform_.position_.x = std::stof(tmp);
				break;
			case 1:
				transform_.position_.y = std::stof(tmp);
				break;
			case 2:
				transform_.position_.z = std::stof(tmp);
				break;
			case 3:
				transform_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				transform_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				transform_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				transform_.scale_.x = std::stof(tmp);
				transform_.scale_.y = std::stof(tmp);
				transform_.scale_.z = std::stof(tmp);
				break;

			default:
				break;
			}
			sw++;
			c = 0;
			continue;
		}
		tmp[c] = data[i];
		c++;
	}
	delete[] tmp;
	delete[] data;

	CloseHandle(hFile);
}