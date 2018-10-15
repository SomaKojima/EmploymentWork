#include "../../../pch.h"
#include "BaseObjectComponent.h"
#include "../GameComponentLib.h"
#include "../../Object/EntityVector.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

BaseObjectComponent::BaseObjectComponent()
	:
	m_normal(Vector3::Down)
{
}

BaseObjectComponent::~BaseObjectComponent()
{
}

void BaseObjectComponent::Initialize()
{
	EntityVector* entityVector = EntityVector::GetInstance();
	Entity* wall = entityVector->GetEntity("Bottom");
}

void BaseObjectComponent::Update(DX::StepTimer const & timer)
{
	// 現在接している壁が前フレームと同じかどうか調べる
	bool isWall = true;
	auto ite2 = m_last.begin();
	for (auto ite = m_current.begin(); ite != m_current.end(); ite++)
	{
		if (ite2 == m_last.end())
		{
			isWall = false;
			break;
		}
		if ((*ite) != (*ite2))
		{
			isWall = false;
			break;
		}
		ite2++;
	}

	// 壁が同じ出ない場合、重力の向きを計算し直す
	if (!isWall)
	{
		m_normal = Vector3::Zero;
		if (m_current.begin() == m_current.end())
		{
			m_current = m_last;
		}
		for (auto ite = m_current.begin(); ite != m_current.end(); ite++)
		{
			m_normal += (*ite)->GetNomal();
		}
		if (m_normal == Vector3::Zero)
		{
			m_normal = Vector3::Down;
		}
		m_normal.Normalize();
	}

	// 重力の計算
	Vector3 vec = m_me->GetTrans().GetVel();

	m_last = m_current;
	m_current.clear();
}

void BaseObjectComponent::LateUpdate(DX::StepTimer const & timer)
{
	Vector3 gravityVec = m_normal * (9.8f / (60 * 60));
	Vector3 vec = m_me->GetTrans().GetVel();
	// 摩擦
	vec *= Vector3(0.9f, 1.0f, 0.9f);
	// 重力
	vec += gravityVec;
	Vector3 vel = Vector3::Transform(vec, m_me->GetTrans().GetDir());
	Vector3 pos;

	m_me->GetTrans().SetVel(vec);
}

void BaseObjectComponent::Draw(Game * game)
{
}

void BaseObjectComponent::Finalize()
{
}

void BaseObjectComponent::OnCollide(Entity & collide, CollisionData * data)
{
	WallComponent* wall = collide.GetComponent<WallComponent>();
	
	if (wall)
	{
		m_current.push_back(wall);
		m_normal = wall->GetNomal();
	}
}

//DirectX::SimpleMath::Quaternion BaseObjectComponent::GetRotateDir()
//{
//	Vector3 upAngle = m_normal * XMConvertToRadians(90.0f);
//	Quaternion up =
//		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), upAngle.z) *
//		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), upAngle.y) *
//		Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), upAngle.x);
//	Quaternion upDir = up;
//
//	Quaternion wallDir2 = 
//		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), m_currentWall->GetAngle().z) *
//		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_currentWall->GetAngle().y) *
//		Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), m_currentWall->GetAngle().x);
//
// 	return  Quaternion::Slerp(m_me->GetTrans().GetDir(), wallDir2, 0.1f);
//}
//
//bool BaseObjectComponent::IsSomeDir()
//{
//	Vector3 up = Vector3::Transform(Vector3::Up, m_me->GetTrans().GetDir());
//	Vector3 normal = m_currentWall->GetNomal();
//
//	float cosTheta = up.Dot(normal);
//
//	float ragian = acos(cosTheta);
//	float degree = XMConvertToDegrees(ragian);
//
//	float range = 0.5f;
//
//	if ((-range < degree && range > degree) ||
//		(180 - range < degree && 180 + range > degree))
//	{
//		return true;
//	}
//	return false;
//}
