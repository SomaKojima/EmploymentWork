/// <summary>
/// CarFactory.cpp
/// 
/// �����:2018/7/13
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
#include "CarFactory.h"
#include "../Entity.h"
#include "../ModelData.h"

#include "../../Component/ComponentLib.h"

/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CarFactory::CarFactory()
{
	ModelData* modelData = ModelData::GetInstance();
	m_carModel = modelData->GetCar();
}

CarFactory::~CarFactory()
{
	m_carModel = nullptr;
}

/// <summary>
/// �Ԃ̐���
/// </summary>
/// <returns>�������ꂽ�Ԃ̒��Őe�ƂȂ�I�u�W�F�N�g�̃|�C���^��Ԃ�</returns>
Entity* CarFactory::CreateCar()
{
	Entity* entity = new Entity();

	// ���f���R���|�[�l���g�̒ǉ�
	entity->AddComponent(new ModelComponent(m_carModel, ModelComponent::Type::Nomal));
	//// �����R���|�[�l���g�̒ǉ�
	PhysicsComponent* physics = new PhysicsComponent();
	////physics->SetIsGravity(false);
	entity->AddComponent(physics);
	// ���̓����蔻��R���|�[�l���g�̒ǉ�
	entity->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 1.5f));

	entity->GetTrans().SetRadius(1.5f);

	return entity;
}
