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

	// W�L�[�̃R�}���h
	Command* m_keyW;
	// A�L�[�̃R�}���h
	Command* m_keyA;
	// S�L�[�̃R�}���h
	Command* m_keyS;
	// D�L�[�̃R�}���h
	Command* m_keyD;

	// �X�y�[�X�L�[�̃R�}���h
	Command* m_keySpace;
	// C�L�[�̃R�}���h
	Command* m_keyC;
	// Z�L�[�̃R�}���h
	Command* m_keyZ;

	// Z�g���K�[�L�[�̃R�}���h
	Command* m_tKeyZ;

	// �}�E�X�̃N���b�N
	Command* m_clickLeft;

	// �L�[�{�[�h�̃g���K�[
	DirectX::Keyboard::KeyboardStateTracker tracker;

	// �}�E�X�̃g���K�[
	DirectX::Mouse::ButtonStateTracker mouseTracker;

	// �R�}���h�̃R���e�i
	std::vector<Command*> m_commandVector;
};