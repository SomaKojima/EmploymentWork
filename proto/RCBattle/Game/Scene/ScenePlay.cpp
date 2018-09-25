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
	entity->GetTrans().SetTrans(Vector3(0.0f, 2.0f, 0.0f));
	// 入力コンポーネントを追加
	entity->AddComponent(new InputComponent());
	entity->SetName("Player");
	// コンテナに追加
	entityVector->Add(entity);

	// カメラの設定
	game->GetCamera()->SetPlayer(entity);

	// 敵
	// 車の作成
	entity = carFactory->CreateCar();
	entity->GetTrans().SetTrans(Vector3(0.0f, 2.0f, 10.0f));
	// コンテナに追加
	entityVector->Add(entity);

	// 部屋の作成
	entity = new Entity();
	// モデルコンポーネントの追加
	entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// 球の当たり判定コンポーネントの追加
	//entity->AddComponent(new BoxCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f,1.0f,1.0f)));
	entity->AddComponent(new PlaneCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 2, 1));
	entity->GetTrans().SetTrans(Vector3(0.0f, 0.0f, 3.0f));
	// コンテナに追加
	entityVector->Add(entity);
}
