#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"
#include "../../Data/Data.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class WallComponent : public Component
{
public:
	WallComponent(WallType wallType);
	~WallComponent();

	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(DX::StepTimer const& timer) override;
	// 描画
	void Draw(Game* game) override;
	// 終了
	void Finalize() override;

	// 当たり判定の処理
	void OnCollide(Entity& collide, CollisionData* data) override;

	WallType GetWallType() { return m_wallType; }
	DirectX::SimpleMath::Vector3 GetNomal() { return m_normal; }
	DirectX::SimpleMath::Vector3 GetAngle() { return m_angle; }

private:
	WallType m_wallType;		// 現在どの壁に張り付いているか
	DirectX::SimpleMath::Vector3 m_normal;	// 壁の法線
	DirectX::SimpleMath::Vector3 m_angle;
};