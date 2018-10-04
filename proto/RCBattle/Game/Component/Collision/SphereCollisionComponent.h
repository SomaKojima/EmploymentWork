/// <summary>
/// SphereCollisionComponent.h
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
#include "../Component.h"
#include "../../DebugCollision/DebugSphere.h"
#include "../../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class SphereCollisionComponent : public Component
{
public:
	SphereCollisionComponent(DirectX::SimpleMath::Vector3 center, float radius);
	~SphereCollisionComponent();

	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(DX::StepTimer const& timer) override;
	// 描画
	void Draw(Game* game) override;
	// 終了
	void Finalize() override;

	DirectX::SimpleMath::Vector3 HitPlanePosToVec(PlaneCollisionComponent* plane, DirectX::SimpleMath::Vector3& hitPos);

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	float GetRadius() { return m_radius; }
	Collision::Sphere& GetSphere(){ return m_sphere; }
private:
	DirectX::SimpleMath::Vector3 m_center; // 球の中心
	float m_radius;   // 球の半径
	Collision::Sphere m_sphere;

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugSphere> m_obj;
};
