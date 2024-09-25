#pragma once
#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    //���_�̕ϊ�
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.Position = mul(In.Position, wvp); //���_�ϊ�
    
    //���_�@�������[���h�s��ŕϊ�
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0f);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    Out.Normal = worldNormal;
    
    //���_�̃f�t���[�Y���o��
    Out.Diffuse = In.Diffuse; //���邳�̒l�𒸓_�F�Ƃ��ďo��  
    //�e�N�X�`�����W���o��
    Out.TexCoord = In.TexCoord;
    //���[���h�ϊ��������_���W�����
    Out.WorldPosition = mul(In.Position, World);
    
    //�^���W�F���g�����[���h�ϊ�
    float4 worldTangent, tangent;
    tangent = float4(In.Normal.xyz, 0.0f);
    worldTangent = mul(tangent, World);
    worldTangent = normalize(worldTangent);
    Out.Tangent = worldTangent;
    
    //�o�C�m�[�}��
    float4 worldBinormal;
    worldBinormal = 0;
    worldBinormal.xyz = cross(worldTangent.xyz, worldNormal.xyz);
    worldBinormal = normalize(worldBinormal);
    Out.Binormal = worldBinormal;

}