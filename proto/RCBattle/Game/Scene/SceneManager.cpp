#include "../../pch.h"
#include "SceneManager.h"
#include "../Object/EntityVector.h"
#include "ScenePlay.h"
#include "SceneTitle.h"

SceneBase* SceneManager::m_currentScene = nullptr;
Game* SceneManager::m_game = nullptr;

SceneManager::SceneManager()
	:
	m_currentSceneID(Title),
	m_changeSceneID(Title)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	ChangeScene();
}

void SceneManager::Update(DX::StepTimer const& timer)
{
	m_changeSceneID = m_currentSceneID;
	EntityVector* entityVector = EntityVector::GetInstance();
	entityVector->Update(timer);

	if (m_changeSceneID != m_currentSceneID)
	{
		ChangeScene();
	}
}

void SceneManager::Render()
{
	EntityVector* entityVector = EntityVector::GetInstance();
	entityVector->Render(m_game);
}

void SceneManager::Finalize()
{
	EntityVector* entityVector = EntityVector::GetInstance();
	entityVector->Finalize();

	// 現在のシーンの削除
	if (m_currentScene)
	{
		delete m_currentScene;
		m_currentScene = nullptr;
	}
}

void SceneManager::ChangeScene()
{
	// 現在のオブジェクト達の終了処理
	EntityVector* entityVector = EntityVector::GetInstance();
	entityVector->Finalize();

	// 現在のシーンの削除
	if (m_currentScene)
	{
		delete m_currentScene;
		m_currentScene = nullptr;
	}

	// 新しいシーンを作成
	switch (m_changeSceneID)
	{
	case SceneID::Title:
		m_currentScene = new SceneTitle();
		break;
	case SceneID::Play:
		m_currentScene = new ScenePlay();
		break;
	}
	m_currentSceneID = m_changeSceneID;

	// シーンの初期化 
	m_currentScene->Initialize(m_game);
	entityVector->Initialize();
}
