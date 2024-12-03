
#include "common.hlsl"

StructuredBuffer<float3> Position : register(t2);

void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

    //In.Position.x += (In.InstanceID % 100) * 2.0;
    //In.Position.z += In.InstanceID / 100;
    In.Position.xyz += Position[In.InstanceID];
	
	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse * Material.Diffuse;

}

