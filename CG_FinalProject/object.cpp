#include "object.h"


Object::Object()
{
    initPos();

    const vector<float> t{ {
      1, 0, -10, 0, 0, 1, 0, 1,
        1, 1, -10, 0, 0, 1, 0, 0,
        0, 1, -10, 0, 0, 1, 1, 0,
        1, 0, -10, 0, 0, 1, 0, 1,
        0, 1, -10, 0, 0, 1, 1, 0,
        0, 0, -10, 0, 0, 1, 1, 1  } };

    for (int i{}; i < t.size(); i += 8)
        normals.push_back(glm::vec3(t[i + 3], t[i + 4], t[i + 5]));

}

Object::Object(vector<float> vertices, vector<float> colors)
{
    initPos();
    initModel(vertices, colors);
}

Object::Object(vector<float> vertices, vector<float> colors, vector<GLubyte> indices)
{
    initPos();
    initModel(vertices, colors, indices);
}

void Object::initPos()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotate = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Object::setPos(glm::vec3 pos) { this->pos = pos; }
void Object::setPosX(float x) { this->pos.x = x; }
void Object::setPosY(float y) { this->pos.y = y; }
void Object::setPosZ(float z) { this->pos.z = z; }

void Object::setScale(glm::vec3 scale) { this->scale = scale; }
void Object::setScaleX(float x) { this->scale.x = x; }
void Object::setScaleY(float y) { this->scale.y = y; }
void Object::setScaleZ(float z) { this->scale.z = z; }

void Object::setRotate(glm::vec3 rotate) { this->rotate = rotate; }
void Object::setRotateX(float x) { this->rotate.x = x; }
void Object::setRotateY(float y) { this->rotate.y = y; }
void Object::setRotateZ(float z) { this->rotate.z = z; }

void Object::setColor(glm::vec3 color) { this->color = color; }
void Object::setColorR(float r) { this->color.r = r; }
void Object::setColorG(float g) { this->color.g = g; }
void Object::setColorB(float b) { this->color.b = b; }

glm::vec3 Object::getPos() { return pos; }
glm::vec3 Object::getScale() { return scale; }
glm::vec3 Object::getRotate() { return rotate; }
glm::vec3 Object::getColor() { return color; }


void Object::setModelPos(vector<float> vertices)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        this->vertices.push_back(vertices[i]);
    }
}
void Object::setModelColor(vector<float> colors)
{
    for (int i = 0; i < colors.size(); i++)
    {
        this->colors.push_back(colors[i]);
    }
}
void Object::setModelIndices(vector<GLubyte> indices)
{
    for (int i = 0; i < indices.size(); i++)
    {
        this->indices.push_back(indices[i]);
    }
}

void Object::initModel(vector<float> vertices, vector<float> colors)
{
    setModelPos(vertices);
    setModelColor(colors);
}

void Object::initModel(vector<float> vertices, vector<float> colors, vector<GLubyte> indices)
{
    setModelPos(vertices);
    setModelColor(colors);
    setModelIndices(indices);
}

void Object::init()
{
    initPos();
    initBuffer();
}

void Object::initBuffer()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &normBo);
    glBindBuffer(GL_ARRAY_BUFFER, normBo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    

    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    if (!indices.empty())
    {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);
    }
}

// Object 클래스 내의 renderShadowMapping 함수
void Object::renderShadowMapping(const glm::mat4& lightSpaceMatrix, GLuint id)
{
    // 사용할 프로그램을 설정
    glUseProgram(id);

    // 뷰 매트릭스와 프로젝션 매트릭스 설정
    glUniformMatrix4fv(glGetUniformLocation(id, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
    glUniformMatrix4fv(glGetUniformLocation(id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    
    // 오브젝트를 렌더링
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);

    // 프로그램 사용 종료
    //glUseProgram(0);
}

void Object::shadowRender(GLuint id)
{
    // 셰도우 맵 렌더링
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glViewport(0, 0, 800, 800);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 빛의 시점에서의 뷰 매트릭스 설정
    float fov = glm::radians(45.0f);
    float aspect = 800 / 800;
    float n = 1.0f;
    float f = 100.0f;

    glm::mat4 lightProjection = glm::perspective(fov, aspect, n, f);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0, 0.0, 0.5), glm::vec3(0.0-pos.x, 0.0 - pos.y, 0.5 - pos.z), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    // 그림자를 렌더링하는 오브젝트들을 빛의 시점에서 렌더링
    //for (auto& object : objects)
   // {
        /*object->*/renderShadowMapping(lightSpaceMatrix,id);
   // }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Object::shadowInit()
{
    // 셰도우 맵을 렌더링하기 위한 프레임버퍼 생성

    glGenFramebuffers(1, &shadowMapFBO);

    // 셰도우 맵 텍스처 생성
    GLuint shadowMapTexture;
    glGenTextures(1, &shadowMapTexture);
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 800, 800, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // 프레임버퍼에 깊이 맵 텍스처 연결
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowMapTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}