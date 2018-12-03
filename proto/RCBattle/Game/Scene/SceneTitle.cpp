#include "../../pch.h"
#include "SceneTitle.h"
#include "../Object/ModelData.h"
#include "../Object/SpriteData.h"
#include "../Object/EntityVector.h"
#include "../Object/Entity.h"
#include "../Data/Data.h"

#include "../GameComponent/Button/StartButton.h"
#include "../GameComponent/Button/ButtonComponent.h"

#include "../GameComponent/Title/LineOfSightComponent.h"
#include "../GameComponent/Title/ShotComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void SceneTitle::Initialize(Game * game)
{
	game->GetCamera()->SetCameraModel(MyCamera::CAMERA_MODE::TITLE);
	// ���f����ǂݍ���
	ModelData* modelData = ModelData::GetInstance();

	// �X�v���C�g�f�[�^�̓ǂݍ���
	SpriteData* spriteData = SpriteData::GetInstance();

	// �I�u�W�F�N�g�̃R���e�i�N���X
	EntityVector* entityVector = EntityVector::GetInstance();

	Entity* entity = nullptr;

	//// �^�C�g�����S
	//entity = new Entity();
	//entity->AddComponent(new UIRenderer(spriteData->GetTitleLogo(), RECT{ 0, 0, 500, 300 }));
	//entity->GetTrans().SetPos(Vector3(150.0f, 50.0f, 0.0f));
	//entityVector->Add(entity);

	// ��
	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetTitleCar(), RECT{ 0,0,300,300 }, 0.1f));
	int time = 60;
	entity->AddComponent(new LineOfSightComponent(Vector3(400.0f, 50.0f, 0.0f), time));
	entity->AddComponent(new ShotComponent(time));
	entity->GetTrans().SetPos(Vector3(600.0f, 20.0f, 0.0f));
	entityVector->Add(entity);

	// �X�^�[�g�{�^��
	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetButton(), RECT{ 0, 0, 300, 100 }, 0.1f));
	ButtonComponent* button = new ButtonComponent();
	StartButton* start = new StartButton();
	button->AddFunc(start);
	entity->AddComponent(button);
	entity->GetTrans().SetPos(Vector3(250.0f, 400.0f, 0.0f));
	entityVector->Add(entity);

	// �w�i
	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetTitleBG(), RECT{ 0, 0, 800, 600 }));
	entityVector->Add(entity);
}
