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
#include "Component.h"
#include "../DebugCollision/DebugSphere.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class SphereCollisionComponent : public Component
{
public:
	SphereCollisionComponent(DirectX::SimpleMath::Vector3 center, float radius);
	~SphereCollisionComponent();

	// 初期化
	void Initialize(Entity & entity) override;
	// 更新
	void Update(Entity& entity, DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(Entity& entity, DX::StepTimer const& timer) override;
	// 描画
	void Draw(Entity & entity, Game* game) override;
	// 終了
	void Finalize(Entity & entity) override;

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	float GetRadius() { return m_radius; }
private:
	DirectX::SimpleMath::Vector3 m_center; // 球の中心
	float m_radius;   // 球の半径

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugSphere> m_obj;
};
