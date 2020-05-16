//
// Vertex shader for the transformation assignment
//
// Created by Warren R. Carithers 2016/04/22.
//
// Contributor:  sherwin dengxiong
//

#version 150

// attribute:  vertex position
in vec4 vPosition;

// add other global shader variables to hold the
// parameters your application code is providing

uniform float Projectiontype;

float left = -1.0;
float right = 1.0;
float top = 1.0;
float bottom = -1.0;
float near = 0.9;
float far = 5.0;
//view parameters
uniform vec3 eye;
uniform vec3 lookat;
uniform vec3 up;
//transform parameters
uniform vec3 scal; 
uniform vec3 rota;
uniform vec3 transform;
//translate matrix
void translate(out mat4 trans) {
	trans = mat4(	1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			transform.x, transform.y, transform.z, 1.0);
}
//set scale matrix
void scale(out mat4 sc) {
	sc = mat4(scal.x, 0.0, 0.0, 0.0,
		0.0, scal.y, 0.0, 0.0,
		0.0, 0.0, scal.z, 0.0,
		0.0, 0.0, 0.0, 1.0);
}
//set rotate matrix
void rotate(out mat4 ro) {
	vec3 angle = rota/360*3.1415926; 
	vec3 cos = cos(angle);
	vec3 sin = sin(angle);

	//rotate along x coordinate
	mat4 xcoor = mat4(      1.0, 1.0, 0.0, 0.0,
				0.0, cos.x, sin.x, 0.0,
				0.0, -sin.x, cos.x, 0.0,
				0.0, 0.0, 0.0, 1.0);
	//rotate along y coordinate
	mat4 ycoor = mat4(      cos.y, 0.0, -sin.y, 0.0,
				0.0, 1.0, 0.0, 0.0,
				sin.y, 0.0, cos.y, 0.0,
				0.0, 0.0, 0.0, 1.0);
	//rotate along z coordinate
	mat4 zcoor = mat4(      cos.z, -sin.z, 0.0, 0.0,
				sin.z, cos.z, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0);
	ro = zcoor * ycoor * xcoor;
}
//set view matrix
void setView(out mat4 viewdirection) {
	vec3 n = normalize(eye - lookat);
	vec3 u = normalize(cross(up, n));
	vec3 v = cross(n, u);

	viewdirection = mat4(   u.x, v.x, n.x, 0.0,
				u.y, v.y, n.y, 0.0,
				u.z, v.z, n.z, 0.0,
				-1.0 * dot(u, eye), -1.0 * dot(v, eye), -1.0 * dot(n, eye), 1.0);
}
//set frustum matrix
void setFrustum(out mat4 projections) {
	projections = mat4((near) / (right - left), 0, 0, 0,
			   0, ( near) / (top - bottom), 0, 0,
			   (right + left) / (right - left), (top + bottom) / (top - bottom), (-far - near) / (far - near), -1,
			    0, 0, (-2 * far * near) / (far - near), 0);
}

void setOrtho(out mat4 projections) {
	projections = mat4(1/ (right - left), 0.0, 0, 0,
			   0, 1 / (top - bottom), 0, 0,
			   0, 0, (-far - near) / (far - near), -1,
			   (right + left) / (right - left), (top + bottom) / (top - bottom), (-2 * far * near) / (far - near), 0);
}
void main()
{
    // By default, no transformations are performed.
    mat4 projections, viewdirection;
    mat4 sc, ro, tr; 
	setView(viewdirection);
	if (Projectiontype == 2.0) {
		setOrtho(projections);
	}
	else {
		setFrustum(projections);
	}
	translate(tr);
	scale(sc);
	rotate(ro);

	gl_Position = projections * viewdirection * sc  * tr * vPosition;
}







