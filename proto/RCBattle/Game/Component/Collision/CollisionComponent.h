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
	CollisionComponent():isHit(false) {};
	~CollisionComponent() {};

	// �X�V
	void Update(DX::StepTimer const& timer) override;

	// �ǂ��蓙�̏���
	template<class T>
	void HitBackExecution(T* info, DirectX::SimpleMath::Vector3& hitPos);

	virtual void HitBack(Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(Collision::Sphere* sphere, DirectX::SimpleMath::Vector3& hitPos) {};

	void SetHit(bool flag) { isHit = flag; }
	bool IsHit() { return isHit; }
private:
	bool isHit;
};

template<class T>
inline void CollisionComponent::HitBackExecution(T * info, DirectX::SimpleMath::Vector3 & hitPos)
{
	if (isHit)
	{
		HitBack(info, hitPos);
	}
}
