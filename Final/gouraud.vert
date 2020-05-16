#version 120

// Gouraud shading vertex shader

// INCOMING DATA

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
uniform vec4 lightSourcePosition;

// Properties of the ambient light
uniform vec4 ambientLightColor;

// Vertex location (in model space)
attribute vec4 vPosition;

// Normal vector at vertex (in model space)
attribute vec3 vNormal;

// Model transformations
uniform vec3 theta;
uniform vec3 trans;
uniform vec3 scale;

// Camera parameters
uniform vec3 cPosition;
uniform vec3 cLookAt;
uniform vec3 cUp;

// View volume boundaries
uniform float left;
uniform float right;
uniform float top;
uniform float bottom;
uniform float near;
uniform float far;

// OUTGOING DATA

varying vec4 color;

void main()
{
    // Compute the sines and cosines of each rotation about each axis
    vec3 angles = radians( theta );
    vec3 c = cos( angles );
    vec3 s = sin( angles );

	// vector parameters
	vec3 vNorm;
	vec3 light;
	vec3 vPos;

    // Create rotation matrices
    mat4 rxMat = mat4( 1.0,  0.0,  0.0,  0.0,
                       0.0,  c.x,  s.x,  0.0,
                       0.0,  -s.x, c.x,  0.0,
                       0.0,  0.0,  0.0,  1.0 );

    mat4 ryMat = mat4( c.y,  0.0,  -s.y, 0.0,
                       0.0,  1.0,  0.0,  0.0,
                       s.y,  0.0,  c.y,  0.0,
                       0.0,  0.0,  0.0,  1.0 );

    mat4 rzMat = mat4( c.z,  s.z,  0.0,  0.0,
                       -s.z, c.z,  0.0,  0.0,
                       0.0,  0.0,  1.0,  0.0,
                       0.0,  0.0,  0.0,  1.0 );

    mat4 xlateMat = mat4( 1.0,     0.0,     0.0,     0.0,
                          0.0,     1.0,     0.0,     0.0,
                          0.0,     0.0,     1.0,     0.0,
                          trans.x, trans.y, trans.z, 1.0 );

    mat4 scaleMat = mat4( scale.x,  0.0,     0.0,     0.0,
                          0.0,      scale.y, 0.0,     0.0,
                          0.0,      0.0,     scale.z, 0.0,
                          0.0,      0.0,     0.0,     1.0 );

    // Create view matrix
    vec3 nVec = normalize( cPosition - cLookAt );
    vec3 uVec = normalize( cross (normalize(cUp), nVec) );
    vec3 vVec = normalize( cross (nVec, uVec) );

    mat4 viewMat = mat4( uVec.x, vVec.x, nVec.x, 0.0,
                         uVec.y, vVec.y, nVec.y, 0.0,
                         uVec.z, vVec.z, nVec.z, 0.0,
                         -1.0*(dot(uVec, cPosition)),
                         -1.0*(dot(vVec, cPosition)),
                         -1.0*(dot(nVec, cPosition)), 1.0 );

    // Create projection matrix
    mat4 projMat = mat4( (2.0*near)/(right-left), 0.0, 0.0, 0.0,
                         0.0, ((2.0*near)/(top-bottom)), 0.0, 0.0,
                         ((right+left)/(right-left)),
                         ((top+bottom)/(top-bottom)),
                         ((-1.0*(far+near)) / (far-near)), -1.0,
                         0.0, 0.0, ((-2.0*far*near)/(far-near)), 0.0 );

    // Transformation order:
    //    scale, rotate Z, rotate Y, rotate X, translate
    mat4 modelMat = xlateMat * rxMat * ryMat * rzMat * scaleMat;
    mat4 modelViewMat = viewMat * modelMat;

    // Transform the vertex location into clip space
    gl_Position =  projMat * viewMat  * modelMat * vPosition;

	// vector parameters
	vPos = (modelViewMat * vPosition).xyz;
	light = (modelMat * lightSourcePosition).xyz;
	vNorm = (normalize(modelViewMat * vec4(vNormal,0.0))).xyz;

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

	color = ambient + diffuse * lightSourceColor + specular;
}
