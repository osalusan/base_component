
#include "common.hlsl"

Texture2D g_Texture : register(t0); //0�ԃe�N�X�`���̏��
Texture2D g_TextureNormal : register(t1); //1�ԃe�N�X�`���̏��
SamplerState g_SamplerState : register(s0); //�T���v���[�O��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
//���̂�������ւ̃x�N�g��
    float4 lv = In.WorldPosition - Light.Position;
    //���̂ƌ����̋���
    float4 ld = length(lv);
    //�x�N�g���̐��K��
    lv = normalize(lv);
    
    //���̌���
    float ofs = 1.0f - lv;
    //0�����͂O�ɂ���
    ofs = max(0.0f, ofs);

    //�@���}�b�v�̃f�[�^���擾
    float4 localnormal = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
    //RGB�l���x�N�g���֖߂�
    localnormal = (localnormal * 2.0f) - 1.0f;
    localnormal.w = 1.0f;
    //���K��
    localnormal = normalize(localnormal);
    
    //�^���W�F���g
    float4 tangent = normalize(-In.Tangent);
    //�o�C�m�[�}��
    float4 binomal = normalize(In.Binormal);
    //�m�[�}��
    float4 normal = normalize(In.Normal);
    
    //�ڋ�Ԃ�\���s����쐬����
//    matrix mat = matrix(
//    tangent,//x��
//    binomal,//y��
//    normal,//z��
//    float4(0, 0, 0, 0)//���s�ړ��v�f�̓_�~�[
    
//);
    matrix mat = matrix(
    float4(-1, 0, 0, 0), //x��
    float4(0, 0, 1, 0), //y��
    float4(0, 1, 0, 0), //z��
    float4(0, 0, 0, 0) //���s�ړ��v�f�̓_�~�[
    
);
       
    //�@���}�b�v���̖@����ڋ�Ԃ֕ϊ�����
    normal = mul(localnormal, mat);
    normal = normalize(normal);
    
    //�����v�Z
    float light = 0.5f - 0.5f * dot(normal.xyz, lv.xyz);
    //����������Z
    light *= ofs;
    
    //�e�N�X�`���̃s�N�Z�����擾
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    //���_�F������
    outDiffuse.rgb *= In.Diffuse.rgb;
    //���邳�̍���
    outDiffuse.rgb *= light;
    
    //���̏���
    outDiffuse.a *= In.Diffuse.a;
    //�����̉��Z
    outDiffuse.rgb += Light.Ambient.rgb;
    
    //�J��������s�N�Z���֌������x�N�g��
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    //���K��
    eyev = normalize(eyev);
    //�n�[�t�x�N�g��
    float3 halfv = eyev + lv.xyz;
    //���K��
    halfv = normalize(halfv);
    
    
    //�X�y�L�����[�̌v�Z
    float specular = -dot(halfv, normal.xyz);
    specular = saturate(specular);
    specular = pow(specular, 10);
     //�X�y�L�����[�̉��Z
    outDiffuse.rgb += (specular * ofs);
    
    

}