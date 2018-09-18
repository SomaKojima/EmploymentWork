/// <summary>
/// Collision.cpp
/// 
/// 制作日:2018/7/12
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "Collision.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Component/BoxCollisionComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX::SimpleMath;

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::HitCheck_Sphere(Entity* entity, SphereCollisionComponent& sphere, Entity* entity2, SphereCollisionComponent& sphere2, DirectX::SimpleMath::Vector3* repulsionVel)
{
	Vector3 pos = Vector3::Transform(sphere.GetCenter(), entity->GetTrans().GetWorld());
	Vector3 pos2 = Vector3::Transform(sphere2.GetCenter(), entity2->GetTrans().GetWorld());

	// 中心間の距離の平方を計算
	DirectX::SimpleMath::Vector3 d = pos - pos2;
	float dist2 = d.Dot(d);
	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = sphere.GetRadius() + sphere2.GetRadius();
	if (dist2 < radiusSum * radiusSum)
	{
		if (repulsionVel)
		{
			float l = (sphere.GetRadius() + sphere2.GetRadius()) - sqrtf(dist2);
			d.Normalize();
			*repulsionVel += (d * l);
		}
		return true;
	}
	return false;
}

/// <summary>
/// 当たり判定を求める
/// </summary>
/// <param name="entity">実体</param>
/// <param name="repulsionVel">反発速度</param>
/// <returns>当たり判定</returns>
bool Collision::HitCheck(Entity * entity, Entity* entity2, Vector3* repulsionVel)
{
	if(!entity || !entity2)
	{
		return false;
	}
	SphereCollisionComponent* sphereCollision = entity->GetComponent<SphereCollisionComponent>();
	SphereCollisionComponent* sphereCollision2 = entity2->GetComponent<SphereCollisionComponent>();

	if (sphereCollision && sphereCollision2)
	{
		return HitCheck_Sphere(entity, *sphereCollision, entity2, *sphereCollision2, repulsionVel);
	}

	return false;
}
