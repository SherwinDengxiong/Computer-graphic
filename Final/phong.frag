#version 120

// Phong shading fragment shader

// Material properties of the teapot and torus
uniform vec4 ambient_color;
uniform float ambient_reflection_coefficient;
uniform vec4 diffuse_color;
uniform float diffuse_reflection_coefficient;
uniform vec4 specular_color;
uniform float specular_exponent;
uniform float specular_reflection_coefficient;

// Properties of the light source
uniform vec4 lightSourceColor;

// Properties of the ambient light
uniform vec4 ambientLightColor;

varying vec3 vNorm;
varying vec3 light;
varying vec3 vPos;

void main()
{
	vec3 N = normalize(vNorm); // need for diffuse
	vec3 L = normalize(light - vPos);
	vec3 R = normalize (reflect(L, N)); // need for specular
    vec3 V = normalize (vPos);

	// ambient
	vec4 ambient = ambient_color * ambient_reflection_coefficient * ambientLightColor;

	// diffuse
	vec4 diffuse = diffuse_color * diffuse_reflection_coefficient * (dot(N, L));
	// the vectors have been normalized so we can replace cos by dot

	// specular
	vec4 specular = specular_color * specular_reflection_coefficient * pow(max(0.0, dot(V,R)), specular_exponent);

	gl_FragColor = ambient + diffuse * lightSourceColor + specular;
}
