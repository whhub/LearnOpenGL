#include "TextureFactory.h"
#include "soil.h"


GLuint GenTexture(const char * textureFilePath)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ

    // ���ز���������
    int width, height;
    unsigned char* image = SOIL_load_image(textureFilePath, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

