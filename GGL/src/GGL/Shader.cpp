#include "Shader.h"
#include "Utility.h"

#include <glad/glad.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void GLCheckError(bool info_on_no_error)
{
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        std::cout << "OpenGL error occured: " << err << std::endl;
    } else {
		if(info_on_no_error) std::cout << "No Error" << std::endl;
 	}
}

namespace GGL
{
	Shader::Shader(const ShaderSource& ss)
		: m_RendererID(0)
	{
		m_RendererID = CreateShaderProgram(ss.VertexSource, ss.FragmentSource);
	}

	Shader::Shader(const std::string& vsSourceFilePath, const std::string& fsSourceFilePath)
		: m_RendererID(0)
	{
		m_RendererID = CreateShaderProgram(LoadFile(vsSourceFilePath), LoadFile(fsSourceFilePath));
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		
		if(location == -1) printf("Warning: uniform %s doesn't exist!\n", name.c_str());

		m_UniformLocationCache[name] = location;
		return location;
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		Bind();
		glUniform1i(GetUniformLocation(name), value);
		Unbind();
	}

	void Shader::SetUniform1f(const std::string& name, float value)
	{
		Bind();
		glUniform1f(GetUniformLocation(name), value);
		Unbind();
	}

	void Shader::SetUniform2f(const std::string& name, const glm::vec2& value)
	{
		Bind();
		glUniform2f(GetUniformLocation(name), value.x, value.y);
		Unbind();
	}

	void Shader::SetUniform3f(const std::string& name, const glm::vec3& value)
	{
		Bind();
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
		Unbind();
	}

	void Shader::SetUniform4f(const std::string& name, const glm::vec4& value)
	{
		Bind();
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
		Unbind();
	}

	void Shader::SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix)
	{
		Bind();
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &(matrix[0][0]));
		Unbind();
	}

	void Shader::SetUniformMatrix3f(const std::string& name, const glm::mat3& matrix)
	{
		Bind();
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &(matrix[0][0]));
		Unbind();
	}

	unsigned int Shader::CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);
		return program;
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if(result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*) alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			printf("%s\n", message);
			glDeleteShader(id);
			return 0;
		}
		return id;
	}

	std::string Shader::LoadFile(const std::string& filePath)
	{
		std::ifstream file(filePath);

		std::stringstream ss;
		std::string line;

		while(getline(file, line))
		{
			ss << line << "\n";
		}

		return ss.str();
	}
}