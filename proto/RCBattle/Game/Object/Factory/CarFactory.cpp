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

#include "../../Component/ComponentLib.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CarFactory::CarFactory()
{
	ModelData* modelData = ModelData::GetInstance();
	m_carModel = modelData->GetCar();
}

CarFactory::~CarFactory()
{
	m_carModel = nullptr;
}

/// <summary>
/// 車の生成
/// </summary>
/// <returns>生成された車の中で親となるオブジェクトのポインタを返す</returns>
Entity* CarFactory::CreateCar()
{
	Entity* entity = new Entity();

	// モデルコンポーネントの追加
	entity->AddComponent(new ModelComponent(m_carModel, ModelComponent::Type::Nomal));
	//// 物理コンポーネントの追加
	PhysicsComponent* physics = new PhysicsComponent();
	////physics->SetIsGravity(false);
	entity->AddComponent(physics);
	// 球の当たり判定コンポーネントの追加
	entity->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 1.5f));

	entity->GetTrans().SetRadius(1.5f);

	return entity;
}
