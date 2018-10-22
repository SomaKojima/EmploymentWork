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
}

void SphereCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
	m_sphere.center = Vector3::Transform(m_center, (m_me->GetTrans().GetWorld()));
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void SphereCollisionComponent::Draw(Game * game)
{
	Matrix world = m_me->GetTrans().GetWorld() * Matrix::CreateTranslation(m_center);
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

DirectX::SimpleMath::Vector3 SphereCollisionComponent::HitPlanePosToVec(PlaneCollisionComponent* plane, DirectX::SimpleMath::Vector3& hitPos)
{
	// 速度を取得
	Vector3 vec = m_me->GetTrans().GetVel();
	//Vector3 accel = m_me->GetTrans().GetAccel();

	// 面の法線
	Vector3 normal(plane->GetTriangle()->plane.a, plane->GetTriangle()->plane.b, plane->GetTriangle()->plane.c);

	// 法線の向きのベクトルをなくす
	Quaternion q;
	m_me->GetTrans().GetDir().Conjugate(q);

	// めり込み押し出し
	/*Vector3 hitPosVec = m_sphere.center - hitPos;
	hitPosVec.Normalize();
	Vector3 a = m_sphere.center - (hitPosVec * m_sphere.radius) - hitPos;
	float length = a.Length();
	Vector3 vel = length * normal;
	Vector3 pos = m_me->GetTrans().GetPos() + vel;
	vel = Vector3::Transform(vel, q);*/

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

	m_me->GetTrans().SetVel(w_vec);

	// 壁にひっつく
	return Vector3::Zero;
}

