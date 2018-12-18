/// <summary>
/// CarFactory.h
/// 
/// �����:2018/7/13
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

#include "../../Utility/Utility.h"

/// <summary>
/// �O���錾
/// </summary>
class Entity;

/// <summary>
/// �ԃt�@�N�g���N���X
/// </summary>
class CarFactory : public SingletonBase<CarFactory>
{
public:
	// �R���X�g���N�^
	CarFactory();
	// �f�X�g���N�^
	~CarFactory();

	// �Ԃ̐���
	Entity* CreateCar();

private:
	DirectX::Model* m_carBodyModel;	// �Ԃ̃��f��
	DirectX::Model* m_carCannonModel;	// �Ԃ̃��f��
};