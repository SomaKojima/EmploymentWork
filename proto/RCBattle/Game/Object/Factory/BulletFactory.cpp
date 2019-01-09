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
}

BulletFactory::~BulletFactory()
{
}

/// <summary>
/// �e�̐���
/// </summary>
/// <returns>�������ꂽ�e�̒��Őe�ƂȂ�I�u�W�F�N�g�̃|�C���^��Ԃ�</returns>
Entity * BulletFactory::CreateBullet(int num)
{
	ModelData* modelData = ModelData::GetInstance();
	Entity* entity = nullptr;

	entity = new Entity();
	// ���f���R���|�[�l���g�̒ǉ�
	switch (num)
	{
	case 0:
		entity->AddComponent(new ModelComponent(modelData->GetBullet(), ModelComponent::Type::Nomal));
		break;
	case 1:
		entity->AddComponent(new ModelComponent(modelData->GetBullet2(), ModelComponent::Type::Nomal));
		break;
	}
	// ���̓����蔻��R���|�[�l���g�̒ǉ�
	entity->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 0.1f));
	entity->GetTrans().radius.Set(0.4f);
	entity->AddComponent(new BulletComponent());

	return entity;
}


