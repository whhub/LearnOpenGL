#version 330 core
	layout (location = 0) in vec3 position;	// λ�ñ���������λ��ֵΪ 0
	out vec3 ourPosition;	// ��Ƭ����ɫ���������λ��
	void main()
	{
	gl_Position = vec4(position, 1.0);
	ourPosition = position;
	}