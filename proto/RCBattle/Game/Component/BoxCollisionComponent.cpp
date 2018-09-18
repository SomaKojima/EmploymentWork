/// <summary>
/// BoxCollisionComponent.cpp
/// 
/// 制作日:2018/7/12
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "BoxCollisionComponent.h"
#include "SphereCollisionComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BoxCollisionComponent::BoxCollisionComponent(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 radius)
	:
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_name = "BoxCollision";
}

/// <summary>
/// デストラクタ
/// </summary>
BoxCollisionComponent::~BoxCollisionComponent()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="entity">実体</param>
void BoxCollisionComponent::Initialize(Entity & entity)
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
/// <param name="timer">時間</param>
void BoxCollisionComponent::Update(Entity & entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="m_entity">実体</param>
/// <param name="timer">時間</param>
void BoxCollisionComponent::LateUpdate(Entity & m_entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void BoxCollisionComponent::Draw(Entity & entity, Game * game)
{
	Matrix world = entity.GetTrans().GetWorld() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugBox>(game->GetDevice(), m_center, m_radius);
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
void BoxCollisionComponent::Finalize(Entity & entity)
{
}