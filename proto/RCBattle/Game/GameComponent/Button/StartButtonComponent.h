#pragma once

#include "../../Component/Component.h"
#include "../../GameComponent/Button/ButtonComponent.h"

/// <summary>
/// �{�^���̂̃R���|�[�l���g�N���X
/// </summary>
class StartButtonComponent : public Component, public ButtonComponent::ButtonFunc
{
public:
	StartButtonComponent();
	~StartButtonComponent();

	void Press() override;
};
