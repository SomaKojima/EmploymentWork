#include "../../pch.h"
#include "ModelData.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ModelData::ModelData()
{
}

ModelData::~ModelData()
{
	m_bulletModel.reset();
	m_carModel.reset();
	m_carBodyModel.reset();
	m_carCannonModel.reset();
	m_roomModel.reset();
	m_sphere.reset();
}

void ModelData::Create(ID3D11Device* device)
{
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources\\Models");
	m_bulletModel = Model::CreateFromCMO(device, L"Resources\\Models\\burret.cmo", fx);
	m_carModel = Model::CreateFromCMO(device, L"Resources\\Models\\car.cmo", fx);

	m_carBodyModel = Model::CreateFromCMO(device, L"Resources\\Models\\car_body.cmo", fx);
	m_carCannonModel = Model::CreateFromCMO(device, L"Resources\\Models\\car_cannon.cmo", fx);
	m_roomModel = Model::CreateFromCMO(device, L"Resources\\Models\\room.cmo", fx);
	m_sphere = Model::CreateFromCMO(device, L"Resources\\Models\\sphere.cmo", fx);
}

