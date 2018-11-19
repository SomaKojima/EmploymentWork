#include "../../pch.h"
#include "SceneTitle.h"
#include "../Object/ModelData.h"
#include "../Object/SpriteData.h"
#include "../Object/EntityVector.h"
#include "../Object/Entity.h"

#include "../GameComponent/Button/StartButton.h"
#include "../GameComponent/Button/ButtonComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void SceneTitle::Initialize(Game * game)
{
	game->GetCamera()->SetCameraModel(MyCamera::CAMERA_MODE::TITLE);
	// モデルを読み込む
	ModelData* modelData = ModelData::GetInstance();

	// スプライトデータの読み込み
	SpriteData* spriteData = SpriteData::GetInstance();

	// オブジェクトのコンテナクラス
	EntityVector* entityVector = EntityVector::GetInstance();

	Entity* entity = nullptr;

	// スタートボタン
	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetTitleLogo(), RECT{ 0, 0, 500, 300 }));
	entity->GetTrans().SetPos(Vector3(150.0f, 50.0f, 0.0f));
	entityVector->Add(entity);

	// スタートボタン
	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetButton(), RECT{ 0, 0, 300, 100 }));
	ButtonComponent* button = new ButtonComponent();
	StartButton* start = new StartButton();
	button->AddFunc(start);
	entity->AddComponent(button);
	entity->GetTrans().SetPos(Vector3(250.0f, 400.0f, 0.0f));
	entityVector->Add(entity);

	// 背景
	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetTitleBG(), RECT{ 0, 0, 800, 600 }));
	entityVector->Add(entity);

}
