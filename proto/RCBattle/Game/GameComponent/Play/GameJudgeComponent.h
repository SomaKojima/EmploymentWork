/// ヘッダのインクルード
/// </summary>
#include <list>
#include "../../Component/Component.h"

class MyCamera;

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class GameJudgeComponent : public Component
{
public:
	GameJudgeComponent(MyCamera* camera);
	~GameJudgeComponent();

	// 更新
	void Update(DX::StepTimer const& timer) override;

private:
	MyCamera* m_camera;
};
