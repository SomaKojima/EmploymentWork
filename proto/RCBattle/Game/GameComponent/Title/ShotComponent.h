#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class ShotComponent : public Component
{
public:
	ShotComponent(int time);
	~ShotComponent();

	// �X�V
	void Update(DX::StepTimer const& timer) override;

private:
	int m_time;
};
