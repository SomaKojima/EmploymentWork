/// <summary>
/// InputComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
#include "InputComponent.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
InputComponent::InputComponent()
	:
	m_inputHandle()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InputComponent::~InputComponent()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="entity">����</param>
/// <param name="timer">����</param>
void InputComponent::Update(DX::StepTimer const& timer)
{
	std::vector<Command*>& command = m_inputHandle.GetInputHnadle();
	for (auto ite = command.begin(); ite != command.end(); ite++)
	{
		(*ite)->Excute(*m_me);
	}
}
