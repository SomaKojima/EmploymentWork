/// <summary>
/// CarFactory.cpp
/// 
/// 制作日:2018/7/13
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../../pch.h"
#include "CarFactory.h"
#include "../Entity.h"
#include "../ModelData.h"
#include "../EntityVector.h"

#include "../../Component/ComponentLib.h"
#include "../../GameComponent/Player/PlayerCannonComponent.h"
#include "../../GameComponent/Player/CameraRotateComponent.h"
#include "../../GameComponent/BaseObject/BaseObjectComponent.h"
#include "../../GameComponent/BaseObject/flowComponent.h"
#include "../../GameComponent/BaseObject/StatusComponent.h"


/// <summary>
/// 名前空間
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CarFactory::CarFactory()
{
	ModelData* modelData = ModelData::GetInstance();
	m_carBodyModel = modelData->GetCarBody();
	m_carCannonModel = modelData->GetCarCannon();
}

CarFactory::~CarFactory()
{
	m_carBodyModel = nullptr;
	m_carCannonModel = nullptr;
}

/// <summary>
/// 車の生成
/// </summary>
/// <returns>生成された車の中で親となるオブジェクトのポインタを返す</returns>
Entity* CarFactory::CreateCar(MyCamera* camera)
{

	EntityVector* entityVector = EntityVector::GetInstance();


	// ----- ボディを生成 -----
	Entity* entity_body = new Entity();
	entity_body->GetTrans().radius.Set(1.5f);

	entity_body->SetName("Player");
	entity_body->SetTag(Tag::Player1);
	entity_body->GetTrans().pos.Set(Vector3(0.0f, 3.0f, -5.0f));

	// モデルコンポーネントの追加
	entity_body->AddComponent(new ModelComponent(m_carBodyModel, ModelComponent::Type::Nomal));

	//// 物理コンポーネントの追加
	PhysicsComponent* physics = new PhysicsComponent();
	physics->SetIsGravity(false);
	physics->SetIsFriction(false);
	entity_body->AddComponent(physics);

	// 球の当たり判定コンポーネントの追加
	entity_body->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 1.5f));

	// 入力コンポーネントを追加
	entity_body->AddComponent(new InputComponent());

	// オブジェクトの元コンポーネントを追加
	entity_body->AddComponent(new BaseObjectComponent());

	// カメラの操作コンポーネントを追加
	entity_body->AddComponent(new CameraRotateComponent(camera, CameraRotateComponent::Type::Vertical));

	// 浮遊コンポーネントを追加
	//entity_body->AddComponent(new FlowComponent());

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
	entity_cannon->AddComponent(new ModelComponent(m_carCannonModel, ModelComponent::Type::Nomal));

	// 大砲のコンポーネントの追加
	entity_cannon->AddComponent(new PlayerCannonComponent(camera));

	entityVector->Add(entity_cannon);

	return entity_body;
}
