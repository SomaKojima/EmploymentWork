#include "../../pch.h"
#include "SceneTitle.h"
#include "../Object/ModelData.h"
#include "../Object/SpriteData.h"
#include "../Object/EntityVector.h"
#include "../Object/Entity.h"

#include "../GameComponent/Button/StartButtonComponent.h"
#include "../GameComponent/Button/ButtonComponent.h"

using namespace std;
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

	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetSprite(), RECT{0, 0, 100, 100}));
	ButtonComponent* button = new ButtonComponent();
	entity->AddComponent(button);

	StartButtonComponent* start = new StartButtonComponent();
	entity->AddComponent(start);
	button->AddFunc(start);

	entityVector->Add(entity);
}
