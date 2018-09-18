//
// Game.cpp
//
#include < wchar.h > 
#include "pch.h"
#include "Game.h"
#include "Game/Component/ComponentLib.h"
#include "Game/Collision/Collision.h"
#include "Game/Object/ModelData.h"
#include "Game/Object/EntityVector.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;
wchar_t* Game::m_debugText[18] = {
	nullptr,
	nullptr, 
	nullptr, 
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr};
int Game::m_numText = 0;
Vector3 Game::m_posText = Vector3::Zero;
int Game::m_numText2 = 0;
Vector3 Game::m_posText2 = Vector3::Zero;

Game::Game()
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

	// デバッグカメラの作成
	m_debugCamera = std::make_unique<DebugCamera>(width, height);

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

void Game::AddText(wchar_t text[])
{
	// テキストがいっぱいの時
	if (m_debugText[17] != nullptr)
	{
		for (int i = 0; i < 17; i++)
		{
			m_debugText[i] = m_debugText[i + 1];
		}
		m_debugText[17] = text;
		return;
	}

	// テキストを入れる
	for (int i = 0; i < 18; i++)
	{
		if (m_debugText[i] == nullptr)
		{
			m_debugText[i] = text;
			return;
		}
	}
}

void Game::DeleteText()
{
	for (int i = 0; i < 17; i++)
	{
		m_debugText[i] = m_debugText[i + 1];
		if (m_debugText[i] == nullptr)
		{
			return;
		}
	}
	m_debugText[17] = nullptr;
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	// デバッグカメラの更新
	m_debugCamera->Update();

	//// コンポーネントの更新
	EntityVector* entityVector = EntityVector::GetInstance();
	entityVector->Update(timer);

	// 1秒ごとにデバッグテキストを1行消す
	static int second = 0;
	if ((int)(timer.GetTotalSeconds()) != second)
	{
		second = (int)(timer.GetTotalSeconds());
		DeleteText();
	}

	// カメラの更新
	m_camera.Update();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	// ビュー行列の作成
	m_view = Matrix::CreateLookAt(m_camera.GetEyePosition(), m_camera.GetTargetPosition(), Vector3::Up);
	//m_view = m_debugCamera->GetCameraMatrix();

	// グリッドの床の描画
	m_gridFloor->Render(context, m_view, m_projection);

	// ここから描画処理を記述する

	EntityVector* entityVector = EntityVector::GetInstance();
	entityVector->Render(this);

	Vector2 pos = Vector2::Zero;
	m_sprites->Begin();
	// デバッグテキストの描画
	for (int i = 0; i < 18; i++)
	{
		if (m_debugText[i] == nullptr)
		{
			break;
		}
		m_font->DrawString(m_sprites.get(), m_debugText[i], pos, Colors::Red);
		pos.y += 32;
	}
	//	FPSの描画
	wchar_t name[30] = L"fps : ";
	wchar_t fpsBuf[30] = L"";
	int a = m_timer.GetFramesPerSecond();
	_itow( a , fpsBuf, 10);
	wcscat(name, fpsBuf);
	m_font->DrawString(m_sprites.get(), name, Vector2(300.0f, 10.0f), Colors::Red);


	wchar_t name2[30] = L"num : ";
	wchar_t num[30] = L"";
	_itow(m_numText, num, 10);
	wcscat(name2, num);
	m_font->DrawString(m_sprites.get(), name2, Vector2(300.0f, 42.0f), Colors::Red);
	//wchar_t name3[30] = L"pos : ";
	//wchar_t num2[30] = L"";
	//_itow((int)m_posText.x, num, 10);
	//_itow((int)m_posText.y, num2, 10);
	//wcscat(num, L",");
	//wcscat(num, num2);
	//_itow((int)m_posText.z, num2, 10);
	//wcscat(num, L",");
	//wcscat(num, num2);
	//wcscat(name3, num);
	//m_font->DrawString(m_sprites.get(), name3, Vector2(300, 74.0f), Colors::Red);

	wchar_t name4[30] = L"num2 : ";
	wchar_t num3[30] = L"";
	_itow(m_numText2, num3, 10);
	wcscat(name4, num3);
	m_font->DrawString(m_sprites.get(), name4, Vector2(300.0f, 106.0f), Colors::Red);
	//wchar_t name5[30] = L"pos : ";
	//wchar_t num4[30] = L"";
	//wchar_t num5[30] = L"";
	//_itow((int)m_posText2.x, num4, 10);
	//_itow((int)m_posText2.y, num5, 10);
	//wcscat(num4, L",");
	//wcscat(num4, num5);
	//_itow((int)m_posText2.z, num5, 10);
	//wcscat(num4, L",");
	//wcscat(num4, num5);
	//wcscat(name5, num4);
	//m_font->DrawString(m_sprites.get(), name5, Vector2(300, 138.0f), Colors::Red);

	m_sprites->End();

	// ここまで

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::DarkBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context =  m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);

	// スプライトフォントの作成
	m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");

	// グリッドの床の作成
	m_gridFloor = std::make_unique<GridFloor>(device, context, m_states.get(), 10.0f, 10);

	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Init(4, -100.0f, 100.0f,100.0f, 0.0f, 100.0f, -100.0f);

	// 車モデルの作成
	// モデルを読み込む
	ModelData* modelData = ModelData::GetInstance();
	modelData->Create(device);

	// オブジェクトのコンテナクラス
	EntityVector* entityVector = EntityVector::GetInstance();

	Entity* entity = nullptr;

	// 車のファクトリの生成
	CarFactory* carFactory = CarFactory::GetInstance();

	// プレイヤーの作成
	// 車の作成
	entity = carFactory->CreateCar();
	entity->GetTrans().SetTrans(Vector3(0.0f, 2.0f, 0.0f));
	// 入力コンポーネントを追加
	entity->AddComponent(new InputComponent());
	// コンテナに追加
	entityVector->Add(entity);

	// カメラの設定
	m_camera.SetPlayer(entity);

	// 敵
	// 車の作成
	entity = carFactory->CreateCar();
	entity->GetTrans().SetTrans(Vector3(0.0f, 2.0f, 10.0f));
	// コンテナに追加
	entityVector->Add(entity);

	// 部屋の作成
	entity = new Entity();
	// モデルコンポーネントの追加
	entity->AddComponent(new ModelComponent(modelData->GetRoom(), ModelComponent::Type::Sky));
	// 球の当たり判定コンポーネントの追加
	entity->AddComponent(new BoxCollisionComponent(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f,1.0f,1.0f)));
	// コンテナに追加
	entityVector->Add(entity);

	entityVector->Initialize();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
	);

	// デバッグカメラにウインドウのサイズ変更を伝える
	m_debugCamera->SetWindowSize(size.right, size.bottom);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

	// コモンステートの解放
	m_states.reset();

	// スプライトバッチの解放
	m_sprites.reset();

	// スプライトフォントの解放
	m_font.reset();

	// グリッドの床の解放
	m_gridFloor.reset();

	CLiner8TreeManager::Lost();

	// 車モデルの開放

	EntityVector* entityVector = EntityVector::GetInstance();
	entityVector->Finalize();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
