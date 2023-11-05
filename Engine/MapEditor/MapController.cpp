#include "MapController.h"
#include "MapData.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Model.h"

//�R���X�g���N�^
MapController::MapController(GameObject* parent)
    :GameObject(parent, "MapController")
{
}

//�f�X�g���N�^
MapController::~MapController()
{
}

//������
void MapController::Initialize()
{
    transform_.rotate_.x = 45.0f;
}

//�X�V
void MapController::Update()
{

    if (Input::IsKey(DIK_LSHIFT) && transform_.position_.y <= 10.0f) {
        transform_.position_.y += 0.2f;
    }
    if (Input::IsKey(DIK_LCONTROL) && transform_.position_.y >= 0.0f) {
        transform_.position_.y -= 0.2f;
    }

    if (Input::IsKey(DIK_LEFTARROW)) {
        transform_.rotate_.y -= 1.0f;
    }
    if (Input::IsKey(DIK_RIGHTARROW)) {
        transform_.rotate_.y += 1.0f;
    }

    if (Input::IsKey(DIK_UPARROW) && transform_.rotate_.x <= 88) {
        transform_.rotate_.x += 1.0f;
    }
    if (Input::IsKey(DIK_DOWNARROW) && transform_.rotate_.x >= 0) {
        transform_.rotate_.x -= 1.0f;
    }

    //transform.rotate_.y�x��]������s����쐬
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //���݂̈ʒu���x�N�g���^�ɕϊ�
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR moveZ = { 0.0f, 0.0f, 0.1f, 0.0f }; //����0.1m

    //�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    moveZ = XMVector3TransformCoord(moveZ, rotY);


    //W�L�[�������ꂽ��ړ�
    if (Input::IsKey(DIK_W)) {
        //�ړ�
        pos += moveZ;

    }

    if (Input::IsKey(DIK_S)) {

        pos -= moveZ;

    }

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR moveX = { 0.1f, 0.0f, 0.0f, 0.0f }; //����0.1m

    //�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    moveX = XMVector3TransformCoord(moveX, rotY);


    if (Input::IsKey(DIK_A)) {

        pos -= moveX;

    }

    if (Input::IsKey(DIK_D)) {

        pos += moveX;

    }

    //���ݒn���x�N�g�����炢����transform.position�ɖ߂�
    XMStoreFloat3(&transform_.position_, pos);

    //�|�W�V��������Ɍ���B
    Camera::SetTarget(transform_.position_);

    //�J�����̈ʒu�͏�Ƀ|�W�V�����̌��
    XMVECTOR vCam = { 0,0,-10,0 };
    vCam = XMVector3TransformCoord(vCam, rotX * rotY);
    Camera::SetPosition(pos + vCam);
}

//�`��
void MapController::Draw()
{
}

//�J��
void MapController::Release()
{
}