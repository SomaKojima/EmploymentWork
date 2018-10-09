#include "../../../pch.h"
#include "BaseObjectComponent.h"
#include "../GameComponentLib.h"
#include "../../Object/EntityVector.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

BaseObjectComponent::BaseObjectComponent()
	:
	m_wallType(WallType::Bottom),
	m_normal(Vector3::Down),
	m_currentWall(nullptr),
	m_lastWall(nullptr)
{
}

BaseObjectComponent::~BaseObjectComponent()
{
}

void BaseObjectComponent::Initialize()
{
	EntityVector* entityVector = EntityVector::GetInstance();
	m_currentWall = entityVector->GetEntity("Bottom")->GetComponent<WallComponent>();
	PhysicsComponent* physics = m_me->GetComponent<PhysicsComponent>();
	m_physics = physics;
}

void BaseObjectComponent::Update(DX::StepTimer const & timer)
{
}

void BaseObjectComponent::LateUpdate(DX::StepTimer const & timer)
{
	//Vector3 gravityVec = m_normal * (9.8f / (60 * 60));
	m_physics->SetGravityDir(m_normal);
	Vector3 vec = m_me->GetTrans().GetVel();
	Vector3 vel = Vector3::Transform(vec, m_me->GetTrans().GetDir());
	Vector3 pos;

	if (m_currentWall->GetEntity()->GetName() == "Right")
	{
 		int a = 0;
	}

	if (m_currentWall)
	{
		// xé≤
		if (m_normal.x > 0.0f && vel.x > 0.0f)
		{
			if (m_me->GetTrans().GetWorld().Translation().x > m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().x - 1.5f)
			{
				pos = Vector3(
					m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().x - 1.5f,
					m_me->GetTrans().GetWorld().Translation().y, 
					m_me->GetTrans().GetWorld().Translation().z);
				vec.y  = 0.0f;
				m_me->GetTrans().SetPos(pos);
			}
		}
		else if (m_normal.x < 0.0f && vel.x < 0.0f)
		{
			if (m_me->GetTrans().GetWorld().Translation().x < m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().x + 1.5f)
			{
				pos = Vector3(
					m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().x + 1.5f,
					m_me->GetTrans().GetWorld().Translation().y,
					m_me->GetTrans().GetWorld().Translation().z);
				vec.y = 0.0f;
				m_me->GetTrans().SetPos(pos);
			}
		}
		// yé≤
 		if (m_normal.y < 0.0f && vel.y <= 0.0f)
		{
			if (m_me->GetTrans().GetWorld().Translation().y < m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().y + 1.5f)
			{
				pos = Vector3(
					m_me->GetTrans().GetWorld().Translation().x,
					m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().y + 1.5f,
					m_me->GetTrans().GetWorld().Translation().z);
				vec.y = 0.0f;
				m_me->GetTrans().SetPos(pos);
			}
		}
		else if (m_normal.y > 0.0f && vel.y >= 0.0f)
		{
			if (m_me->GetTrans().GetWorld().Translation().y > m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().y - 1.5f)
			{
				pos = Vector3(
					m_me->GetTrans().GetWorld().Translation().x,
					m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().y - 1.5f,
					m_me->GetTrans().GetWorld().Translation().z);
				vec.y = 0.0f;
				m_me->GetTrans().SetPos(pos);
			}
		}

		// zé≤
		if (m_normal.z < 0.0f && vel.z <= 0.0f)
		{
			if (m_me->GetTrans().GetWorld().Translation().z < m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().z + 1.5f)
			{
				pos = Vector3(
					m_me->GetTrans().GetWorld().Translation().x,
					m_me->GetTrans().GetWorld().Translation().y,
					m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().z + 1.5f);
				vec.y = 0.0f;
				m_me->GetTrans().SetPos(pos);
			}
		}
		else if (m_normal.z > 0.0f && vel.z >= 0.0f)
		{
			if (m_me->GetTrans().GetWorld().Translation().z > m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().z - 1.5f)
			{
				pos = Vector3(
					m_me->GetTrans().GetWorld().Translation().x,
					m_me->GetTrans().GetWorld().Translation().y,
					m_currentWall->GetEntity()->GetTrans().GetWorld().Translation().z - 1.5f);
				vec.y = 0.0f;
				m_me->GetTrans().SetPos(pos);
			}
		}
	}

	m_me->GetTrans().SetVel(vec);

	// å¸Ç´ÇïœÇ¶ÇÈ
	if (!IsSomeDir())
	{
		Quaternion dir = GetRotateDir();
		m_me->GetTrans().SetDir(dir);
	}
}

void BaseObjectComponent::Draw(Game * game)
{
}

void BaseObjectComponent::Finalize()
{
}

void BaseObjectComponent::OnCollide(Entity & collide, CollisionData * data)
{
	if (m_currentWall->GetEntity() != &collide)
	{
		Vector3 lastNormal = m_currentWall->GetNomal();

		WallComponent* wall = collide.GetComponent<WallComponent>();
		if(wall)
		{
			m_lastWall = wall;
			m_wallType = wall->GetWallType();
			m_normal = wall->GetNomal();

			float jumpForce = -0.1f;
			m_me->GetTrans().SetVel(m_me->GetTrans().GetVel() + (m_normal * jumpForce));
			m_currentWall = wall;

			// å¸Ç´ÇïœÇ¶ÇÈ
			if (!IsSomeDir())
			{
				Quaternion dir = GetRotateDir();
				m_me->GetTrans().SetDir(dir);
			}
		}
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

	Quaternion wallDir2 = 
		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), m_currentWall->GetAngle().z) *
		Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_currentWall->GetAngle().y) *
		Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), m_currentWall->GetAngle().x);

 	return  Quaternion::Slerp(m_me->GetTrans().GetDir(), wallDir2, 0.1f);
}

bool BaseObjectComponent::IsSomeDir()
{
	Vector3 up = Vector3::Transform(Vector3::Up, m_me->GetTrans().GetDir());
	Vector3 normal = m_currentWall->GetNomal();

	float cosTheta = up.Dot(normal);

	float ragian = acos(cosTheta);
	float degree = XMConvertToDegrees(ragian);

	float range = 0.5f;

	if ((-range < degree && range > degree) ||
		(180 - range < degree && 180 + range > degree))
	{
		return true;
	}
	return false;
}
