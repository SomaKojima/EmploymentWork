#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"

class StatusComponent;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class HP_UIComponent : public Component
{
public:
	HP_UIComponent(StatusComponent* status = nullptr);
	~HP_UIComponent();

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	//void LateUpdate(DX::StepTimer const& timer) override;
	// �`��
	//void Draw(Game* game) override;
	// �I��
	//void Finalize() override;

	// �����蔻��̏���
	//void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
	StatusComponent* m_status;
	Entity* m_life[3];

	int m_lastHp;
	int m_time;
	int m_flashTime;
};