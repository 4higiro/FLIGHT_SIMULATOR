#ifndef BUFFER_OBJECTS // ������ �� ���������� ���������
#define BUFFER_OBJECTS

#include "engine.hpp" // ��������� ���� ������������ ������

// engine - ������������ ���� �������

namespace engine
{
	// ����� ������� ���������� ������
	class VBO
	{
	private:
		mutable Uint id = 0U; // ������������� ������

		// ��������� ���������� � �������������� ���������� ������
		VBO(const VBO& other) {}
		VBO& operator=(const VBO& other) {}

		friend class Model; // �������� ���� � ������ �������� � ������ Model
	public:
		// ������� ������ � ��������� OpenGL
		static void resetBind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0U);
		}

		// �������� ������
		VBO()
		{
			glGenBuffers(1, &id);
		}

		// ������ �������������� ������
		Uint getID() const
		{
			return id;
		}

		// ���������� ������ � ���������� OpenGL
		void bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		// �������� ������ ������ �� ����������
		void data(const Float* data, Size n, Uint mode)
		{
			// data - ��� ������ � �������� 
			// n	- ������ ������� � �������
			// mode - ����� ��������
			glBufferData(GL_ARRAY_BUFFER, n, data, mode);
		}

		// ������� ������
		void clear()
		{
			if (id != 0U)
			{
				glDeleteBuffers(1, &id);
				id = 0U;
			}
		}

		// ����������� ������
		~VBO()
		{
			clear();
		}
	};

	// ����� ������� ����������� ������
	class EBO
	{
	private:
		mutable Uint id = 0U; // ������������� ������

		// ��������� ���������� � �������������� ���������� ������
		EBO(const VBO& other) {}
		EBO& operator=(const VBO& other) {}

		friend class Model; // �������� ���� � ������ �������� � ������ Model
	public:
		// ������� ������ � ��������� OpenGL
		static void resetBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0U);
		}

		// �������� ������
		EBO()
		{
			glGenBuffers(1, &id);
		}

		// ������ �������������� ������
		Uint getID() const
		{
			return id;
		}

		// ���������� ������ � ���������� OpenGL
		void bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		// �������� ������ ������ �� ����������
		void data(const Uint* data, Size n, Uint mode)
		{
			// data - ������ (������� ������� ������ �� ���������� �������)
			// n	- ������ ������� � �������
			// mode - ����� ��������
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, n, data, mode);
		}

		// ������ ���� ������ �� ��������� ������
		void draw(Uint shp_id, Int vertex_count) const
		{
			// shp_id		- ������������� ��������� ��������� 
			// vertex_count - ���������� �������� ������
			glUseProgram(shp_id);
			glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, NULL);
		}

		// ������� ������
		void clear()
		{
			if (id != 0U)
			{
				glDeleteBuffers(1, &id);
				id = 0U;
			}
		}

		// ����������� ������
		~EBO()
		{
			clear();
		}
	};

	// ����� ������� ���������� �������
	class VAO
	{
	private:
		mutable Uint id = 0; // ������������� �������

		// ��������� ���������� � �������������� ���������� �������
		VAO(const VAO& other) {}
		VAO& operator=(const VAO& other) {}

		friend class Model; // �������� ���� � ������ �������� � ������ Model
	public:
		// ������� ������� �� ��������� OpenGL
		static void resetBind()
		{
			glBindVertexArray(0U);
		}

		// �������� �������
		VAO()
		{
			glGenVertexArrays(1, &id);
		}

		// ������ �������������� �������
		Uint getID() const
		{
			return id;
		}

		// ���������� ������� � ���������� OpenGL
		void bind() const
		{
			glBindVertexArray(id);
		}

		// �������� ������ ������, ���������� � ����������� ���������� �������
		void setBuffDataConfig(Uint attrib_index, Int number_count, Int stride, Int bias)
		{
			// attrib_index - ������������� ��������� 
			// number_count - ���-�� �����, ����������� ���� �������������
			// stride		- ��� ����� ��������� (� ������)
			// biad			- ����� � ������ ������� (� ������)
			glVertexAttribPointer(attrib_index, number_count, GL_FLOAT, GL_FALSE, stride * sizeof(Float), (void*)(bias * sizeof(Float)));
			glEnableVertexAttribArray(attrib_index);
		}

		// ������� �������
		void clear()
		{
			if (id != 0U)
			{
				glDeleteVertexArrays(1, &id);
				id = 0U;
			}
		}

		// ����������� �������
		~VAO()
		{
			clear();
		}
	};
}

#endif 
