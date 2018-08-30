/// <summary>
/// InputHandler.h
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
#include <vector>
#include "Command.h"

/// <summary>
/// 前方宣言
/// </summary>
class BulletFactory;

/// <summary>
/// 入力ハンドルクラス
/// </summary>
class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	// 入力ハンドルを取得
	std::vector<Command*>& GetInputHnadle();

private:
	// 上キーのコマンド
	Command* m_keyUpArrow;
	// 下キーのコマンド
	Command* m_keyDownArrow;
	// 左キーのコマンド
	Command* m_keyLeftArrow;
	// 右キーのコマンド
	Command* m_keyRightArrow;
	// スペースキーのコマンド
	Command* m_keySpace;
	// Cキーのコマンド
	Command* m_keyC;
	// Zキーのコマンド
	Command* m_keyZ;

	// キーボードのトリガー
	DirectX::Keyboard::KeyboardStateTracker tracker;

	// コマンドのコンテナ
	std::vector<Command*> m_commandVector;
};