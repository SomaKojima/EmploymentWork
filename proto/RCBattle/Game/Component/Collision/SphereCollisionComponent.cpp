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
		//m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
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
	Vector3 vec = Vector3::Transform(m_me->GetTrans().GetVel(), m_me->GetTrans().GetDir());
	
	/*float radian_xy = atan2(plane->GetTriangle()->plane.b, plane->GetTriangle()->plane.a);
	float radian_xz = atan2(plane->GetTriangle()->plane.c, plane->GetTriangle()->plane.a);
*/
	//// 仰角
	//float phi = (radian_xy)* XM_PI / 180;
	//// 方位角
	//float theta = (radian_xz - 180) * XM_PI / 180;

	//float radian = 1;

	//float x = -radian * cos(phi) * cos(theta);
	//float y = radian * sin(phi);
	//float z = radian * cos(phi) * sin(theta);

	//Quaternion dir = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), -z) *
	//	Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), -y) *
	//	Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), -x);

	//vec = Vector3::Transform(vec, dir);

	//vec = Vector3(plane->GetTriangle()->plane.a * vec.x, plane->GetTriangle()->plane.b * vec.y, plane->GetTriangle()->plane.c * vec.z);
	//Vector3 world = m_me->GetTrans().GetWorld().Translation() + vec;
	//m_me->GetTrans().SetPos(world);

	return DirectX::SimpleMath::Vector3();
}

