#include "../../pch.h"
#include "ScenePlay.h"
#include "../Object/ModelData.h"
#include "../Object/SpriteData.h"
#include "../Object/EntityVector.h"
#include "../Object/Entity.h"
#include "../Component/TestComponent.h"
#include "../GameComponent/GameComponentLib.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void ScenePlay::Initialize(Game * game)
{
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
	entity = carFactory->CreateCar(); 
	entity->SetName("Player");
	entity->GetTrans().SetPos(Vector3(0.0f, 3.0f, -5.0f));
	// ���̓R���|�[�l���g��ǉ�
	entity->AddComponent(new InputComponent());
	entity->AddComponent(new BaseObjectComponent());

	// �R���e�i�ɒǉ�
	entityVector->Add(entity);

	// �J�����̐ݒ�
	game->GetCamera()->SetPlayer(entity);

	//// �G
	//// �Ԃ̍쐬
	//entity = carFactory->CreateCar();
	//entity->GetTrans().SetPos(Vector3(0.0f, 1.5f, 10.0f));
	//// �R���e�i�ɒǉ�
	//entityVector->Add(entity);

	// �����̍쐬
	entity = new Entity();
	entity->SetName("Room");
	// ���f���R���|�[�l���g�̒ǉ�
	//entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);
	
	// ��
	entity = new Entity();
	entity->SetName("Bottom");
	entity->GetTrans().SetRadius(50.0f);
	entity->AddComponent(new PlaneCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(XMConvertToRadians(90.0f), 0.0f, 0.0f), 50, 50));
	entity->AddComponent(new WallComponent(WallType::Bottom));
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);

	// �E�̕�
	entity = new Entity();
	entity->SetName("Right");
	entity->GetTrans().SetPos(Vector3(5.0f, 0.0f, 0.0f));
	entity->GetTrans().SetRadius(50.0f);
	entity->AddComponent(new PlaneCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, XMConvertToRadians(90.0f), 0.0f), 10, 10));
	entity->AddComponent(new WallComponent(WallType::Right));
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);

}
