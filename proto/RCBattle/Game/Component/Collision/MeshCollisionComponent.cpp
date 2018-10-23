/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../../pch.h"
#include "MeshCollisionComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="radius">半径</param>
MeshCollisionComponent::MeshCollisionComponent(wchar_t* file)
	:
	m_file(file)
{
}

/// <summary>
/// デストラクタ
/// </summary>
MeshCollisionComponent::~MeshCollisionComponent()
{
}

void MeshCollisionComponent::Update(DX::StepTimer const & timer)
{
}

void MeshCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void MeshCollisionComponent::Draw(Game * game)
{
	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugMesh>(game->GetDevice(), m_file);
	}
	else
	{
		m_obj->DrawCollision(game->GetContext(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// 終了
/// </summary>
/// <param name="entity">実体</param>
void MeshCollisionComponent::Finalize()
{
	m_obj.reset();
}