#include "../../pch.h"
#include "ScenePlay.h"
#include "../Data/Data.h"
#include "../Object/ModelData.h"
#include "../Object/SpriteData.h"
#include "../Object/EntityVector.h"
#include "../Object/Entity.h"
#include "../Component/TestComponent.h"
#include "../GameComponent/GameComponentLib.h"
#include "../GameComponent/Player/CameraRotateComponent.h"
#include "../GameComponent/Player/HP_UIComponent.h"
#include "../GameComponent/Enemy/EnemyComponent.h"
#include "../GameComponent/Enemy/EnemyCannonComponent.h"
#include "../GameComponent/BaseObject/StatusComponent.h"
#include "../GameComponent/Play/GameJudgeComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void ScenePlay::Initialize(Game * game)
{
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
	Entity* player = carFactory->CreateCar(game->GetCamera());

	// カメラの設定
	game->GetCamera()->SetPlayer(player);

	// 敵
	// ----- ボディを生成 -----
	Entity* entity_body = new Entity();
	entity_body->GetTrans().radius.Set(1.5f);

	entity_body->SetName("Enemy");
	entity_body->SetTag(Tag::Player2);
	entity_body->GetTrans().pos.Set(Vector3(0.0f, 3.0f, 5.0f));

	// モデルコンポーネントの追加
	entity_body->AddComponent(new ModelComponent(modelData->GetCarBody(), ModelComponent::Type::Nomal));

	//// 物理コンポーネントの追加
	PhysicsComponent* physics = new PhysicsComponent();
	physics->SetIsGravity(false);
	physics->SetIsFriction(false);
	entity_body->AddComponent(physics);

	// 球の当たり判定コンポーネントの追加
	entity_body->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 1.5f));

	// 敵コンポーネントを追加
	entity_body->AddComponent(new EnemeyComponent(player));

	// オブジェクトの元コンポーネントを追加
	entity_body->AddComponent(new BaseObjectComponent());

	// ステータスコンポーネントを追加
	entity_body->AddComponent(new StatusComponent());

	entityVector->Add(entity_body);



	// ----- 砲台を生成 -----
	Entity* entity_cannon = new Entity();
	entity_cannon->GetTrans().pos.Set(Vector3(0.0f, -0.25f, 0.5f));
	entity_cannon->SetName("cannon");

	// 親を設定
	entity_body->AddChild(entity_cannon);

	// モデルコンポーネントの追加
	entity_cannon->AddComponent(new ModelComponent(modelData->GetCarCannon(), ModelComponent::Type::Nomal));

	entity_cannon->AddComponent(new EnemyCannonComponent());

	entityVector->Add(entity_cannon);


	// 部屋の作成
	entity = new Entity();
	entity->SetName("Wall");
	entity->SetTag(Tag::Room);
	entity->GetTrans().radius.Set(200);
	// モデルコンポーネントの追加
	entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// メッシュの当たり判定の追加
	entity->AddComponent(new MeshCollisionComponent(L"Resources\\Obj\\room.obj"));
	// コンテナに追加
	entityVector->Add(entity);


	//// 球の作成
	//entity = new Entity();
	//entity->SetName("Wall");
	//entity->SetTag(Tag::Room);
	//entity->GetTrans().radius.Set(15);
	//// モデルコンポーネントの追加
	//entity->AddComponent(new ModelComponent(modelData->GetSphere(), ModelComponent::Type::Nomal));
	//// メッシュの当たり判定の追加
	//entity->AddComponent(new MeshCollisionComponent(L"Resources\\Obj\\sphere.obj"));
	//// コンテナに追加
	//entityVector->Add(entity);


	// マーク
	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetMark(), RECT{ 0, 0, 50, 50 }));
	entity->GetTrans().pos.Set(Vector2(400 - 25, 300 - 25));
	entityVector->Add(entity);


	// HP_UI
	entity = new Entity();
	entity->AddComponent(new HP_UIComponent(player->GetComponent<StatusComponent>()));
	entity->GetTrans().pos.Set(Vector3(0.0f, 500.0f, 0.0f));
	entityVector->Add(entity);

	// 試合の判定
	entity = new Entity();
	entity->AddComponent(new GameJudgeComponent(game->GetCamera()));
	entityVector->Add(entity);


	// カメラの初期化
	game->GetCamera()->Initialize();

	// マウスの非表示
	while (ShowCursor(FALSE) >= 0);
}
