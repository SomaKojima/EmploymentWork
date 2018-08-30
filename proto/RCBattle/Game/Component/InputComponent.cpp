/// <summary>
/// InputComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "InputComponent.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
InputComponent::InputComponent()
	:
	m_inputHandle()
{
	m_name = "Input";
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InputComponent::~InputComponent()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="entity"></param>
void InputComponent::Initialize(Entity & entity)
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="entity">����</param>
/// <param name="timer">����</param>
void InputComponent::Update(Entity& entity, DX::StepTimer const& timer)
{
	std::vector<Command*>& command = m_inputHandle.GetInputHnadle();
	for (auto ite = command.begin(); ite != command.end(); ite++)
	{
		(*ite)->Excute(entity);
	}
}

/// <summary>
/// �x���X�V
/// </summary>
/// <param name="m_entity">����</param>
/// <param name="timer">����</param>
void InputComponent::LateUpdate(Entity & m_entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void InputComponent::Draw(Entity & entity, Game * game)
{
}

/// <summary>
/// �I������
/// </summary>
/// <param name="entity">����</param>
void InputComponent::Finalize(Entity & entity)
{
}
