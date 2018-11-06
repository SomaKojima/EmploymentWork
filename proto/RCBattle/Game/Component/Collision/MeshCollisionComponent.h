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
#include <list>
#include "CollisionComponent.h"
#include "../../DebugCollision/DebugMesh.h"
#include "../../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class MeshCollisionComponent : public CollisionComponent
{
public:
	MeshCollisionComponent(wchar_t* file);
	~MeshCollisionComponent();

	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(DX::StepTimer const& timer) override;
	// 描画
	void Draw(Game* game) override;
	// 終了
	void Finalize() override;

	const std::list<Collision::Triangle>* GetTriangleList() override { return &m_triangles; }

	Collision::CollisionType GetShapeType() { return Collision::CollisionType::TRIANGLE; }

private:
	wchar_t* m_file;
	std::list<Collision::Triangle> m_triangles;

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugMesh> m_obj;
};