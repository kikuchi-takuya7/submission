#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position);
	void SetPosition(XMFLOAT3 position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target);
	void SetTarget(XMFLOAT3 target);

	//�ʒu���擾
	XMFLOAT3 GetPosition();

	//�œ_���擾
	XMFLOAT3 GetTarget();

	//�ʒu���擾
	XMVECTOR GetPositionVector();

	//�œ_���擾
	XMVECTOR GetTargetVector();
	
	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();

	//�r���{�[�h�p��]�s����擾
	XMMATRIX GetBillboardMatrix();

	XMFLOAT3 GetScreenPosition(XMFLOAT3 pos3d);



};