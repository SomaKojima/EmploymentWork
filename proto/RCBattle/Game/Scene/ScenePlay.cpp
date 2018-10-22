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
	entity->GetTrans().SetPos(Vector3(0.0f, 3.0f, -5.0f));
	// 入力コンポーネントを追加
	entity->AddComponent(new InputComponent());
	entity->AddComponent(new BaseObjectComponent());

	// コンテナに追加
	entityVector->Add(entity);

	// カメラの設定
	game->GetCamera()->SetPlayer(entity);

	//// 敵
	//// 車の作成
	//entity = carFactory->CreateCar();
	//entity->GetTrans().SetPos(Vector3(0.0f, 1.5f, 10.0f));
	//// コンテナに追加
	//entityVector->Add(entity);

	// 部屋の作成
	entity = new Entity();
	entity->SetName("Room");
	// モデルコンポーネントの追加
	//entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// コンテナに追加
	entityVector->Add(entity);
	
	// 床
	entity = new Entity();
	entity->SetName("Bottom");
	entity->GetTrans().SetRadius(50.0f);
	entity->AddComponent(new PlaneCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(XMConvertToRadians(90.0f), 0.0f, 0.0f), 50, 50));
	entity->AddComponent(new WallComponent(WallType::Bottom));
	// コンテナに追加
	entityVector->Add(entity);

	// 右の壁
	entity = new Entity();
	entity->SetName("Right");
	entity->GetTrans().SetPos(Vector3(5.0f, 0.0f, 0.0f));
	entity->GetTrans().SetRadius(50.0f);
	entity->AddComponent(new PlaneCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, XMConvertToRadians(90.0f), 0.0f), 10, 10));
	entity->AddComponent(new WallComponent(WallType::Right));
	// コンテナに追加
	entityVector->Add(entity);

}
