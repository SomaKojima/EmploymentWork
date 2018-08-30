/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "SphereCollisionComponent.h"
#include "BoxCollisionComponent.h"

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
SphereCollisionComponent::SphereCollisionComponent(DirectX::SimpleMath::Vector3 center, float radius)
	:
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_name = "SphereCollision";
}

/// <summary>
/// デストラクタ
/// </summary>
SphereCollisionComponent::~SphereCollisionComponent()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="entity">実体</param>
void SphereCollisionComponent::Initialize(Entity & entity)
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
/// <param name="timer">時間</param>
void SphereCollisionComponent::Update(Entity & entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="m_entity">実体</param>
/// <param name="timer">時間</param>
void SphereCollisionComponent::LateUpdate(Entity & entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void SphereCollisionComponent::Draw(Entity & entity, Game * game)
{
	Matrix world = entity.GetWorld() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugSphere>(game->GetDevice(), m_center, m_radius);
	}
	else
	{
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// 終了
/// </summary>
/// <param name="entity">実体</param>
void SphereCollisionComponent::Finalize(Entity & entity)
{
	m_obj.reset();
}