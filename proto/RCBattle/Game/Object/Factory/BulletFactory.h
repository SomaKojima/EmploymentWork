/// <summary>
/// BulletFactory.h
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
/// �e�t�@�N�g���N���X
/// </summary>
class BulletFactory : public SingletonBase<BulletFactory>
{
public:
	// �R���X�g���N�^
	BulletFactory();
	// �f�X�g���N�^
	~BulletFactory();

	// �e�̐���
	Entity* CreateBullet();

private:
	//static BulletFactory* sBulletFactory;

	DirectX::Model* m_bulletModel;	// �e�̃��f��
};
