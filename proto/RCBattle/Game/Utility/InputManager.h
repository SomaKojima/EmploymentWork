#pragma once

#include "Utility.h"

class InputManager : public SingletonBase<InputManager>
{
public:
	InputManager() {}
	~InputManager() {}

public:
	DirectX::Mouse::ButtonStateTracker& GetMouseTracker() { return mouseTracker; }

private:
	// �}�E�X�̃g���K�[
	DirectX::Mouse::ButtonStateTracker mouseTracker;
};