/// <summary>
/// InputHandler.h
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
#include <vector>
#include "Command.h"

/// <summary>
/// �O���錾
/// </summary>
class BulletFactory;

/// <summary>
/// ���̓n���h���N���X
/// </summary>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	// ���̓n���h�����擾
	std::vector<Command*>& GetInputHnadle();

private:
	// ��L�[�̃R�}���h
	Command* m_keyUpArrow;
	// ���L�[�̃R�}���h
	Command* m_keyDownArrow;
	// ���L�[�̃R�}���h
	Command* m_keyLeftArrow;
	// �E�L�[�̃R�}���h
	Command* m_keyRightArrow;
	// �X�y�[�X�L�[�̃R�}���h
	Command* m_keySpace;
	// C�L�[�̃R�}���h
	Command* m_keyC;
	// Z�L�[�̃R�}���h
	Command* m_keyZ;

	// �L�[�{�[�h�̃g���K�[
	DirectX::Keyboard::KeyboardStateTracker tracker;

	// �R�}���h�̃R���e�i
	std::vector<Command*> m_commandVector;
};