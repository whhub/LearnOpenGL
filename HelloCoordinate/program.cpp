#include "gl/glew.h"            // glew first
#include "program.h"
#include "TextureFactory.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/matrix_transform.inl>


void DrawCabinetTexturePerspective(GLFWwindow* window, GLuint shaderProgram)
{
        // Vertex Buffer
    GLfloat vertices[] = {
//     ---- 位置 ----      - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // 左上
    };
    GLuint indices[] = {
        0, 1, 3,    // First Triangle
        1, 2, 3     // Second Triangle
    };

;


    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    // 纹理属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);       // Unbind VAO


    // 生成纹理
    GLuint texture1 = GenTexture("container.jpg");
    GLuint texture2 = GenTexture("awesomeface.png");


    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
	
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

        glUniform1f(glGetUniformLocation(shaderProgram, "mixValue"), 0.5);


        // Create transformations
        glm::mat4 model, view, projection;
        model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        projection = glm::perspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);


        //get their uniform location
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
        //pass them to the shaders
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        // Draw container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);    
}
