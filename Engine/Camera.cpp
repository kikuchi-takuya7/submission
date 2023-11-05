#include "Camera.h"
#include "Direct3D.h"

namespace Camera {
	//�ϐ�
	XMVECTOR position_;	//�J�����̈ʒu�i���_�j
	XMVECTOR target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
	XMMATRIX billBoard_;
}

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	/*XMFLOAT3 position;
	XMStoreFloat3(&position, position_);
	XMFLOAT3 target;
	XMStoreFloat3(&target, target_);
	viewMatrix_ = XMMatrixLookAtLH(XMVectorSet(position.x, position.y, position.z, 0),
	XMVectorSet(target.x, target.y, target.z, 0), XMVectorSet(0, 1, 0, 0));*/

	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	billBoard_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), target_ - position_, XMVectorSet(0, 1, 0, 0));
	billBoard_ = XMMatrixInverse(nullptr, billBoard_);
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	SetPosition(XMLoadFloat3(&position));
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

void Camera::SetTarget(XMFLOAT3 target)
{
	SetTarget(XMLoadFloat3(&target));
}

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() 
{ 
	XMFLOAT3 f;

	XMStoreFloat3(&f, position_);
	return f;
}

//�œ_���擾
XMFLOAT3 Camera::GetTarget()
{
	XMFLOAT3 f;

	XMStoreFloat3(&f, target_);
	return f;
}

XMVECTOR Camera::GetPositionVector()
{
	return position_;
}

XMVECTOR Camera::GetTargetVector()
{
	return target_;
}


//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	//return XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	return viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	//return XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);
	return projMatrix_;
}

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() 
{
	return billBoard_; 
}

XMFLOAT3 Camera::GetScreenPosition(XMFLOAT3 pos3d)
{
	XMVECTOR v2 = XMVector3Transform(XMLoadFloat3(&pos3d), Camera::GetViewMatrix());
	v2 = XMVector3Transform(v2, Camera::GetProjectionMatrix());
	float x = XMVectorGetX(v2);
	float y = XMVectorGetY(v2);
	float z = XMVectorGetZ(v2);
	return XMFLOAT3(
		x / z * Direct3D::screenWidth_ / 2.0f + Direct3D::screenWidth_ / 2.0f,
		-y / z * Direct3D::screenHeight_ / 2.0f + Direct3D::screenHeight_ / 2.0f,
		0);
}