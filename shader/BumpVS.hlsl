
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

}