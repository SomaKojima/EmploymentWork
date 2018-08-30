/// <summary>
/// Collision.h
/// 
/// 制作日:2018/7/12
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Object/Entity.h"

/// <summary>
/// 前方宣言
/// </summary>
class SphereCollisionComponent;
class BoxCollisionComponent;

/// <summary>
/// 当たり判定クラス
/// </summary>
class Collision
{
protected:
	Collision();
	~Collision();
	static bool HitCheck_Sphere(Entity* entity, SphereCollisionComponent& sphere, Entity* entity2, SphereCollisionComponent& sphere2, DirectX::SimpleMath::Vector3* repulsionVel = nullptr);

public:
	static bool HitCheck(Entity* entity, Entity* entity2, DirectX::SimpleMath::Vector3* repulsionVel = nullptr);
};
