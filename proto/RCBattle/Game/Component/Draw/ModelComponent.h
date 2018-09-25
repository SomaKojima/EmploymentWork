/// <summary>
/// ModelComponent.h
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
#include <Model.h>
#include "../Component.h"

/// <summary>
/// ���f���R���|�[�l���g�N���X
/// </summary>
class ModelComponent : public Component
{
public:
	enum Type
	{
		Nomal,
		Sky
	};

public:
	ModelComponent(DirectX::Model* model, Type type);
	~ModelComponent();

	// �`��
	void Draw(Game* game) override;
	// �I��
	void Finalize() override;
private:
	Type m_type;
	DirectX::Model* m_model;
};