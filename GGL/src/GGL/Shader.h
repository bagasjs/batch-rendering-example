#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace GGL
{
	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const ShaderSource& shaderSource);
		Shader(const std::string& vsSourceFilePath, const std::string& fsSourceFilePath);
		~Shader();

		unsigned int GetRendererID() const { return m_RendererID; }
		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, const glm::vec2& value);
		void SetUniform3f(const std::string& name, const glm::vec3& value);
		void SetUniform4f(const std::string& name, const glm::vec4& value);
		void SetUniformMatrix3f(const std::string& name, const glm::mat3& matrix);
		void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix);


	public:
		static std::string LoadFile(const std::string& filePath);

	private:
		unsigned int CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		unsigned int CompileShader(unsigned int type, const std::string& source);

		int GetUniformLocation(const std::string& name);

	private:
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}