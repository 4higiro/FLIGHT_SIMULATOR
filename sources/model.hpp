#ifndef MODEL // Защита от повторного включения
#define MODEL

#include "engine.hpp" // Включение всех заголовочных файлов

/*
	Основаня задача класса модели - объединить несколько мешей для проведения над всеми ними
	одновременно аффинных преобразований. Таким образом модель может состоять из отдельных движущихся
	деталей.
*/

// engine - пространство имен проекта

namespace engine
{
	// Класс трехмерной Модели
	class Model
	{
	private:
		std::vector<Mesh*> meshes;	// Массив мешей

		Mat3 m_rot, m_scl;			// Матрицы поворота и масштабирования
		Mat4 m_move;				// Матрицы перемещения
		Mat4 matrix;				// Общая матрица
	public:
		// Конструктор по умолчанию доступен
		Model() {}

		// Конструктор, заполняющий поля
		Model(std::vector<Mesh*> _meshes) : meshes(_meshes) {}

		// Геттер кол-ва мешей
		Size account()
		{
			return meshes.size();
		}

		// Геттер матрицы преобразования в мировую систему координат
		Mat4 model() const
		{
			return matrix;
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

		// Формирование матрицы модели с помощью последовательных аффинных преобразований (поворот, масштабирвоание, перемещение)
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

		// Итерирование по каждой детали массива
		Mesh& operator[](Size index)
		{
			return *meshes[index];
		}

		// Рендер всех мешей и загрузка матрицы модели
		void draw(const ShaderProgram& program) const
		{
			// program - рисующая шейдерная программа
			for (Size i = 0Ull; i < meshes.size(); i++)
				meshes[i]->draw(program, matrix);
		}
	};
}

#endif
