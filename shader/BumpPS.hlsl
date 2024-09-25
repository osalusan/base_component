
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
    float ofs = 1.0f - (1.0f / Light.PointLightParam) * ld;
    //0�����͂O�ɂ���
    ofs = max(0, ofs);

    //�@���}�b�v
    float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
    //RGB=>�x�N�g���ɖ߂�
    normalMap = (normalMap * 2.0f) - 1.0f;
    //�@���Ƃ��ĕϐ��֊i�[����
    float4 normal;
    normal.x = -normalMap.x;
    normal.y = normalMap.y;
    normal.z = normalMap.y;
    normal.w = 0.0f;
    
    //�s�N�Z���̖@���𐳋K��
    normal = normalize(normal);
    //�����v�Z
    float light = 0.5f - 0.5f * dot(normal.xyz, lv.xyz);
    //����������Z
    light *= ofs;
    
    //�e�N�X�`���̃s�N�Z������
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    //�F�ɖ��邳����Z
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    //���̏���
    outDiffuse.a *= In.Diffuse.a;
    //�����̉��Z
    outDiffuse.rgb += Light.Ambient.rgb;
    
    //�J��������s�N�Z���Ɍ������x�N�g��
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    //���K��
    eyev = normalize(eyev);
    
    //�n�[�t�x�N�g���̌v�Z
    float3 halfv = eyev + lv.xyz;
    //���K��
    halfv = normalize(halfv);
    
    //�X�y�L�����[�̌v�Z
    float specular = -dot(halfv, normal.xyz); //���ʔ��˂̌v�Z
    specular = saturate(specular); 
    specular = pow(specular, 10);
    
    outDiffuse.rgb += specular; //�X�y�L�����l���f�t���[�Y�Ƃ��đ���

}