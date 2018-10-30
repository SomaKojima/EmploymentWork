/// <summary>
/// CollisionComponent.h
/// 
/// �����:2018/10/26
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Component.h"
#include "../../Collision/Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent() :isHit(false) {};
	~CollisionComponent() {};

	// �X�V
	void Update(DX::StepTimer const& timer) override;

	// �ǂ��蓙�̏���
	virtual void HitBack(const Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(const Collision::Sphere* sphere, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(const Collision::Plane* sphere, DirectX::SimpleMath::Vector3& hitPos) {};

	void SetHit(bool flag) { isHit = flag; }
	bool IsHit() { return isHit; }

	Collision::CollisionType GetShape(
		const Collision::Sphere** sphere = nullptr,
		const Collision::Plane** plane = nullptr,
		const Collision::Triangle** triangle = nullptr,
		const std::list<Collision::Triangle>** triangleList = nullptr)
	{

		if (sphere)		*sphere = &GetSphere();
		if (plane)		*plane = &GetPlane();
		if (triangle)		*triangle = &GetTriangle();
		if (triangleList)	*triangleList = &GetTriangleList();

		if (*sphere) return Collision::CollisionType::SPHERE;
		if (*plane)return Collision::CollisionType::PLANE;
		if (*triangle)return Collision::CollisionType::TRIANGLE;
		if (*triangleList)return Collision::CollisionType::TRIANGLE;

		return Collision::CollisionType::NONE;
	}

	virtual Collision::CollisionData2 GetShape() {};

protected:
	// ���̎擾
	virtual const Collision::Sphere& GetSphere() { Collision::Sphere* sphere = nullptr; return *sphere; }
	// �ʂ̎擾
	virtual const Collision::Plane& GetPlane() { Collision::Plane* plane = nullptr; return *plane; }
	// �O�p�`�̎擾
	virtual const Collision::Triangle& GetTriangle() { Collision::Triangle* triangle = nullptr; return *triangle; }

	virtual const std::list<Collision::Triangle>& GetTriangleList() 
	{ std::list<Collision::Triangle>* triangleList = nullptr; return *triangleList; }

private:
	bool isHit;
};
