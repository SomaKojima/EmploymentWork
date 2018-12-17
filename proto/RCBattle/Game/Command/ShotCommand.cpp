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
#include "../Object/Factory/BulletFactory.h"
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

	_entity->GetTrans().dir.Set(entity.GetTrans().dir.Get());
	_entity->GetTrans().vel.SetLocal(Vector3(0.0f, 0.0f, 0.5f));

	Vector3 pos = Vector3::Transform(Vector3::Zero, entity.GetTrans().world.Get());
	pos += Vector3::Transform(Vector3(0.0f, -0.1f, 2.0f), entity.GetTrans().dir.Get());
	_entity->GetTrans().pos.Set(pos);

	_entity->SetName("Bullet");

	// �v���C���[�̒e�̐ݒ�
	_entity->SetTag(Tag::Player1);
	
	entityVector->Add(_entity);
}
