#include "sspch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

namespace soso {

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) {

		// Create empty handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send vertex shader source code to OpenGL
		// Reminder: std::string's .c_str is NULL character terminated
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile shader and verify status
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			SS_CORE_ERROR("{0}", infoLog.data());
			SS_CORE_ASSERT(false, "Vertex shader compilation failed.");
			return;
		}

		// Create empty handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send fragment shader source code to OpenGL
		// Reminder: std::string's .c_str is NULL character terminated
		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile shader and verify status
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shaders anymore.
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			SS_CORE_ERROR("{0}", infoLog.data());
			SS_CORE_ASSERT(false, "Fragment shader compilation failed.");
			return;
		}

		// Both shaders compiled successfully
		// Link them into a program

		// Get program obj
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach shaders
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link program
		glLinkProgram(program);

		// Verify linking
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			SS_CORE_ERROR("{0}", infoLog.data());
			SS_CORE_ASSERT(false, "Shader link failed.");
			return;
		}

		// Detach shaders after successful link
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}
}