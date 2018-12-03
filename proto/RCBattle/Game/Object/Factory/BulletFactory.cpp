/// <summary>
/// BulletFactory.cpp
/// 
/// �����:2018/7/13
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
#include "BulletFactory.h"
#include "../Entity.h"
#include "../ModelData.h"

#include "../../Component/ComponentLib.h"
#include "../../GameComponent/BulletComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//BulletFactory* BulletFactory::sBulletFactory = nullptr;

BulletFactory::BulletFactory()
{
	ModelData* modelData = ModelData::GetInstance();
	m_bulletModel = modelData->GetBullet();
}

BulletFactory::~BulletFactory()
{
	m_bulletModel = nullptr;
}

/// <summary>
/// �e�̐���
/// </summary>
/// <returns>�������ꂽ�e�̒��Őe�ƂȂ�I�u�W�F�N�g�̃|�C���^��Ԃ�</returns>
Entity * BulletFactory::CreateBullet()
{
	Entity* entity = nullptr;

	entity = new Entity();
	// ���f���R���|�[�l���g�̒ǉ�
	entity->AddComponent(new ModelComponent(m_bulletModel, ModelComponent::Type::Nomal));
	// ���̓����蔻��R���|�[�l���g�̒ǉ�
	entity->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 0.1f));
	entity->GetTrans().radius.Set(0.4f);
	entity->AddComponent(new BulletComponent());

	return entity;
}


