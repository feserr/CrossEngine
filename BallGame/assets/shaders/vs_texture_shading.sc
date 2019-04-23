$input a_position, a_texcoord0, a_color0
$output v_texcoord0, v_color0

/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "bgfx_shader.sh"
#include "shaderlib.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_texcoord0 = a_texcoord0;
	v_color0 = a_color0;
}
