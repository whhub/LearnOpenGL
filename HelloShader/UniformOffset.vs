#version 330 core
	layout (location = 0) in vec3 position;	// λ�ñ���������λ��ֵΪ 0
	layout (location = 1) in vec3 color;	// ��ɫ����������λ��ֵΪ 1
	out vec3 ourColor;	// ��Ƭ����ɫ�����һ����ɫ
	uniform float offset;
	void main()
	{
	gl_Position = vec4(position.x+offset, position.y, position.z, 1.0);
	ourColor = color;
	}