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
	InitComponent();
}

void OtherPlayer::Uninit()
{
	RemoveComponent();
}

void OtherPlayer::Update()
{

	//À•W‚ÌÝ’è
	if (_Velocity)
	{
		_TransForm->_Position.x += _Velocity->_Velocity.x;
		_TransForm->_Position.y += _Velocity->_Velocity.y;
		_TransForm->_Position.z += _Velocity->_Velocity.z;
	}

	
	AnimationState();
	UpdateComponent();
}

void OtherPlayer::Draw()
{

	XMMATRIX world, scl, rot, trans;

	scl = XMMatrixScaling(_TransForm->_Scale.x, _TransForm->_Scale.y, _TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x + _partsTransFomr[0]->_Position.x, _TransForm->_Position.y + _partsTransFomr[0]->_Position.y, _TransForm->_Position.z + _partsTransFomr[0]->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[0]) { _partsModel[0]->Draw(); }

	scl = XMMatrixScaling(_TransForm->_Scale.x, _TransForm->_Scale.y, _TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x + _partsTransFomr[1]->_Position.x, _TransForm->_Position.y + _partsTransFomr[1]->_Position.y, _TransForm->_Position.z + _partsTransFomr[1]->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[1]) { _partsModel[1]->Draw(); }

	scl = XMMatrixScaling(_TransForm->_Scale.x + _partsTransFomr[2]->_Scale.x, _TransForm->_Scale.y + _partsTransFomr[2]->_Scale.y, _TransForm->_Scale.z + _partsTransFomr[2]->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x + _partsTransFomr[2]->_Position.x, _TransForm->_Position.y + _partsTransFomr[2]->_Position.y, _TransForm->_Position.z + _partsTransFomr[2]->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[2]) { _partsModel[2]->Draw(); }

	scl = XMMatrixScaling(_TransForm->_Scale.x + _partsTransFomr[3]->_Scale.x, _TransForm->_Scale.y + _partsTransFomr[3]->_Scale.y, _TransForm->_Scale.z + _partsTransFomr[3]->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x + _partsTransFomr[3]->_Position.x, _TransForm->_Position.y + _partsTransFomr[3]->_Position.y, _TransForm->_Position.z + _partsTransFomr[3]->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[3]) { _partsModel[3]->Draw(); }

	scl = XMMatrixScaling(_TransForm->_Scale.x + _partsTransFomr[4]->_Scale.x, _TransForm->_Scale.y + _partsTransFomr[4]->_Scale.y, _TransForm->_Scale.z + _partsTransFomr[4]->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x + _partsTransFomr[4]->_Position.x, _TransForm->_Position.y + _partsTransFomr[4]->_Position.y, _TransForm->_Position.z + _partsTransFomr[4]->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[4]) { _partsModel[4]->Draw(); }

	scl = XMMatrixScaling(_TransForm->_Scale.x + _partsTransFomr[5]->_Scale.x, _TransForm->_Scale.y + _partsTransFomr[5]->_Scale.y, _TransForm->_Scale.z + _partsTransFomr[5]->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x + _partsTransFomr[5]->_Position.x, _TransForm->_Position.y + _partsTransFomr[5]->_Position.y, _TransForm->_Position.z + _partsTransFomr[5]->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	if (_partsModel[5]) { _partsModel[5]->Draw(); }

	DrawComponent();
}

void OtherPlayer::InitComponent()
{
	_Velocity = new Velocity(this);
	_Sharder = new Sharder(this);
	for (int i = 0; i < MAX_PARTS; i++) { _partsTransFomr[i] = new TransForm(this); }
	for (int i = 0; i < MAX_PARTS; i++) { _partsModel[i] = new ModelRenderer(this); }
	for (int i = 0; i < MAX_PARTS; i++) { _partsAnimation[i] = new Animation(this); }

	_Velocity->Init();
	_Sharder->Init();

	_partsTransFomr[0]->Init(); _partsTransFomr[0]->_Position.y = 2.5f;
	_partsTransFomr[1]->Init();
	_partsTransFomr[2]->Init(); _partsTransFomr[2]->_Scale = { -0.6f,-0.6f,-0.6f };
	_partsTransFomr[3]->Init(); _partsTransFomr[3]->_Scale = { -0.6f,-0.6f,-0.6f };
	_partsTransFomr[4]->Init(); _partsTransFomr[4]->_Scale = { -0.5f,-0.5f,-0.5f };
	_partsTransFomr[5]->Init(); _partsTransFomr[5]->_Scale = { -0.5f,-0.5f,-0.5f };
	for (int i = 0; i < MAX_PARTS; i++) { _partsModel[i]->Init(); }
	for (int i = 0; i < MAX_PARTS; i++) { _partsAnimation[i]->Init(); }


	LoadModel();
}

void OtherPlayer::UpdateComponent()
{
	if (_Velocity) { _Velocity->Update(); };
	if (_Sharder) { _Sharder->Update(); }
}

void OtherPlayer::DrawComponent()
{
	if (_Sharder) { _Sharder->Draw(); }
}

void OtherPlayer::RemoveComponent()
{
	for (int i = 0; i < MAX_PARTS; i++) { if (_partsAnimation[i] != nullptr) { _partsAnimation[i]->Unit(); delete[] _partsAnimation[i]; } }
	for (int i = 0; i < MAX_PARTS; i++) { if (_partsModel[i] != nullptr) { _partsModel[i]->Unit(); delete[] _partsModel[i]; } }
	for (int i = 0; i < MAX_PARTS; i++) { if (_partsTransFomr[i] != nullptr) { _partsTransFomr[i]->Unit(); delete[] _partsTransFomr[i]; } }
	if (_Sharder != nullptr) { _Sharder->Unit(); delete _Sharder; }
	if (_Velocity != nullptr) { _Velocity->Unit(); delete _Velocity; }
}

void OtherPlayer::SetState(PLAYER_STATE state)
{
	if (_state != state)
	{
		_state = state;

		for (int i = 0; i < MAX_PARTS; i++) { _partsAnimation[i]->_count = 0; }

	}
}

void OtherPlayer::AnimationState()
{
	
}
