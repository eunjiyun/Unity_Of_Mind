#include "base.h"

void Base::init()
{
    const vector<float> baseVertices = {
        -.5f, 0.f, -1.f,
        .4f, 0.f, -1.f,
        .4f, 0.f, 1.f,
        -.5f, 0.f, 1.f };
    const vector<float> baseColor = {
        0.f, 1.f, 0.f,
        1.f, 0.f, 0.f,
        0.f, 0.f, 1.f,
        1.f, .5f, 1.f };
    const vector<GLubyte> baseIndices = {
        0, 1, 2,
        0, 2, 3 };

    // ¹Ù´Ú »ö
    color = glm::vec3(0.5f, 0.5f, 0.5f);

    initModel(baseVertices, baseColor, baseIndices);
    initPos();
    initBuffer();
}

void Base::render(GLuint shaderProgramID)
{
    model = glm::mat4(1.f);

    glUniform3f(glGetUniformLocation(shaderProgramID, "fColor"), color.r, color.g, color.b);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

