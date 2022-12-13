#include <glad/glad.h>
#include <GGL/Window.h>
#include <GGL/Shader.h>
#include <GGL/Texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <array>

struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
};

struct Vec4
{
    float x, y, w, h;
};

struct Vertex
{
    Vec3 Position;
    Vec4 Color;
    Vec2 TexCoords;
    float TexID;
};

static Vertex* CreateQuad(Vertex* target, float width, float height, float x, float y, float textureID) {
    target->Position = { x, y, 0.0f, };
    target->Color = { 0.18f, 0.6f, 0.16f, 1.0f, };
    target->TexCoords = { 0.0f, 0.0f, };
    target->TexID = textureID;
    target++;

    target->Position = { x + width, y, 0.0f, };
    target->Color = { 0.98f, 0.1f, 0.96f, 1.0f,  };
    target->TexCoords = { 1.0f, 0.0f, };
    target->TexID = textureID;
    target++;

    target->Position = { x + width, y + height, 0.0f, };
    target->Color = { 0.18f, 0.6f, 0.16f, 1.0f, };
    target->TexCoords = { 1.0f, 1.0f, };
    target->TexID = textureID;
    target++;

    target->Position = { x, y + height, 0.0f, };
    target->Color = { 0.98f, 0.1f, 0.96f, 1.0f, };
    target->TexCoords = { 0.0f, 1.0f, };
    target->TexID = textureID;
    target++;

    return target;
}

int main(int argc, char** argv)
{
    GGL::WindowOptions opts;
    opts.CoreProfile = true;
    GGL::Window win(opts);
    win.EnableVSync();

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int ganyu1 = GGL::LoadTexture("res/camp.png");
    unsigned int ganyu2 = GGL::LoadTexture("res/bronya.png");

    GGL::BindTexture(ganyu1, 0);
    GGL::BindTexture(ganyu2, 1);

    GGL::Shader shader("res/basic.v.glsl", "res/basic.f.glsl");
    const size_t MaxQuadCount = 1000;
    const size_t MaxVertexCount = MaxQuadCount * 4;
    const size_t MaxIndexCount = MaxQuadCount * 6;

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID));

    // uint32_t indices[] = {
    //     0, 1, 2, 2, 3, 0,
    //     4, 5, 6, 6, 7, 4,
    // };

    uint32_t indices[MaxIndexCount];
    uint32_t offset = 0;
    for(size_t i = 0; i < MaxIndexCount; i+=6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;
        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;
        offset+=4;
    }

    uint32_t ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader.Bind();
    auto location = glGetUniformLocation(shader.GetRendererID(), "u_Textures");
    int samplers[] = { 0, 1 };
    glUniform1iv(location, 2, samplers);

    glm::mat4 proj = glm::ortho(0.0f, (float)opts.Width, 0.0f, (float)opts.Height, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 mvp = proj * view * model;

    shader.SetUniformMatrix4f("u_MVP", mvp);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    shader.Unbind();

    glClearColor(0.1f, 0.1f, 0.1, 1.0f);

    float posq1 = 0;
    float posq2 = 110;
    float speed = 10.0f;
    while(win.IsOpen())
    {
        win.Clear();
        // Set dynamic buffer
        uint32_t indexCount = 0;
        std::array<Vertex, 1000> vertices;
        Vertex* buffer = vertices.data();
        for(int y = 0; y < 3; y++)
        {
            for(int x = 0; x < 3; x++)
            {
                buffer  = CreateQuad(buffer, 100, 100, x * 100, y * 100, (x+y)%2);
                indexCount += 6;
            }
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

        shader.Bind();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
        win.Update();
    }
}