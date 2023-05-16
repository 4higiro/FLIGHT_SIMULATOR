#ifndef MODEL // ������ �� ���������� ���������
#define MODEL

#include "engine.hpp" // ��������� ���� ������������ ������

/*
	�������� ������ ������ ������ - ��������� ������ � �������� �� ����������
	� ������������ ������� �������� �� ��������� ������� ��������� ������ �
	������� ������� ��������� - ������� model. �������� ��� ��� ����, ����� ���� �������� 
	����������� �������� ��� ��������� �������� �� ��������� �������� �� �����.
	� �������� ������ ����� ��������� ��������� ��������: �������, �����������, ���������������.
	������������ ������ ��� ���������� ������� ���� �������� � ������� �����������.
*/

// engine - ������������ ���� �������

namespace engine
{
	// ����� ���������� ������
	class Model
	{
	private:
		VBO buff;				// ��������� �����
		EBO ebuff;				// ���������� �����
		VAO arr;				// ��������� ������ (�������� ���������� ������)
		Texture2D tex;			// ��������

		Int vertex_count = 0;	// ���-�� ������
		Int index_count = 0;	// ���-�� �������� � ���������� ������
		
		/*
			������ ����� ���������� � ��������������, �� �� ������� ������ ����� ��������
			�� ����������, �� ��� ���������� ����� ������� �� ���������� �����, �� ������ ��
			�� ��� � ����������� ������ ��������� ���������� ����� �������� � ������ ������.
			� ����� ������ ��������� ����� ������ ����� ������������� �������.
		*/

		bool is_orig = true; // ��� �������� ��������� ��������� ������������

		Mat3 m_rot, m_scl;	// ������� �������� � ���������������
		Mat4 m_move;		// ������� �����������
		Mat4 matrix;		// ����� �������

		// ���������� ������
		void setBuffer(Float* vertecies, Uint* indices, Uint vertex_count, Uint index_count, std::string texture_path)
		{
			// verteties	- ������������ ������ � ��������
			// indices		- ������������ ������ � ������� ��������� ������
			// vertex_count - ���-�� ������ ���������� ������
			// index_count  - ���-�� �������� ���������� ������
			// texture_path - ���� � ��������
			arr.bind();
			buff.bind();
			buff.data(vertecies, vertex_count * 8Ull * sizeof(Float), GL_STATIC_DRAW);
			arr.setBuffDataConfig(0U, 3, 8, 0);
			arr.setBuffDataConfig(1U, 3, 8, 3);
			arr.setBuffDataConfig(2U, 2, 8, 6);
			ebuff.bind();
			ebuff.data(indices, index_count * sizeof(Uint), GL_STATIC_DRAW);
			tex.bind();
			tex.setConfig(GL_REPEAT, GL_LINEAR);
			tex.load(texture_path);
			Texture2D::resetBind();
			EBO::resetBind();
			VBO::resetBind();
			VAO::resetBind();
		}
	public:
		// ����������� �� ��������� ��������
		Model() {}

		// ����������� �����������
		Model(const Model& other)
		{
			// �����������
			buff.id = other.buff.getID();
			ebuff.id = other.ebuff.getID();
			arr.id = other.arr.getID();
			tex.id = other.tex.getID();
			m_rot = other.m_rot;
			m_scl = other.m_scl;
			m_move = other.m_move;
			matrix = other.matrix;
			vertex_count = other.vertex_count;
			index_count = other.index_count;
			is_orig = false; // ������� � ����������������
		}

		// �������� ������������
		Model& operator=(const Model& other)
		{
			// ������� ������� �������
			clear();
			// �����������
			buff.id = other.buff.getID();
			ebuff.id = other.ebuff.getID();
			arr.id = other.arr.getID();
			tex.id = other.tex.getID();
			m_rot = other.m_rot;
			m_scl = other.m_scl;
			m_move = other.m_move;
			matrix = other.matrix;
			vertex_count = other.vertex_count;
			index_count = other.index_count;
			is_orig = false; // ������� � ����������������
			return *this;
		}

		// �������� ��������������
		bool isOriginal() const
		{
			return is_orig;
		}

		// ������ ���-�� ������
		Int account() const
		{
			return vertex_count;
		}

		// ������! ��������� ����� ������� ������������
		void original()
		{
			is_orig = true;
		}

		// ������ ������� �������������� � ������� ������� ���������
		Mat4 model() const
		{
			return matrix;
		}

		// �������� ������ � �������� ������ �� �����
		void load(std::string vertecies_path, std::string texture_path)
		{
			// vertecies_path	- ���� � ����� � ���������
			// texture_path		- ���� � ����� � ���������
			std::ifstream fin;
			fin.open(vertecies_path);
			fin >> vertex_count;
			std::vector<Float> data(8Ull * vertex_count);
			for (Size i = 0Ull; i < 8Ull * vertex_count; i++)
				fin >> data[i];
			fin >> index_count;
			std::vector<Uint> order(index_count);
			for (Size i = 0; i < index_count; i++)
				fin >> order[i];
			setBuffer(data.data(), order.data(), vertex_count, index_count, texture_path);
			fin.close();
		}

		// ������� ������ � 3-� ���������� (yOz, xOz, xOy)
		void rotate(Vec3 angle)
		{
			// angle - ���� �������� �� ���� ����������
			Mat3 yoz = engine::rotate(Vec3(1.0f, 0.0f, 0.0f), angle.x);
			Mat3 xoz = engine::rotate(Vec3(0.0f, 1.0f, 0.0f), angle.y);
			Mat3 xoy = engine::rotate(Vec3(0.0f, 0.0f, 1.0f), angle.z);
			m_rot = yoz * xoz * xoy;
		}

		// ����������� ������ (x, y, z)
		void move(Vec3 bias)
		{
			// bias - ������ �����������
			m_move = engine::move(bias);
		}

		// ��������������� ������ �� 3-� ���� (Ox, Oy, Oz)
		void scale(Vec3 scalars)
		{
			// scalars - ������������ ���������������
			m_scl = engine::scale(scalars);
		}

		// ������������ ������� ������ � ������� ���������������� �������� �������� (�������, ���������������, �����������)
		void transform(Vec3 priority)
		{
			// priority - �������� �����������, ���������� ��������� - �������������� ��������������
			Mat4 temp;
			for (Size i = 0; i < 3Ull; i++)
			{
				if (priority.x >= priority.y && priority.x >= priority.z)
				{
					temp = temp * Mat4(m_rot, Vec3(0.0f));
					priority.x = priority.y - 1.0f;
				}
				else if (priority.y >= priority.x && priority.y >= priority.z)
				{
					temp = temp * Mat4(m_scl, Vec3(0.0f));
					priority.y = priority.z - 1.0f;
				}
				else if (priority.z >= priority.x && priority.z >= priority.y)
				{
					temp = temp * m_move;
					priority.z = priority.x - 1.0f;
				}
			}
			matrix = temp;
		}

		// ������ ���� ������ � �������� ������� ������
		void draw(const ShaderProgram& program) const
		{
			// program - �������� ��������� ���������
			arr.bind();
			ebuff.bind();
			tex.bind();
			program.use();
			program.setUniform("model", matrix);
			ebuff.draw(program.getID(), index_count);
			engine::Texture2D::resetBind();
			engine::EBO::resetBind();
			engine::VAO::resetBind();
		}

		// ������� ������������ ������
		void clear()
		{
			if (is_orig)
			{
				buff.clear();
				ebuff.clear();
				arr.clear();
				tex.clear();
			}
		}

		// ����������� ������������ ������
		~Model()
		{
			clear();
		}
	};
}

#endif
