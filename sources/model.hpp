#ifndef MODEL // Защита от повторного включения
#define MODEL

#include "engine.hpp" // Включение всех заголовочных файлов

/*
	Основная задаче класса модели - загрузить данные о вершинах на видеокарту
	и сформировать матрицу перехода из локальной системы координат модели в
	мировую систему координат - матрицу model. Делается это для того, чтобы было возможно 
	производить операции над объектами отдельно от остальных объектов на сцене.
	К вершинам модели можно применить следующие операции: поворот, перемещение, масшатбирование.
	Пользователь класса сам определяет порядок этих операций с помощью приоритетов.
*/

// engine - пространство имен проекта

namespace engine
{
	// Класс трехмерной Модели
	class Model
	{
	private:
		VBO buff;				// Вершинный буфер
		EBO ebuff;				// Элементный буфер
		VAO arr;				// Вершинный массив (разметка вершинного буфера)
		Texture2D tex;			// Текстура

		Int vertex_count = 0;	// Кол-во вершин
		Int index_count = 0;	// Кол-во индексов в элементном буфере
		
		/*
			Модель можно копировать и перезаписывать, но по скольку данные будут хранится
			на видеокарте, то все экзмепляры будут ссылать на одинаковый буфер, не смотря на
			то что в оперативной памяти остальная информация будет хранится в разных местах.
			В таком случае очищаться будет только буфер оригинального объекта.
		*/

		bool is_orig = true; // При создании экземпляр считается оригинальным

		Mat3 m_rot, m_scl;	// Матрицы поворота и масштабирования
		Mat4 m_move;		// Матрицы перемещения
		Mat4 matrix;		// Общая матрица

		// Заполнение буфера
		void setBuffer(Float* vertecies, Uint* indices, Uint vertex_count, Uint index_count, std::string texture_path)
		{
			// verteties	- расположение данных о вершинах
			// indices		- расположения данных о порядке рисования вершин
			// vertex_count - кол-во вершин вершинного буфера
			// index_count  - кол-во индексов элементого буфера
			// texture_path - путь к текстуре
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
		// Конструктор по умолчанию доступен
		Model() {}

		// Конструктор копирования
		Model(const Model& other)
		{
			// Копирование
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
			is_orig = false; // Пометка о неоригинальности
		}

		// Оператор присваивания
		Model& operator=(const Model& other)
		{
			// Очистка старого объекта
			clear();
			// Копирования
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
			is_orig = false; // Пометка о неоригинальности
			return *this;
		}

		// Проверка оригинальности
		bool isOriginal() const
		{
			return is_orig;
		}

		// Геттер кол-ва вершин
		Int account() const
		{
			return vertex_count;
		}

		// ОПАСНО! Экземпляр можно сделать оригинальным
		void original()
		{
			is_orig = true;
		}

		// Геттер матрицы преобразования в мировую систему координат
		Mat4 model() const
		{
			return matrix;
		}

		// Загрузка вершин и текстуры модели из файла
		void load(std::string vertecies_path, std::string texture_path)
		{
			// vertecies_path	- путь к файлу с вершинами
			// texture_path		- путь к файлу с текстурой
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

		// Поворот модели в 3-х плоскостях (yOz, xOz, xOy)
		void rotate(Vec3 angle)
		{
			// angle - углы поворота во всех плоскостях
			Mat3 yoz = engine::rotate(Vec3(1.0f, 0.0f, 0.0f), angle.x);
			Mat3 xoz = engine::rotate(Vec3(0.0f, 1.0f, 0.0f), angle.y);
			Mat3 xoy = engine::rotate(Vec3(0.0f, 0.0f, 1.0f), angle.z);
			m_rot = yoz * xoz * xoy;
		}

		// Перемещение модели (x, y, z)
		void move(Vec3 bias)
		{
			// bias - вектор перемещения
			m_move = engine::move(bias);
		}

		// Масштабирвоание модели по 3-м осям (Ox, Oy, Oz)
		void scale(Vec3 scalars)
		{
			// scalars - коэффициенты масштабирвоания
			m_scl = engine::scale(scalars);
		}

		// Формирование матрицы модели с помощью последовательных линейных операций (поворот, масштабирвоание, перемещение)
		void transform(Vec3 priority)
		{
			// priority - значения приоритетов, наибольший приоритет - первоочередное преобразование
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

		// Рендер всех вершин и загрузка матрицы модели
		void draw(const ShaderProgram& program) const
		{
			// program - рисующая шейдерная программа
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

		// Очистка оригинальной модели
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

		// Уничтожение оригинальной модели
		~Model()
		{
			clear();
		}
	};
}

#endif
