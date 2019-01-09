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
}

BulletFactory::~BulletFactory()
{
}

/// <summary>
/// 弾の生成
/// </summary>
/// <returns>生成された弾の中で親となるオブジェクトのポインタを返す</returns>
Entity * BulletFactory::CreateBullet(int num)
{
	ModelData* modelData = ModelData::GetInstance();
	Entity* entity = nullptr;

	entity = new Entity();
	// モデルコンポーネントの追加
	switch (num)
	{
	case 0:
		entity->AddComponent(new ModelComponent(modelData->GetBullet(), ModelComponent::Type::Nomal));
		break;
	case 1:
		entity->AddComponent(new ModelComponent(modelData->GetBullet2(), ModelComponent::Type::Nomal));
		break;
	}
	// 球の当たり判定コンポーネントの追加
	entity->AddComponent(new SphereCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), 0.1f));
	entity->GetTrans().radius.Set(0.4f);
	entity->AddComponent(new BulletComponent());

	return entity;
}


