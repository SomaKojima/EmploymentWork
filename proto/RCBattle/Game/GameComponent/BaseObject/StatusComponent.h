#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class StatusComponent : public Component
{
public:
	StatusComponent();
	~StatusComponent();

	// 初期化
	//void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 遅延更新
	//void LateUpdate(DX::StepTimer const& timer) override;
	// 描画
	//void Draw(Game* game) override;
	// 終了
	//void Finalize() override;

	// 当たり判定の処理
	void OnCollide(Entity& collide, Collision::CollisionData* data) override;

	int GetHP() { return m_hp; }

private:
	int m_hp;
};

