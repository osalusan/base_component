
#include "common.hlsl"


Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	if (Material.TextureEnable)
	{
		outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
		outDiffuse *= In.Diffuse;
	}
	else
	{
		outDiffuse = In.Diffuse;
    }

	// �A���t�@�N���b�v
    //clip(outDiffuse.a - 0.1);

	// �A���t�@�e�B�U
    float t = frac((In.TexCoord.x + In.TexCoord.y) * 200);
    clip(outDiffuse.a - t);
}
