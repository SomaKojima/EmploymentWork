/// �w�b�_�̃C���N���[�h
/// </summary>
#include <list>
#include "../../Component/Component.h"

class MyCamera;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class GameJudgeComponent : public Component
{
public:
	GameJudgeComponent(MyCamera* camera);
	~GameJudgeComponent();

	// �X�V
	void Update(DX::StepTimer const& timer) override;

private:
	MyCamera* m_camera;
};
