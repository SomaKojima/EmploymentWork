#pragma once

#include "../../Component/Component.h"
#include "../../GameComponent/Button/ButtonComponent.h"

/// <summary>
/// �{�^���̂̃R���|�[�l���g�N���X
/// </summary>
class StartButton : public ButtonComponent::ButtonFunc
{
public:
	StartButton();
	~StartButton();

	void Press() override;
};
