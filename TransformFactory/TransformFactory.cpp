#include "TransformFactory.h"
#include <glm/gtc/matrix_transform.inl>
#include <GLFW/glfw3.h>

glm::mat4 CreateSampleTransfrom()
{
    glm::mat4 trans;
    trans = glm::rotate(trans, 90.0f, glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    return trans;
}

glm::mat4 CreateTimelyRotation()
{
    glm::mat4 trans;
    trans = glm::rotate(trans, (GLfloat)glfwGetTime()*50.0f, glm::vec3(0.0, 0.0, 1.0));
    trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
    return trans;

}
