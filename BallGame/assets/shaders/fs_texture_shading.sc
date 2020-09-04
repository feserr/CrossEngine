$input v_texcoord0, v_color0

/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "bgfx_shader.sh"
#include "shaderlib.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 color = toLinear(texture2D(s_texColor, v_texcoord0.xy*0.5+0.5) );

	gl_FragColor = v_color0 * color;
}
