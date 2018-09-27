#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component/Component.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class EnemeyComponent : public Component
{
public:
	EnemeyComponent();
	~EnemeyComponent();

	// 更新
	void Update(DX::StepTimer const& timer) override;

	// 当たり判定の処理
	void OnCollide(Entity& collide, DirectX::SimpleMath::Vector3& hit_pos) override;

private:
	int count;
};
