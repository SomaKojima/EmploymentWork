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
#include "Component.h"

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

	// ������
	void Initialize(Entity & entity) override;
	// �X�V
	void Update(Entity& entity, DX::StepTimer const& timer) override;
	// �x���X�V
	void LateUpdate(Entity& entity, DX::StepTimer const& timer) override;
	// �`��
	void Draw(Entity & entity, Game* game) override;
	// �I��
	void Finalize(Entity & entity) override;
private:
	Type m_type;
	DirectX::Model* m_model;
};