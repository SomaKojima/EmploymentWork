#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"
#include <list>

class UIRenderer;

/// <summary>
/// �{�^���̂̃R���|�[�l���g�N���X
/// </summary>
class ButtonComponent : public Component
{
public:
	class ButtonFunc
	{
	public:
		virtual ~ButtonFunc() {}

		virtual void Press() {}
		virtual void Relese() {}
		virtual void Long() {}
	};
public:
	ButtonComponent();
	~ButtonComponent();

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �I��
	void Finalize() override;

	void AddFunc(ButtonFunc* func);

private:
	UIRenderer* uiRenderer;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_tracker;

	// ���������̏���
	std::list<ButtonFunc*> m_pressList;
};

