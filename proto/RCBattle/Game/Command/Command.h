/// <summary>
/// Commoand.h
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
#include "../Object/Entity.h"

/// <summary>
/// �R�}���h�N���X
/// </summary>
class Command
{
public:
	virtual ~Command() {};

	virtual void Excute(Entity& entity) = 0;
};