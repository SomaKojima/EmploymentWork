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
	
}

void BaseObjectComponent::LateUpdate(DX::StepTimer const & timer)
{

	if (m_current.size() != 0)
	{
		m_normal = Vector3::Zero;
		for (auto ite = m_current.begin(); ite != m_current.end(); ite++)
		{
			m_normal += (*ite)->GetNomal();
		}
		m_normal.Normalize();

		/////// Œü‚«‚ð•Ï‚¦‚é

		// Žp¨‚ð‡‚í‚¹‚é

		Vector3 upDir = Vector3::Transform(Vector3::Up, m_me->GetTrans().GetDir());
		// ‰ñ“]Ž²ŒvŽZ
		Vector3 axis = upDir.Cross(-m_normal);
		if (axis != Vector3::Zero)
		{
			// Šp“x‚ð‹‚ß‚é
			float rot = acos(upDir.Dot(-m_normal));
			Quaternion  Q1 = Quaternion::CreateFromAxisAngle(axis, rot);

			m_me->GetTrans().SetDir(Q1);
		}

		//// Œü‚«‚ð‡‚í‚¹‚é

		//Quaternion CQ1;
		//Q1.Conjugate(CQ1);
		//Quaternion ODQ(0, 0, 1, 0);
		//Quaternion res = CQ1 * ODQ;
		//res *= Q1;

		//Vector3 od(res.x, res.y, res.z);

	}

	// ‘¬“x‚ðŽæ“¾
	Vector3 vel = m_me->GetTrans().GetVel();
	Vector3 accel = m_me->GetTrans().GetAccel();

	// –€ŽC‚ÌŒvŽZ
	vel *= Vector3(0.9f, 1.0f, 0.9f);
	accel *= Vector3(0.9f, 1.0f, 0.9f);

	// d—Í‚ÌŒvŽZ
	accel += (m_normal * (9.8f / (60 * 60)));

	m_me->GetTrans().SetAccel(accel);
	m_me->GetTrans().SetVel(vel);

	m_last = m_current;
	m_current.clear();
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

DirectX::SimpleMath::Quaternion BaseObjectComponent::GetRotateDir()
{
	Vector3 upAngle = m_normal * XMConvertToRadians(90.0f);
	Quaternion up =
		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), upAngle.z) *
		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), upAngle.y) *
		Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), upAngle.x);
	Quaternion upDir = up;

	/*Quaternion wallDir2 = 
		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), m_currentWall->GetAngle().z) *
		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_currentWall->GetAngle().y) *
		Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), m_currentWall->GetAngle().x);

 	return  Quaternion::Slerp(m_me->GetTrans().GetDir(), wallDir2, 0.1f);*/

	return Quaternion::Identity;
}

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
