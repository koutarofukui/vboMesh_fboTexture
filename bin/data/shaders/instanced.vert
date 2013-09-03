
#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor = vec4(1.0);
uniform	sampler2DRect tex0;			// we use this to sample depth data for our boxes.



in vec4  position;
in vec2  texcoord;
in vec4  color_coord;
in vec3  normal;

out vec4 colorVarying;		// we use flat colors, and, more importantly, flat normals, since we want crisp, flat shaded surfaces.
out vec2 texCoordVarying;



// ---------------------------------------------------------------------- 

void main()
{
    

	int iCount = 128;
    float fCount = float(iCount);

	float instanceX = float(gl_InstanceID%(iCount) - iCount/2) / 128.0;
	float instanceY = float(gl_InstanceID/(iCount) - iCount/2) / 128.0;
    int xc = gl_InstanceID%(iCount);  
    int yc = gl_InstanceID/(iCount);  

    //gl_TexCoord[0] = gl_MultiTexCood0;

    //vec4 pixelDepth = texture(tex0,vec2(instanceX +fCount/2.0 , instanceY +fCount/2.0));
    vec4 pixelDepth = texture(tex0,vec2(xc,yc));  
    //vec4 pixelDepth = texture(tex0,gl_TexCoord[0].st);
	
    colorVarying = vec4(globalColor.rgba);
	
	vec4 vPos = position;

    vPos.z += vPos.z * pixelDepth.r * 2000;

	vPos = vPos + vec4(instanceX*20*128,instanceY*10*128, 0,0);
    
	gl_Position = projectionMatrix * modelViewMatrix * vPos;
    
}