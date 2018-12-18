#include "../../pch.h"
#include "ScenePlay.h"
#include "../Object/ModelData.h"
#include "../Object/SpriteData.h"
#include "../Object/EntityVector.h"
#include "../Object/Entity.h"
#include "../Component/TestComponent.h"
#include "../GameComponent/GameComponentLib.h"
#include "../Data/Data.h"
#include "../GameComponent/Player/CameraRotateComponent.h"
#include "../GameComponent/EnemyComponent.h"
#include "../GameComponent/BaseObject/EnemyCannonComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void ScenePlay::Initialize(Game * game)
{
	ShowCursor(FALSE);
	game->GetCamera()->SetCameraModel(MyCamera::CAMERA_MODE::GAME);
	// ���f����ǂݍ���
	ModelData* modelData = ModelData::GetInstance();

	// �X�v���C�g�f�[�^�̓ǂݍ���
	SpriteData* spriteData = SpriteData::GetInstance();

	// �I�u�W�F�N�g�̃R���e�i�N���X
	EntityVector* entityVector = EntityVector::GetInstance();

	Entity* entity = nullptr;

	// �Ԃ̃t�@�N�g���̐���
	CarFactory* carFactory = CarFactory::GetInstance();

	// �v���C���[�̍쐬
	// �Ԃ̍쐬
	Entity* player = carFactory->CreateCar(game->GetCamera());

	// �J�����̐ݒ�
	game->GetCamera()->SetPlayer(player);

	// �G
	// ----- �{�f�B�𐶐� -----
	Entity* entity_body = new Entity();
	entity_body->GetTrans().radius.Set(1.5f);

	entity_body->SetName("Enemy");
	entity_body->SetTag(Tag::Player2);
	entity_body->GetTrans().pos.Set(Vector3(0.0f, 3.0f, 5.0f));

	// ���f���R���|�[�l���g�̒ǉ�
	entity_body->AddComponent(new ModelComponent(modelData->GetCarBody(), ModelComponent::Type::Nomal));

	//// �����R���|�[�l���g�̒ǉ�
	PhysicsComponent* physics = new PhysicsComponent();
	physics->SetIsGravity(false);
	physics->SetIsFriction(false);
	entity_body->AddComponent(physics);

	// ���̓����蔻��R���|�[�l���g�̒ǉ�
	entity_body->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 1.5f));

	// �G�R���|�[�l���g��ǉ�
	entity_body->AddComponent(new EnemeyComponent(player));

	// �I�u�W�F�N�g�̌��R���|�[�l���g��ǉ�
	entity_body->AddComponent(new BaseObjectComponent());

	entityVector->Add(entity_body);



	// ----- �C��𐶐� -----
	Entity* entity_cannon = new Entity();
	entity_cannon->GetTrans().pos.Set(Vector3(0.0f, -0.25f, 0.5f));
	entity_cannon->SetName("cannon");

	// �e��ݒ�
	entity_body->AddChild(entity_cannon);

	// ���f���R���|�[�l���g�̒ǉ�
	entity_cannon->AddComponent(new ModelComponent(modelData->GetCarCannon(), ModelComponent::Type::Nomal));

	entity_cannon->AddComponent(new EnemyCannonComponent());

	entityVector->Add(entity_cannon);


	// �����̍쐬
	entity = new Entity();
	entity->SetName("Wall");
	entity->SetTag(Tag::Room);
	entity->GetTrans().radius.Set(200);
	// ���f���R���|�[�l���g�̒ǉ�
	entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// ���b�V���̓����蔻��̒ǉ�
	entity->AddComponent(new MeshCollisionComponent(L"Resources\\Obj\\room.obj"));
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);


	// ���̍쐬
	entity = new Entity();
	entity->SetName("Wall");
	entity->SetTag(Tag::Room);
	entity->GetTrans().radius.Set(15);
	// ���f���R���|�[�l���g�̒ǉ�
	entity->AddComponent(new ModelComponent(modelData->GetSphere(), ModelComponent::Type::Nomal));
	// ���b�V���̓����蔻��̒ǉ�
	entity->AddComponent(new MeshCollisionComponent(L"Resources\\Obj\\sphere.obj"));
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);

	game->GetCamera()->Initialize();
}
