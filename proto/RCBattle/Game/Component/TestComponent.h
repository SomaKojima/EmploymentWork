/// <summary>
/// TestComponent.h
/// 
/// �����:2018/9/24
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include <Model.h>
#include "Component.h"

/// <summary>
/// ���f���R���|�[�l���g�N���X
/// </summary>
class TestComponent : public Component
{
public:
	TestComponent();
	~TestComponent();

	void Update(DX::StepTimer const& timer) override;
private:
	int count;
};
