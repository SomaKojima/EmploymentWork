#include "../../pch.h"
#include "ScenePlay.h"
#include "../Object/ModelData.h"
#include "../Object/SpriteData.h"
#include "../Object/EntityVector.h"
#include "../Object/Entity.h"

using namespace std;
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
	entity->GetTrans().SetTrans(Vector3(0.0f, 2.0f, 0.0f));
	// ���̓R���|�[�l���g��ǉ�
	entity->AddComponent(new InputComponent());
	entity->SetName("Player");
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);

	// �J�����̐ݒ�
	game->GetCamera()->SetPlayer(entity);

	// �G
	// �Ԃ̍쐬
	entity = carFactory->CreateCar();
	entity->GetTrans().SetTrans(Vector3(0.0f, 2.0f, 10.0f));
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);

	// �����̍쐬
	entity = new Entity();
	// ���f���R���|�[�l���g�̒ǉ�
	entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// ���̓����蔻��R���|�[�l���g�̒ǉ�
	//entity->AddComponent(new BoxCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f,1.0f,1.0f)));
	entity->AddComponent(new PlaneCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 2, 1));
	entity->GetTrans().SetTrans(Vector3(0.0f, 0.0f, 3.0f));
	// �R���e�i�ɒǉ�
	entityVector->Add(entity);
}
