/// <summary>
/// InputComponent.h
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <list>
#include "../Component.h"

/// <summary>
/// 前方宣言
/// </summary>
class SphereCollisionComponent;
class BoxCollisionComponent;
class PlaneCollisionComponent;

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(DX::StepTimer const& timer) override;
	// 当たり判定の処理
	void OnCollide(Entity& collide, CollisionData* data) override;

	//SphereCollisionComponent* GetSphereCollision() { return sphere; }
	//BoxCollisionComponent* GetBoxCollision() { return box; }

	void SetIsFriction(bool isFriction) { m_isFriction = isFriction; }
	void SetIsGravity(bool isGravity) { m_isGravity = isGravity; }

private:
	float m_gravity;	// 重力
	bool m_isFriction;	// 摩擦
	bool m_isGravity;	// 重力のフラグ

	std::list<SphereCollisionComponent*> m_spherelist;
	std::list<PlaneCollisionComponent*> m_planelist;
};