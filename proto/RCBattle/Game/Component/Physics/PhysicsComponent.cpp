/// <summary>
/// PhysicsComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../../pch.h"
#include "PhysicsComponent.h"
#include "../../Collision/Collision.h"

#include "../ComponentLib.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="entityVector">実体のコンテナのポインタ</param>
PhysicsComponent::PhysicsComponent()
	:
	m_gravity(9.8f),
	m_isFriction(true),
	m_isGravity(true)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PhysicsComponent::~PhysicsComponent()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="entity">実体</param>
void PhysicsComponent::Initialize()
{
	m_spherelist = m_me->GetComponentList<SphereCollisionComponent>();
	m_planelist = m_me->GetComponentList<PlaneCollisionComponent>();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
/// <param name="timer">時間</param>
void PhysicsComponent::Update(DX::StepTimer const& timer)
{
	Vector3 vel = m_me->GetTrans().GetVel();
	vel *= 0.9f;
	/*if(m_isFriction)
	{
		vel.x *= 0.9f;
		vel.z *= 0.9f;
	}
	if(m_isGravity)
	{
		vel.y -= (m_gravity / (60 * 60));
	}*/

	Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().GetWorld()) + vel;
	/*if (pos.y <= 1.5f)
	{
		m_me->GetTrans().SetWorld(m_me->GetTrans().GetWorld() * Matrix::CreateTranslation(Vector3(0.0f, -pos.y + 1.5f, 0.0f)));
		vel.y = 0.0f;
	}
*/
	m_me->GetTrans().SetVel(vel);
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="m_entity">実体</param>
/// <param name="timer">時間</param>
void PhysicsComponent::LateUpdate(DX::StepTimer const & timer)
{
	/*Vector3 pos = m_me->GetTrans().GetPos();

	pos += m_repulsionVel;
	m_me->GetTrans().SetPos(pos);
	m_repulsionVel = Vector3::Zero;*/
}

void PhysicsComponent::OnCollide(Entity& collide, CollisionData* data)
{
	// 向いている向きに変えた速度
	switch (data->type)
	{
	case CollisionType::SPHERE_PLANE:

		break;
	}
	Vector3 vel = Vector3::Transform(m_me->GetTrans().GetVel(), m_me->GetTrans().GetDir());
	Vector3 pos = Vector3::Transform(vel, m_me->GetTrans().GetWorld());
}