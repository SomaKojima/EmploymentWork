#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class LineOfSightComponent : public Component
{
public:
	LineOfSightComponent(DirectX::SimpleMath::Vector3 end, int time);
	~LineOfSightComponent();


	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;

private:
	DirectX::SimpleMath::Vector3 m_end;
	DirectX::SimpleMath::Vector3 m_dir;
	float m_speed;
	int m_time;
};
