/// <summary>
/// Commoand.h
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
#include "../Object/Entity.h"

/// <summary>
/// コマンドクラス
/// </summary>
class Command
{
public:
	virtual ~Command() {};

	virtual void Excute(Entity& entity) = 0;
};