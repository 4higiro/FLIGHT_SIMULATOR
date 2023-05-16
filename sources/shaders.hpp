#ifndef SHADERS // ������ �� ���������� ���������
#define SHADERS

#include "engine.hpp" // ��������� ���� ������������ ������

// engine - ������������ ���� �������

namespace engine
{
	// �������� ��������� ���� �������� �� �����
	void loadShaderSource(std::string path, char*& shader_source)
	{
		// path			 - ���� � ����� � �������� �����
		// shader_source - ����� ������ ��������� ����
		std::ifstream fin;
		fin.open(path);
		std::string input_source;
		while (!fin.eof())
			input_source += fin.get();
		input_source.pop_back();
		input_source.push_back('\0');
		shader_source = (char*)input_source.c_str();
		fin.close();
	}

	// ����� �������
	class Shader
	{
	private:
		Uint id = 0U; // ������������� �������

		// ��������� ����������� � ���������� �������
		Shader(const Shader& other) {}
		Shader& operator=(const Shader& other) {}
	public:
		// �������� �������
		Shader(Uint type) 
		{
			id = glCreateShader(type);
		}

		// ������ �������������� �������
		Uint getID() const
		{
			return id;
		}

		// ������ ��������� ���� �������
		void changeSource(const char* source)
		{
			glShaderSource(id, 1, &source, NULL);
		}

		// ���������� ��������� ���� �������
		bool compile(Char info_log[512])
		{
			// info_log - ���������� �� ������� ���������� (��� �� ���������� ������ ����������)
			glCompileShader(id);
			Int success = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success)
				glGetShaderInfoLog(id, 512, NULL, info_log);
			return static_cast<bool>(success);
		}

		// ������� �������
		void clear()
		{
			if (id != 0U)
			{
				glDeleteShader(id);
				id = 0U;
			}
		}

		// ����������� �������
		~Shader()
		{
			clear();
		}
	};

	// ����� ��������� ��������� 
	class ShaderProgram
	{
	private:
		Uint id = 0U; // ������������� ��������� ���������

		// ��������� ����������� � ���������� ��������� ���������
		ShaderProgram(const ShaderProgram& other) {}
		ShaderProgram& operator=(const ShaderProgram& other) {}
	public:
		// �������� ��������� ���������
		ShaderProgram(Uint vertex_shader_id, Uint fragment_shader_id)
		{
			// vertex_shader_id	  - ������������� ���������� �������
			// fragment_shader_id - ������������� ������������ �������
			id = glCreateProgram();
			glAttachShader(id, vertex_shader_id);
			glAttachShader(id, fragment_shader_id);
		}

		// ������ �������������� ��������� ���������
		Uint getID() const
		{
			return id;
		}

		// �������� ��������
		bool link(Char info_log[512])
		{
			// info_log - ���������� �� ������� �������� (��� �� ���������� ������ ��������)
			glLinkProgram(id);
			Int success = 0;
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success)
				glGetProgramInfoLog(id, 512, NULL, info_log);
			return static_cast<bool>(success);
		}

		// ������������� ���������� ��������� ��������� ��� ���������� �������
		void use() const
		{
			glUseProgram(id);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Float n) const
		{
			// var_name - ��� uniform-����������
			// n		- ������������ ��������
			Uint n_loc = glGetUniformLocation(id, var_name.c_str());
			glUniform1f(n_loc, n);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Int n) const
		{
			// var_name - ��� uniform-����������
			// n		- ������������ ��������
			Uint n_loc = glGetUniformLocation(id, var_name.c_str());
			glUniform1i(n_loc, n);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Vec4 v) const
		{
			// var_name - ��� uniform-����������
			// v		- ������������ ��������
			Uint v_loc = glGetUniformLocation(id, var_name.c_str());
			Float v_ptr[4Ull];
			ptr(v, v_ptr);
			glUniform4fv(v_loc, 1, v_ptr);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Vec3 v) const
		{
			// var_name - ��� uniform-����������
			// v		- ������������ ��������
			Uint v_loc = glGetUniformLocation(id, var_name.c_str());
			Float v_ptr[3Ull];
			ptr(v, v_ptr);
			glUniform3fv(v_loc, 1, v_ptr);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Vec2 v) const
		{
			// var_name - ��� uniform-����������
			// v		- ������������ ��������
			Uint v_loc = glGetUniformLocation(id, var_name.c_str());
			Float v_ptr[2Ull];
			ptr(v, v_ptr);
			glUniform2fv(v_loc, 1, v_ptr);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Mat4 m) const
		{
			// var_name - ��� uniform-����������
			// m		- ������������ ��������
			Uint m_loc = glGetUniformLocation(id, var_name.c_str());
			Float m_ptr[16Ull];
			ptr(m, m_ptr);
			glUniformMatrix4fv(m_loc, 1, GL_TRUE, m_ptr);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Mat3 m) const
		{
			// var_name - ��� uniform-����������
			// m		- ������������ ��������
			Uint m_loc = glGetUniformLocation(id, var_name.c_str());
			Float m_ptr[9Ull];
			ptr(m, m_ptr);
			glUniformMatrix3fv(m_loc, 1, GL_TRUE, m_ptr);
		}

		// ������ �������� uniform-����������
		void setUniform(std::string var_name, Mat2 m) const
		{
			// var_name - ��� uniform-����������
			// m		- ������������ ��������
			Uint m_loc = glGetUniformLocation(id, var_name.c_str());
			Float m_ptr[4Ull];
			ptr(m, m_ptr);
			glUniformMatrix2fv(m_loc, 1, GL_FALSE, m_ptr);
		}

		// ������� ��������� ���������
		void clear()
		{
			if (id != 0U)
			{
				glDeleteProgram(id);
				id = 0U;
			}
		}

		// ����������� ��������� ���������
		~ShaderProgram()
		{
			clear();
		}
	};
}

#endif 