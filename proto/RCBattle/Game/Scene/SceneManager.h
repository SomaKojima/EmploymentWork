#pragma once

#include "../../StepTimer.h"
#include "../Utility/Utility.h"

class Game;

class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Initialize(Game* game) = 0;
};

class SceneManager : public SingletonBase<SceneManager>
{
public:
	enum SceneID
	{
		Title,
		Play,

		Max
	};

public:
	SceneManager();
	~SceneManager();

	void Update(DX::StepTimer const& timer);
	void Render();
	void Finalize();

	void ChangeSceneID(SceneID sceneid) { m_changeSceneID = sceneid; }

	void SetGame(Game* game) { m_game = game; }

	void ChangeScene();
private:
	void Initialize();

private:
	SceneID m_currentSceneID;
	SceneID m_changeSceneID;
	static SceneBase* m_currentScene;
	static Game* m_game;
};
