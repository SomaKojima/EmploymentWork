/// <summary>
/// BulletFactory.cpp
/// 
/// 制作日:2018/7/13
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../../pch.h"
#include "BulletFactory.h"
#include "../Entity.h"
#include "../ModelData.h"

#include "../../Component/ComponentLib.h"
#include "../../GameComponent/BulletComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//BulletFactory* BulletFactory::sBulletFactory = nullptr;

BulletFactory::BulletFactory()
{
	ModelData* modelData = ModelData::GetInstance();
	m_bulletModel = modelData->GetBullet();
}

BulletFactory::~BulletFactory()
{
	m_bulletModel = nullptr;
}

/// <summary>
/// 弾の生成
/// </summary>
/// <returns>生成された弾の中で親となるオブジェクトのポインタを返す</returns>
Entity * BulletFactory::CreateBullet()
{
	Entity* entity = nullptr;

	entity = new Entity();
	// モデルコンポーネントの追加
	entity->AddComponent(new ModelComponent(m_bulletModel, ModelComponent::Type::Nomal));
	// 球の当たり判定コンポーネントの追加
	entity->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 0.1f));
	entity->GetTrans().radius.Set(0.4f);
	entity->AddComponent(new BulletComponent());

	return entity;
}


