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
#include "../EntityVector.h"

#include "../../Component/ComponentLib.h"
#include "../../GameComponent/Player/PlayerCannonComponent.h"
#include "../../GameComponent/Player/CameraRotateComponent.h"
#include "../../GameComponent/BaseObject/BaseObjectComponent.h"
#include "../../GameComponent/BaseObject/flowComponent.h"
#include "../../GameComponent/BaseObject/StatusComponent.h"


/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CarFactory::CarFactory()
{
	ModelData* modelData = ModelData::GetInstance();
	m_carBodyModel = modelData->GetCarBody();
	m_carCannonModel = modelData->GetCarCannon();
}

CarFactory::~CarFactory()
{
	m_carBodyModel = nullptr;
	m_carCannonModel = nullptr;
}

/// <summary>
/// �Ԃ̐���
/// </summary>
/// <returns>�������ꂽ�Ԃ̒��Őe�ƂȂ�I�u�W�F�N�g�̃|�C���^��Ԃ�</returns>
Entity* CarFactory::CreateCar(MyCamera* camera)
{

	EntityVector* entityVector = EntityVector::GetInstance();


	// ----- �{�f�B�𐶐� -----
	Entity* entity_body = new Entity();
	entity_body->GetTrans().radius.Set(1.5f);

	entity_body->SetName("Player");
	entity_body->SetTag(Tag::Player1);
	entity_body->GetTrans().pos.Set(Vector3(0.0f, 3.0f, -5.0f));

	// ���f���R���|�[�l���g�̒ǉ�
	entity_body->AddComponent(new ModelComponent(m_carBodyModel, ModelComponent::Type::Nomal));

	//// �����R���|�[�l���g�̒ǉ�
	PhysicsComponent* physics = new PhysicsComponent();
	physics->SetIsGravity(false);
	physics->SetIsFriction(false);
	entity_body->AddComponent(physics);

	// ���̓����蔻��R���|�[�l���g�̒ǉ�
	entity_body->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 1.5f));

	// ���̓R���|�[�l���g��ǉ�
	entity_body->AddComponent(new InputComponent());

	// �I�u�W�F�N�g�̌��R���|�[�l���g��ǉ�
	entity_body->AddComponent(new BaseObjectComponent());

	// �J�����̑���R���|�[�l���g��ǉ�
	entity_body->AddComponent(new CameraRotateComponent(camera, CameraRotateComponent::Type::Vertical));

	// ���V�R���|�[�l���g��ǉ�
	//entity_body->AddComponent(new FlowComponent());

	// �X�e�[�^�X�R���|�[�l���g��ǉ�
	entity_body->AddComponent(new StatusComponent());

	entityVector->Add(entity_body);



	// ----- �C��𐶐� -----
	Entity* entity_cannon = new Entity();
	entity_cannon->GetTrans().pos.Set(Vector3(0.0f, -0.25f, 0.5f));
	entity_cannon->SetName("cannon");

	// �e��ݒ�
	entity_body->AddChild(entity_cannon);

	// ���f���R���|�[�l���g�̒ǉ�
	entity_cannon->AddComponent(new ModelComponent(m_carCannonModel, ModelComponent::Type::Nomal));

	// ��C�̃R���|�[�l���g�̒ǉ�
	entity_cannon->AddComponent(new PlayerCannonComponent(camera));

	entityVector->Add(entity_cannon);

	return entity_body;
}
