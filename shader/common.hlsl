//���̃t�@�C���͑��̃V�F�[�_�[�t�@�C���փC���N���[�h����܂�
// �e��}�g���N�X��x�N�g�����󂯎��ϐ���p��
cbuffer WorldBuffer : register(b0) //�萔�o�b�t�@ 0 ��
{
    matrix World;
}
cbuffer ViewBuffer : register(b1) //�萔�o�b�t�@ 1 ��
{
    matrix View;
}
cbuffer ProjectionBuffer : register(b2) //�萔�o�b�t�@ 2 ��
{
    matrix Projection;
}

struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    bool TextureEnable;
    float2 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}

//���_�V�F�[�_�[�֓��͂����f�[�^���\���̂̌`�ŕ\��
//����͒��_�o�b�t�@�̓��e���̂���
struct VS_IN
{
    float4 Position : POSITION0; //�Z�}���e�B�N�X�͒��_���C�A�E�g�ɍ��킹��
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    float4 Tangent : TANGENT;
}; //�\������|���S���̃��C�A�E�g�Ɠ���
//�s�N�Z���V�F�[�_�[�֓��͂����f�[�^���\���̂̌`�ŕ\��
struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    float4 Tangent : TANGENT0;
    float4 Binormal : BINORMAL0;
};
//���C�g�\���̂̒�`�@C���ꑤ��LIGHT�\���̂Ɠ������e
struct LIGHT
{
    bool Enable;
    bool3 Dummy;
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
    float4 SkyColor; //�V���F
    float4 GroundColor; //�n�ʐF
    float4 GroundNormal; //�n�ʖ@��
    
    float4 Position; //���̍��W
    float4 PointLightParam;
    float4 Angle; //�X�|�b�g���C�g�̃R�[��
};
cbuffer LightBuffer : register(b4) //�R���X�^���g�o�b�t�@�S�ԂŎ󂯎��
{
    LIGHT Light; //���C�g�^�\���̂Ƃ��ė��p����
}

cbuffer CameraBuffer : register(b5) //�o�b�t�@�̂T�ԂƂ���
{
    float4 CameraPosition; //�J�������W���󂯎��ϐ�
}

//---------------------------------
//�ėp�p�����[�^�󂯎��p
//---------------------------------
cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter; //C���ꑤ����󂯎��
    
   
}
