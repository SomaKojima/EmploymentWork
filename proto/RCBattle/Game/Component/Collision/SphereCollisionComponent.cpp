/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
#include "SphereCollisionComponent.h"
#include "BoxCollisionComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="radius">���a</param>
SphereCollisionComponent::SphereCollisionComponent(DirectX::SimpleMath::Vector3 center, float radius)
	:
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_sphere.radius = radius;
}

/// <summary>
/// �f�X�g���N�^
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
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void SphereCollisionComponent::Draw(Game * game)
{
	Matrix world = m_me->GetTrans().GetWorld() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugSphere>(game->GetDevice(), m_center, m_radius);
	}
	else
	{
		//m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
/// <param name="entity">����</param>
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
	//// �p
	//float phi = (radian_xy)* XM_PI / 180;
	//// ���ʊp
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

