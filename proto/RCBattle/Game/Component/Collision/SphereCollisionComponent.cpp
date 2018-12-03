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
	m_sphere.radius = radius;
}

/// <summary>
/// デストラクタ
/// </summary>
SphereCollisionComponent::~SphereCollisionComponent()
{

}

void SphereCollisionComponent::Update(DX::StepTimer const & timer)
{
	CollisionComponent::Update(timer);
}

void SphereCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
	m_sphere.center = Vector3::Transform(m_center, (m_me->GetTrans().world.Get()));
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void SphereCollisionComponent::Draw(Game * game)
{
	Matrix world = m_me->GetTrans().world.Get() * Matrix::CreateTranslation(m_center);
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
void SphereCollisionComponent::Finalize()
{
	m_obj.reset();
}

void SphereCollisionComponent::HitBack(const Collision::Triangle * triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// 速度を取得
	Vector3 vec = m_me->GetTrans().vel.GetLocal();

	// 面の法線
	Vector3 normal(triangle->plane.a, triangle->plane.b, triangle->plane.c);

	// 法線の向きのベクトルをなくす(プレイヤーの向きに合わせる・ローカル座標にする)
	Quaternion q;
	m_me->GetTrans().dir.Get().Conjugate(q);

	// 壁ずり
	Vector3 normal2 = Vector3::Transform(normal, q);

	float l = vec.Dot(normal2);
	Vector3 w_vec;
	if (l <= 0)
	{
		w_vec = vec - l * normal2;
	}
	else
	{
		w_vec = vec;
	}

	// 座標の更新
	Vector3 pos = m_me->GetTrans().pos.Get();
	pos += Vector3::Transform(w_vec, m_me->GetTrans().dir.Get());

	//m_me->GetTrans().SetPos(pos);

	m_me->GetTrans().vel.SetLocal(w_vec);
}

