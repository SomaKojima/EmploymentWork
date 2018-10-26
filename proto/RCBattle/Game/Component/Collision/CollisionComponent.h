/// <summary>
/// CollisionComponent.h
/// 
/// 制作日:2018/10/26
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component.h"
#include "../../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent():isHit(false) {};
	~CollisionComponent() {};

	// 更新
	void Update(DX::StepTimer const& timer) override;

	// 壁ずり等の処理
	template<class T>
	void HitBackExecution(T* info, DirectX::SimpleMath::Vector3& hitPos);

	virtual void HitBack(Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(Collision::Sphere* sphere, DirectX::SimpleMath::Vector3& hitPos) {};

	void SetHit(bool flag) { isHit = flag; }
	bool IsHit() { return isHit; }
private:
	bool isHit;
};

template<class T>
inline void CollisionComponent::HitBackExecution(T * info, DirectX::SimpleMath::Vector3 & hitPos)
{
	if (isHit)
	{
		HitBack(info, hitPos);
	}
}
