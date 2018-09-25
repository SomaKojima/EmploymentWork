/// <summary>
/// ModelComponent.h
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <Model.h>
#include "../Component.h"

/// <summary>
/// モデルコンポーネントクラス
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

	// 描画
	void Draw(Game* game) override;
	// 終了
	void Finalize() override;
private:
	Type m_type;
	DirectX::Model* m_model;
};