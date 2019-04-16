$input v_texcoord0, v_color0

/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "bgfx_shader.sh"
#include "shaderlib.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 color = toLinear(texture2D(s_texColor, v_texcoord0) );

	gl_FragColor.xyz = v_color0.xyz * color.xyz;
	gl_FragColor.w = 1.0;
	//gl_FragColor = toGamma(gl_FragColor);
	//gl_FragColor = texture2D(s_texColor, v_texcoord0.xy*0.5+0.5);
}
