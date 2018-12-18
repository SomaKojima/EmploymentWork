#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <list>
#include "../../Component/Component.h"
#include "../../Data/Data.h"

class Entity;

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class FlowComponent : public Component
{
public:
	FlowComponent();
	~FlowComponent();

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
	//void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
	float m_angle;
	int m_count;
};

