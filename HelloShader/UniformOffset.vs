#version 330 core
	layout (location = 0) in vec3 position;	// 位置变量的属性位置值为 0
	layout (location = 1) in vec3 color;	// 颜色变量的属性位置值为 1
	out vec3 ourColor;	// 向片段着色器输出一个颜色
	uniform float offset;
	void main()
	{
	gl_Position = vec4(position.x+offset, position.y, position.z, 1.0);
	ourColor = color;
	}