#include "otherplayer.h"

void OtherPlayer::LoadModel()
{
	_partsModel[0]->Load("asset\\model\\head.obj");
	_partsModel[1]->Load("asset\\model\\body.obj");
	_partsModel[2]->Load("asset\\model\\head.obj");
	_partsModel[3]->Load("asset\\model\\head.obj");
	_partsModel[4]->Load("asset\\model\\head.obj");
	_partsModel[5]->Load("asset\\model\\head.obj");
}

void OtherPlayer::Init()
{
	InitComponents();
}

void OtherPlayer::Uninit()
{
	RemoveComponents();
}

void OtherPlayer::Update()
{

	//À•W‚ÌÝ’è
	if (m_Velocity)
	{
		m_TransForm->m_Position.x += m_Velocity->m_Velocity.x;
		m_TransForm->m_Position.y += m_Velocity->m_Velocity.y;
		m_TransForm->m_Position.z += m_Velocity->m_Velocity.z;
	}

	
	AnimationState();
	UpdateComponents();
}

void OtherPlayer::Draw()
{

	XMMATRIX world, scl, rot, trans;

	scl = XMMatrixScaling(m_TransForm->m_Scale.x, m_TransForm->m_Scale.y, m_TransForm->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + _partsTransFomr[0]->m_Position.x, m_TransForm->m_Position.y + _partsTransFomr[0]->m_Position.y, m_TransForm->m_Position.z + _partsTransFomr[0]->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[0]) { _partsModel[0]->Draw(); }

	scl = XMMatrixScaling(m_TransForm->m_Scale.x, m_TransForm->m_Scale.y, m_TransForm->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + _partsTransFomr[1]->m_Position.x, m_TransForm->m_Position.y + _partsTransFomr[1]->m_Position.y, m_TransForm->m_Position.z + _partsTransFomr[1]->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[1]) { _partsModel[1]->Draw(); }

	scl = XMMatrixScaling(m_TransForm->m_Scale.x + _partsTransFomr[2]->m_Scale.x, m_TransForm->m_Scale.y + _partsTransFomr[2]->m_Scale.y, m_TransForm->m_Scale.z + _partsTransFomr[2]->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + _partsTransFomr[2]->m_Position.x, m_TransForm->m_Position.y + _partsTransFomr[2]->m_Position.y, m_TransForm->m_Position.z + _partsTransFomr[2]->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[2]) { _partsModel[2]->Draw(); }

	scl = XMMatrixScaling(m_TransForm->m_Scale.x + _partsTransFomr[3]->m_Scale.x, m_TransForm->m_Scale.y + _partsTransFomr[3]->m_Scale.y, m_TransForm->m_Scale.z + _partsTransFomr[3]->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + _partsTransFomr[3]->m_Position.x, m_TransForm->m_Position.y + _partsTransFomr[3]->m_Position.y, m_TransForm->m_Position.z + _partsTransFomr[3]->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[3]) { _partsModel[3]->Draw(); }

	scl = XMMatrixScaling(m_TransForm->m_Scale.x + _partsTransFomr[4]->m_Scale.x, m_TransForm->m_Scale.y + _partsTransFomr[4]->m_Scale.y, m_TransForm->m_Scale.z + _partsTransFomr[4]->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + _partsTransFomr[4]->m_Position.x, m_TransForm->m_Position.y + _partsTransFomr[4]->m_Position.y, m_TransForm->m_Position.z + _partsTransFomr[4]->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[4]) { _partsModel[4]->Draw(); }

	scl = XMMatrixScaling(m_TransForm->m_Scale.x + _partsTransFomr[5]->m_Scale.x, m_TransForm->m_Scale.y + _partsTransFomr[5]->m_Scale.y, m_TransForm->m_Scale.z + _partsTransFomr[5]->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + _partsTransFomr[5]->m_Position.x, m_TransForm->m_Position.y + _partsTransFomr[5]->m_Position.y, m_TransForm->m_Position.z + _partsTransFomr[5]->m_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[5]) { _partsModel[5]->Draw(); }

	DrawComponents();
}

void OtherPlayer::InitComponents()
{
	m_Velocity = new Velocity(this);
	m_Sharder = new Sharder(this);
	for (int i = 0; i < MAX_PARTS; i++) { _partsTransFomr[i] = new TransForm(this); }
	for (int i = 0; i < MAX_PARTS; i++) { _partsModel[i] = new ModelRenderer(this); }
	for (int i = 0; i < MAX_PARTS; i++) { _partsAnimation[i] = new Animation(this); }

	m_Velocity->Init();
	m_Sharder->Init();

	_partsTransFomr[0]->Init(); _partsTransFomr[0]->m_Position.y = 2.5f;
	_partsTransFomr[1]->Init();
	_partsTransFomr[2]->Init(); _partsTransFomr[2]->m_Scale = { -0.6f,-0.6f,-0.6f };
	_partsTransFomr[3]->Init(); _partsTransFomr[3]->m_Scale = { -0.6f,-0.6f,-0.6f };
	_partsTransFomr[4]->Init(); _partsTransFomr[4]->m_Scale = { -0.5f,-0.5f,-0.5f };
	_partsTransFomr[5]->Init(); _partsTransFomr[5]->m_Scale = { -0.5f,-0.5f,-0.5f };
	for (int i = 0; i < MAX_PARTS; i++) { _partsModel[i]->Init(); }
	for (int i = 0; i < MAX_PARTS; i++) { _partsAnimation[i]->Init(); }


	LoadModel();
}

void OtherPlayer::UpdateComponents()
{
	if (m_Velocity) { m_Velocity->Update(); };
	if (m_Sharder) { m_Sharder->Update(); }
}

void OtherPlayer::DrawComponents()
{
	if (m_Sharder) { m_Sharder->Draw(); }
}

void OtherPlayer::RemoveComponents()
{
	for (int i = 0; i < MAX_PARTS; i++) { if (_partsAnimation[i] != nullptr) { _partsAnimation[i]->Unit(); delete[] _partsAnimation[i]; } }
	for (int i = 0; i < MAX_PARTS; i++) { if (_partsModel[i] != nullptr) { _partsModel[i]->Unit(); delete[] _partsModel[i]; } }
	for (int i = 0; i < MAX_PARTS; i++) { if (_partsTransFomr[i] != nullptr) { _partsTransFomr[i]->Unit(); delete[] _partsTransFomr[i]; } }
	if (m_Sharder != nullptr) { m_Sharder->Unit(); delete m_Sharder; }
	if (m_Velocity != nullptr) { m_Velocity->Unit(); delete m_Velocity; }
}

void OtherPlayer::SetState(PLAYER_STATE state)
{
	if (_state != state)
	{
		_state = state;

		for (int i = 0; i < MAX_PARTS; i++) { _partsAnimation[i]->m_Count = 0; }

	}
}

void OtherPlayer::AnimationState()
{
	
}
