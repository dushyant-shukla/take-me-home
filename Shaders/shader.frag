#version 330 core

in vec2 textureCoordinates;
in vec3 outColor;

uniform sampler2D inTexture;
uniform bool useTexture;
uniform bool debug;
uniform bool useColor;

out vec4 fragColor;

void main() {

	if(useTexture) {
		fragColor = texture(inTexture, textureCoordinates);
	}
	else {
		if(debug && !useColor) {
			fragColor = vec4(0.0, 0.0, 0.0, 1.0);
			// vec2 pos = mod(gl_FragCoord.xy, vec2(50.0)) - vec2(25.0);
			// float dist_squared = dot(pos, pos);
			// fragColor = (dist_squared < 400.0) ? vec4(.90, .90, .90, 1.0) : vec4(.20, .20, .40, 1.0);
		} else {
			fragColor = vec4(outColor, 1.0f);
		}
	}
}