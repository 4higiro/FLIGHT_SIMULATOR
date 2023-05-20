#ifndef BUFFER_OBJECTS // Защита от повторного включения
#define BUFFER_OBJECTS

#include "engine.hpp" // Включение всех заголовочных файлов

// engine - пространство имен проекта

namespace engine
{
	// Класс Объекта Вершинного Буфера
	class VBO
	{
	private:
		mutable Uint id = 0U; // Идентификатор буфера

		// Запрещено копировать и перезаписывать экземпляры буфера
		VBO(const VBO& other) {}
		VBO& operator=(const VBO& other) {}

		friend class Mesh; // Закрытые поля и методы доступны в классе Mesh
	public:
		// Отвязка буфера в контексте OpenGL
		static void resetBind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0U);
		}

		// Создание буфера
		VBO()
		{
			glGenBuffers(1, &id);
		}

		// Геттер идентификатора буфера
		Uint getID() const
		{
			return id;
		}

		// Связывание буфера с контекстом OpenGL
		void bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		// Загрузка данных буфера на видеокарту
		void data(const Float* data, Size n, Uint mode)
		{
			// data - Все данные о вершинах 
			// n	- Размер массива с данными
			// mode - Режим хранения
			glBufferData(GL_ARRAY_BUFFER, n, data, mode);
		}

		// Очистка буфера
		void clear()
		{
			if (id != 0U)
			{
				glDeleteBuffers(1, &id);
				id = 0U;
			}
		}

		// Уничтожение буфера
		~VBO()
		{
			clear();
		}
	};

	// Класс Объекта Элементного Буфера
	class EBO
	{
	private:
		mutable Uint id = 0U; // Идентификатор буфера

		// Запрещено копировать и перезаписывать экземпляры буфера
		EBO(const VBO& other) {}
		EBO& operator=(const VBO& other) {}

		friend class Mesh; // Закрытые поля и методы доступны в классе Mesh
	public:
		// Отвязка буфера в контексте OpenGL
		static void resetBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0U);
		}

		// Создание буфера
		EBO()
		{
			glGenBuffers(1, &id);
		}

		// Геттер идентификатора буфера
		Uint getID() const
		{
			return id;
		}

		// Связывание буфера с контекстом OpenGL
		void bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		// Загрузка данных буфера на видеокарту
		void data(const Uint* data, Size n, Uint mode)
		{
			// data - Индесы (порядок рендера вершин из вершинного массива)
			// n	- Размер массива с данными
			// mode - Режим хранения
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, n, data, mode);
		}

		// Рендер всех вершин по элементам буфера
		void draw(Uint shp_id, Int vertex_count) const
		{
			// shp_id		- идентификатор шейдерной программы 
			// vertex_count - количество рисуемых вершин
			glUseProgram(shp_id);
			glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, NULL);
		}

		// Очистка буфера
		void clear()
		{
			if (id != 0U)
			{
				glDeleteBuffers(1, &id);
				id = 0U;
			}
		}

		// Уничтожение буфера
		~EBO()
		{
			clear();
		}
	};

	// Класс Объекта Вершинного Массива
	class VAO
	{
	private:
		mutable Uint id = 0; // Идентификатор массива

		// Заприщено копировать и перезаписывать экзмепляры массива
		VAO(const VAO& other) {}
		VAO& operator=(const VAO& other) {}

		friend class Mesh; // Закрытые поля и методы доступны в классе Mesh
	public:
		// Отвязка массива от контекста OpenGL
		static void resetBind()
		{
			glBindVertexArray(0U);
		}

		// Создание массива
		VAO()
		{
			glGenVertexArrays(1, &id);
		}

		// Геттер идентификатора массива
		Uint getID() const
		{
			return id;
		}

		// Связывание массива с контекстом OpenGL
		void bind() const
		{
			glBindVertexArray(id);
		}

		// Разметка данных буфера, связанного с экземпляром вершинного массива
		void setBuffDataConfig(Uint attrib_index, Int number_count, Int stride, Int bias)
		{
			// attrib_index - идентификатор аттрибута 
			// number_count - кол-во чисел, описывающих один идентификатор
			// stride		- шаг между вершинами (в байтах)
			// biad			- сдвиг с начала массива (в байтах)
			glVertexAttribPointer(attrib_index, number_count, GL_FLOAT, GL_FALSE, stride * sizeof(Float), (void*)(bias * sizeof(Float)));
			glEnableVertexAttribArray(attrib_index);
		}

		// Очистка массива
		void clear()
		{
			if (id != 0U)
			{
				glDeleteVertexArrays(1, &id);
				id = 0U;
			}
		}

		// Уничтожение массива
		~VAO()
		{
			clear();
		}
	};
}

#endif 
