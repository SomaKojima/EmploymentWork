#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component/Component.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class HPComponent : public Component
{
public:
	HPComponent();
	~HPComponent();

	// 更新
	void Update(Entity& entity, DX::StepTimer const& timer) override;

	// 当たり判定の処理
	void OnCollide(Entity& entity, Entity& collide) override;

	void sethp(int hP) { hp = hP; }
	int GetHp() { return hp; }
private:
	int hp;
	int atk;
};