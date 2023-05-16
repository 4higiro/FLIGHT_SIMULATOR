#ifndef CAMERA // Зашита от повторного включения
#define CAMERA

#include "engine.hpp" // Включение всех заголовочных файлов

/*
	Основная задача камеры - сформировать матрицу перехода от мировой системы координат
	в пространство камеры - матрица view. Камера - точка обзора, таким образом преобразование
	можно задать смещением и вращением мирового пространства так, как перемещается и вращается
	камера.
*/

// engine - пространство имен проекта

namespace engine
{
	// Класс Камеры
	class Camera
	{
	private:
		Mat4 m_move;	// Матрица перемещения
		Mat3 m_rot;		// Матрица поворота
		Mat4 matrix;	// Общее преобразование

		// Для одиночки конструктор по умолчанию скрыт
		Camera() {}
	public:
		// Геттер указателя на одиночку
		static Camera* getInstance()
		{
			static Camera instance;
			return &instance;
		}

		// Геттер позиции камеры
		Vec3 position() const 
		{
			return low(m_move.l);
		}

		// Геттер направления обзора камеры
		Vec3 direction() const 
		{
			return Vec3(m_rot.i.z, m_rot.j.z, m_rot.k.z);
		}

		// Геттер вектора-вправо обзора камеры
		Vec3 right() const 
		{
			return Vec3(m_rot.i.x, m_rot.j.x, m_rot.k.x);
		}

		// Вращение камеры в 3-х плоскостях (yOz, xOz, xOy)
		void rotate(Vec3 angle)
		{
			// angle - углы поворота во всех плоскостях
			Mat3 yoz = engine::rotate(Vec3(1.0f, 0.0f, 0.0f), angle.x);
			Mat3 xoz = engine::rotate(Vec3(0.0f, 1.0f, 0.0f), angle.y);
			Mat3 xoy = engine::rotate(Vec3(0.0f, 0.0f, 1.0f), angle.z);
			m_rot = yoz * xoz * xoy;
			matrix = Mat4(m_rot, Vec3(0.0f)) * m_move;
		}

		// Перемещение камеры 
		void move(Vec3 bias)
		{
			// bias - вектор перемещения
			m_move = m_move * engine::move(bias);
			matrix = Mat4(m_rot, Vec3(0.0f)) * m_move;
		}

		// Геттер матрицы преобразования в пространство камеры
		Mat4 view() const
		{
			return matrix;
		}
	};
}

#endif
