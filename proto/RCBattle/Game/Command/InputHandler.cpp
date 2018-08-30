#include "../../pch.h"
#include "InputHandler.h"
#include "AdvanceCommand.h"
#include "RecessionCommand.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "DownCommand.h"
#include "UpCommand.h"
#include "ShotCommand.h"

#include "../Object/BulletFactory.h"

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
	m_keySpace = new UpCommand();
	m_keyC = new DownCommand();
	m_keyZ = new ShotCommand();
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
	delete m_keySpace;
	delete m_keyC;
	delete m_keyZ;
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
	// コンテナの初期化
	m_commandVector.clear();

	if (kb.Up) m_commandVector.push_back(m_keyUpArrow);
	if (kb.Down) m_commandVector.push_back(m_keyDownArrow);


	if (kb.Left) m_commandVector.push_back(m_keyLeftArrow);
	if (kb.Right) m_commandVector.push_back(m_keyRightArrow);

	//if (tracker.pressed.Left) m_commandVector.push_back(m_keyLeftArrow);
	//if(tracker.pressed.Right) m_commandVector.push_back(m_keyRightArrow);

	if (kb.Space) m_commandVector.push_back(m_keySpace);
	if (kb.C) m_commandVector.push_back(m_keyC);
	if (tracker.pressed.Z) m_commandVector.push_back(m_keyZ);

	return m_commandVector;
}
