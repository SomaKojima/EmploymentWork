#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"
#include <list>

class UIRenderer;

/// <summary>
/// ボタンののコンポーネントクラス
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

	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 終了
	void Finalize() override;

	void AddFunc(ButtonFunc* func);

private:
	UIRenderer* uiRenderer;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;

	// 押した時の処理
	std::list<ButtonFunc*> m_pressList;
};

