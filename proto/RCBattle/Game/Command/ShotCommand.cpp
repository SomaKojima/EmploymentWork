/// <summary>
/// ShotCommand.cpp
/// 
/// �����:2018/7/13
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "ShotCommand.h"
#include "../Object//BulletFactory.h"
#include "../Object/EntityVector.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ShotCommand::ShotCommand()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ShotCommand::~ShotCommand()
{
}

/// <summary>
/// ���s
/// </summary>
/// <param name="entity">����</param>
void ShotCommand::Excute(Entity & entity)
{
	// ���̂̃R���e�i
	EntityVector* entityVector = EntityVector::GetInstance();

	// �e�̍쐬
	BulletFactory* bulletFactory = BulletFactory::GetInstance();
	Entity* _entity = bulletFactory->CreateBullet();

	_entity->SetAngle(entity.GetAngle());
	_entity->SetVel(Vector3(0.0f, 0.0f, 0.2f));

	Vector3 pos = Vector3::Transform(Vector3::Zero, entity.GetWorld());
	pos += Vector3::Transform(Vector3(0.0f, -1.0f, 3.0f), entity.GetDir());
	_entity->SetTrans(pos);
	
	entityVector->Add(_entity);
}
