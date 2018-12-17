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

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void ScenePlay::Initialize(Game * game)
{
	ShowCursor(FALSE);
	game->GetCamera()->SetCameraModel(MyCamera::CAMERA_MODE::GAME);
	// モデルを読み込む
	ModelData* modelData = ModelData::GetInstance();

	// スプライトデータの読み込み
	SpriteData* spriteData = SpriteData::GetInstance();

	// オブジェクトのコンテナクラス
	EntityVector* entityVector = EntityVector::GetInstance();

	Entity* entity = nullptr;

	// 車のファクトリの生成
	CarFactory* carFactory = CarFactory::GetInstance();

	// プレイヤーの作成
	// 車の作成
	entity = carFactory->CreateCar(); 
	entity->SetName("Player");
	entity->SetTag(Tag::Player1);
	entity->GetTrans().pos.Set(Vector3(0.0f, 3.0f, -5.0f));
	// 入力コンポーネントを追加
	entity->AddComponent(new InputComponent());
	entity->AddComponent(new BaseObjectComponent());
	entity->AddComponent(new CameraRotateComponent(game->GetCamera()));

	// コンテナに追加
	entityVector->Add(entity);

	// カメラの設定
	game->GetCamera()->SetPlayer(entity);

	// 敵
	// 車の作成
	entity = carFactory->CreateCar();
	entity->GetTrans().pos.Set(Vector3(0.0f, 1.5f, 10.0f));
	entity->SetTag(Tag::Player2);
	entity->AddComponent(new BaseObjectComponent());
	entity->AddComponent(new EnemeyComponent());
	// コンテナに追加
	entityVector->Add(entity);

	// 部屋の作成
	entity = new Entity();
	entity->SetName("Wall");
	entity->GetTrans().radius.Set(200);
	// モデルコンポーネントの追加
	entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// メッシュの当たり判定の追加
	entity->AddComponent(new MeshCollisionComponent(L"Resources\\Obj\\room.obj"));
	// コンテナに追加
	entityVector->Add(entity);

	game->GetCamera()->Initialize();
}
