#include "../../pch.h"
#include "InputHandler.h"
#include "AdvanceCommand.h"
#include "RecessionCommand.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "DownCommand.h"
#include "UpCommand.h"
#include "ShotCommand.h"
#include "DriftCommand.h"

#include "RightMoveCommand.h"
#include "LeftMoveCommand.h"

#include "../Object/Factory/BulletFactory.h"

using namespace std;
using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
InputHandler::InputHandler()
{
	m_keyUpArrow = new AdvanceCommand();
	m_keyDownArrow = new RecessionCommand();
	m_keyLeftArrow = new LeftCommand();
	m_keyRightArrow = new RightCommand();

	m_keyW = new AdvanceCommand();
	m_keyS = new RecessionCommand();
	/*m_keyA = new LeftCommand();
	m_keyD = new RightCommand();*/
	m_keyA = new LeftMoveCommand();
	m_keyD = new RightMoveCommand();

	m_keySpace = new UpCommand();
	m_keyC = new DownCommand();
	m_keyZ = new DriftCommand();

	m_tKeyZ = new ShotCommand();

	m_clickLeft = new ShotCommand();
}

/// <summary>
/// デストラクタ
/// </summary>
InputHandler::~InputHandler()
{
	delete m_keyUpArrow;
	delete m_keyDownArrow;
	delete m_keyLeftArrow;
	delete m_keyRightArrow;

	delete m_keyW;
	delete m_keyA;
	delete m_keyS;
	delete m_keyD;

	delete m_keySpace;
	delete m_keyC;
	delete m_keyZ;

	delete m_tKeyZ;

	delete m_clickLeft;

	// コンテナの初期化
	m_commandVector.clear();
}

/// <summary>
/// 入力ハンドルの取得
/// </summary>
/// <returns>コマンド</returns>
vector<Command*>& InputHandler::GetInputHnadle()
{
	// キーボードの作成 
	Keyboard::State kb = Keyboard::Get().GetState();
	tracker.Update(kb);

	// マウスの作成
	Mouse::State mouse = Mouse::Get().GetState();
	mouseTracker.Update(mouse);

	// コンテナの初期化
	m_commandVector.clear();

	// ---- 前後左右移動 -----
	if (kb.Up) m_commandVector.push_back(m_keyUpArrow);
	if (kb.Down) m_commandVector.push_back(m_keyDownArrow);
	if (kb.Left) m_commandVector.push_back(m_keyLeftArrow);
	if (kb.Right) m_commandVector.push_back(m_keyRightArrow);

	if (kb.W) m_commandVector.push_back(m_keyW);
	if (kb.A) m_commandVector.push_back(m_keyA);
	if (kb.S) m_commandVector.push_back(m_keyS);
	if (kb.D) m_commandVector.push_back(m_keyD);

	// ----- ジャンプ -----
	if (tracker.pressed.Space) m_commandVector.push_back(m_keySpace);

	// ----- しゃがむ -----
	if (kb.C) m_commandVector.push_back(m_keyC);
	//if (kb.Z) m_commandVector.push_back(m_keyZ);

	// ----- 弾を撃つ -----
	if (tracker.pressed.Z) m_commandVector.push_back(m_tKeyZ);

	if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED) m_commandVector.push_back(m_clickLeft);

	return m_commandVector;
}
