#ifndef SHADERS // Защита от повторного включения
#define SHADERS

#include "engine.hpp" // Включение всех заголовочных файлов

// engine - пространство имен проекта

namespace engine
{
	// Загрузка исходного кода шейдеров из файла
	void loadShaderSource(std::string path, Chars& shader_source)
	{
		// path			 - путь к файлу с исходным кодом
		// shader_source - адрес записи исходного кода
		std::ifstream fin;
		fin.open(path);
		std::string input_source;
		while (!fin.eof())
			input_source += fin.get();
		input_source.pop_back();
		input_source.push_back('\0');
		fin.close();
		shader_source = new Char[input_source.length() + 1];
		for (Size i = 0; i < input_source.length(); i++)
			shader_source[i] = input_source[i];
		shader_source[input_source.length()] = '\0';
	}

	// Класс Шейдера
	class Shader
	{
	private:
		Uint id = 0U; // Идентификатор шейдера

		// Запрещено копирование и перезапись шейдера
		Shader(const Shader& other) {}
		Shader& operator=(const Shader& other) {}
	public:
		// Создание шейдера
		Shader(Uint type) 
		{
			id = glCreateShader(type);
		}

		// Геттер идентификатора шейдера
		Uint getID() const
		{
			return id;
		}

		// Запись исходного кода шейдера
		void changeSource(const Chars source)
		{
			glShaderSource(id, 1, &source, NULL);
		}

		// Компиляция исходного кода шейдера
		bool compile(Char info_log[512])
		{
			// info_log - информация об ошибках компиляции (так же возвращает статус компиляции)
			glCompileShader(id);
			Int success = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success)
				glGetShaderInfoLog(id, 512, NULL, info_log);
			return static_cast<bool>(success);
		}

		// Очистка шейдера
		void clear()
		{
			if (id != 0U)
			{
				glDeleteShader(id);
				id = 0U;
			}
		}

		// Уничтожение шейдера
		~Shader()
		{
			clear();
		}
	};

	// Класс Шейдерной программы 
	class ShaderProgram
	{
	private:
		Uint id = 0U; // Идентификатор шейдерной программы

		// Запрещено копирование и перезапись шейдерной программы
		ShaderProgram(const ShaderProgram& other) {}
		ShaderProgram& operator=(const ShaderProgram& other) {}
	public:
		// Создание шейдерной программы
		ShaderProgram(Uint vertex_shader_id, Uint fragment_shader_id)
		{
			// vertex_shader_id	  - идентификатор вершинного шейдера
			// fragment_shader_id - идентификатор фрагментного шейдера
			id = glCreateProgram();
			glAttachShader(id, vertex_shader_id);
			glAttachShader(id, fragment_shader_id);
		}

		// Геттер идентификатора шейдерной программы
		Uint getID() const
		{
			return id;
		}

		// Линковка шейдеров
		bool link(Char info_log[512])
		{
			// info_log - информация об ошибках линковки (так же возвращает статус линковки)
			glLinkProgram(id);
			Int success = 0;
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success)
				glGetProgramInfoLog(id, 512, NULL, info_log);
			return static_cast<bool>(success);
		}

		// Использование экземпляра шейдерной программы для следующего рендера
		void use() const
		{
			glUseProgram(id);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Float n) const
		{
			// var_name - имя uniform-переменной
			// n		- записываемое значение
			Uint n_loc = glGetUniformLocation(id, var_name.c_str());
			glUniform1f(n_loc, n);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Int n) const
		{
			// var_name - имя uniform-переменной
			// n		- записываемое значение
			Uint n_loc = glGetUniformLocation(id, var_name.c_str());
			glUniform1i(n_loc, n);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Vec4 v) const
		{
			// var_name - имя uniform-переменной
			// v		- записываемое значение
			Uint v_loc = glGetUniformLocation(id, var_name.c_str());
			Float v_ptr[4Ull];
			ptr(v, v_ptr);
			glUniform4fv(v_loc, 1, v_ptr);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Vec3 v) const
		{
			// var_name - имя uniform-переменной
			// v		- записываемое значение
			Uint v_loc = glGetUniformLocation(id, var_name.c_str());
			Float v_ptr[3Ull];
			ptr(v, v_ptr);
			glUniform3fv(v_loc, 1, v_ptr);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Vec2 v) const
		{
			// var_name - имя uniform-переменной
			// v		- записываемое значение
			Uint v_loc = glGetUniformLocation(id, var_name.c_str());
			Float v_ptr[2Ull];
			ptr(v, v_ptr);
			glUniform2fv(v_loc, 1, v_ptr);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Mat4 m) const
		{
			// var_name - имя uniform-переменной
			// m		- записываемое значение
			Uint m_loc = glGetUniformLocation(id, var_name.c_str());
			Float m_ptr[16Ull];
			ptr(m, m_ptr);
			glUniformMatrix4fv(m_loc, 1, GL_TRUE, m_ptr);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Mat3 m) const
		{
			// var_name - имя uniform-переменной
			// m		- записываемое значение
			Uint m_loc = glGetUniformLocation(id, var_name.c_str());
			Float m_ptr[9Ull];
			ptr(m, m_ptr);
			glUniformMatrix3fv(m_loc, 1, GL_TRUE, m_ptr);
		}

		// Запись значения uniform-переменной
		void setUniform(std::string var_name, Mat2 m) const
		{
			// var_name - имя uniform-переменной
			// m		- записываемое значение
			Uint m_loc = glGetUniformLocation(id, var_name.c_str());
			Float m_ptr[4Ull];
			ptr(m, m_ptr);
			glUniformMatrix2fv(m_loc, 1, GL_FALSE, m_ptr);
		}

		// Очистка шейдерной программы
		void clear()
		{
			if (id != 0U)
			{
				glDeleteProgram(id);
				id = 0U;
			}
		}

		// Уничтожение шейдерной программы
		~ShaderProgram()
		{
			clear();
		}
	};
}

#endif 