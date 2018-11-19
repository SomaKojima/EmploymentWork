#pragma once

#include "../../Component/Component.h"
#include "../../GameComponent/Button/ButtonComponent.h"

/// <summary>
/// ボタンののコンポーネントクラス
/// </summary>
class StartButton : public ButtonComponent::ButtonFunc
{
public:
	StartButton();
	~StartButton();

	void Press() override;
};
