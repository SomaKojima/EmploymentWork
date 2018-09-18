//
// Game.h
//

#pragma once

#include <Model.h>
#include <vector>

#include "DeviceResources.h"
#include "StepTimer.h"
#include "SpriteBatch.h"

#include "DebugCamera.h"
#include "GridFloor.h"
#include "Game/Object/Entity.h"
#include "Game/Object//CarFactory.h"
#include "Game/Object//BulletFactory.h"
#include "MyCamera.h"
#include "Game/Collision/CCell.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

	DirectX::SpriteBatch* GetSpriteBatch() { return m_sprites.get(); }

	ID3D11Device* GetDevice()
	{
		return m_deviceResources->GetD3DDevice();
	}
	ID3D11DeviceContext* GetContext() { return m_deviceResources->GetD3DDeviceContext(); }
	DirectX::CommonStates* GetStates() { return m_states.get(); }
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }
	const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }

	// デバッグテキスト
	static void AddText(wchar_t text[]);
	static void DeleteText();
	static void SetNumText(int num) { m_numText = num; }
	static void SetPosText(DirectX::SimpleMath::Vector3 pos) { m_posText = pos; }
	static void SetNumText2(int num) { m_numText2 = num; }
	static void SetPosText2(DirectX::SimpleMath::Vector3 pos) { m_posText2 = pos; }

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	// スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_font;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	// グリッドの床
	std::unique_ptr<GridFloor> m_gridFloor;

	// デバッグテキスト
	static wchar_t* m_debugText[18];
	static int  m_numText;
	static int  m_numText2;
	static DirectX::SimpleMath::Vector3 m_posText;
	static DirectX::SimpleMath::Vector3 m_posText2;

	// カメラ
	MyCamera m_camera;

};