/// <summary>
/// InputComponent.h
/// 
/// �����:2018/7/4
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
#include "../../Command/InputHandler.h"
#include "../../Command/Command.h"

class BulletFactory;

/// <summary>
/// ���͂̃R���|�[�l���g�N���X
/// </summary>
class InputComponent : public Component
{
public:
	InputComponent();
	~InputComponent();

	// �X�V
	void Update(Entity& entity, DX::StepTimer const& timer) override;

private:
	InputHandler m_inputHandle;
};

