#version 330 core
	layout (location = 0) in vec3 position;	// 位置变量的属性位置值为 0
	out vec3 ourPosition;	// 向片段着色器输出顶点位置
	void main()
	{
	gl_Position = vec4(position, 1.0);
	ourPosition = position;
	}