#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"

class StatusComponent;

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class HP_UIComponent : public Component
{
public:
	HP_UIComponent(StatusComponent* status = nullptr);
	~HP_UIComponent();

	// 初期化
	void Initialize() override;
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
	StatusComponent* m_status;
	Entity* m_life[3];

	int m_lastHp;
	int m_time;
	int m_flashTime;
};