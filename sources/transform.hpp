#ifndef TRANSFORM // Защита от повторного включения
#define TRANSFORM

#include "engine.hpp" // Включение всех заголовочных файлов

// engine - пространство имен проекта

namespace engine
{
	// Структура двумерного вектоар
	struct Vec2
	{
		Float x, y;	// Кординаты двумерного вектора

		// Конструкторы
		Vec2() { x = 0.0f; y = 0.0f; }
		Vec2(Float value) : x(value), y(value) {}
		Vec2(Float _x, Float _y) : x(_x), y(_y) {}

		// Перегруженные операторы
		Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
		Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
		Vec2 operator*(const Vec2& other) const { return Vec2(x * other.x, y * other.y); }
		Vec2 operator/(const Vec2& other) const { return Vec2(x / other.x, y / other.y); }
	};

	// Структуры трехмерного вектора
	struct Vec3
	{
		Float x, y, z; // Координаты

		// Конструкторы
		Vec3() { x = 0.0f; y = 0.0f; z = 0.0f; }
		Vec3(Float value) : x(value), y(value), z(value) {}
		Vec3(Float _x, Float _y, Float _z) : x(_x), y(_y), z(_z) {}
		Vec3(Vec2 xy, Float _z) : x(xy.x), y(xy.y), z(_z) {}

		// Перегруженные операторы
		Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
		Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
		Vec3 operator*(const Vec3& other) const { return Vec3(x * other.x, y * other.y, z * other.z); }
		Vec3 operator/(const Vec3& other) const { return Vec3(x / other.x, y / other.y, z / other.z); }
	};

	// Структура четырехмерного вектора
	struct Vec4
	{
		Float x, y, z, w; // Координаты

		// Конструкторы
		Vec4() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
		Vec4(Float value) : x(value), y(value), z(value), w(value) {}
		Vec4(Float _x, Float _y, Float _z, Float _w) : x(_x), y(_y), z(_z), w(_w) {}
		Vec4(Vec3 xyz, Float _w) : x(xyz.x), y(xyz.y), z(xyz.z), w(_w) {}

		// Перегруженные операторы
		Vec4 operator+(const Vec4& other) const { return Vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
		Vec4 operator-(const Vec4& other) const { return Vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
		Vec4 operator*(const Vec4& other) const { return Vec4(x * other.x, y * other.y, z * other.z, w * other.w); }
		Vec4 operator/(const Vec4& other) const { return Vec4(x / other.x, y / other.y, z / other.z, w / other.w); }
	};

	// Понижение размерности вектора (отсечение последней координаты)
	Vec2 low(Vec3 v)
	{
		return Vec2(v.x, v.y);
	}

	// Понижение размерности вектора (отсечение последней координаты)
	Vec3 low(Vec4 v)
	{
		return Vec3(v.x, v.y, v.z);
	}

	// Скалярное произведение
	Float dot(Vec2 v1, Vec2 v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	// Скалярное произведение
	Float dot(Vec3 v1, Vec3 v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	// Скалярное произведение
	Float dot(Vec4 v1, Vec4 v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	// Вычисление длины вектора
	Float length(Vec2 v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	// Вычисление длины вектоар
	Float length(Vec3 v)
	{
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// Вычисление длины вектора
	Float length(Vec4 v)
	{
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}

	// Нормализация вектора
	Vec2 normalize(Vec2 v)
	{
		return v / Vec2(length(v));
	}

	// Нормализация вектора
	Vec3 normalize(Vec3 v)
	{
		return v / Vec3(length(v));
	}

	// Нормализация вектора
	Vec4 normalize(Vec4 v)
	{
		return v / Vec4(length(v));
	}

	// Векторное произведение
	Vec2 croos(Vec2 v)
	{
		Vec2 result;
		result.x = v.y;
		result.y = -v.x;
		return result;
	}

	// Векторное произведение
	Vec3 cross(Vec3 v1, Vec3 v2)
	{
		Vec3 result;
		result.x = v1.y * v2.z - v2.y * v1.z;
		result.y = v2.x * v1.z - v1.x * v2.z;
		result.z = v1.x * v2.y - v2.x * v1.y;
		return result;
	}

	// Векторное произведение
	Vec4 cross(Vec4 v1, Vec4 v2, Vec4 v3)
	{
		Vec4 result;
		result.x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v3.y * v2.z);
		result.y = -1.0f * (v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
		result.z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
		result.w = -1.0f * (v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
		return result;
	}

	// Матричное произведение
	Float* multipleMat(Float* a, Float* b, Size n)
	{
		Float* c = new Float[n * n];
		for (Size i = 0Ull; i < n * n; i++)
			c[i] = 0.0f;
		for (Size i = 0Ull; i < n; i++)
		{
			for (int j = 0Ull; j < n; j++)
			{
				for (int k = 0Ull; k < n; k++)
					c[i * n + j] += a[i * n + k] * b[k * n + j];
			}
		}
		return c;
	}

	// Структура матрицы 2х2
	struct Mat2
	{
		Vec2 i, j; // Вектор-столбцы

		// Конструкторы
		Mat2() { i = Vec2(1.0f, 0.0f); j = Vec2(0.0f, 1.0f); }
		Mat2(Vec2 _i, Vec2 _j) : i(_i), j(_j) {}
		Mat2(Float* ptr) { i = Vec2(ptr[0Ull], ptr[2Ull]); j = Vec2(ptr[1Ull], ptr[3Ull]); }

		// Перегруженные операторы
		Mat2 operator+(const Mat2& other) const { return Mat2(i + other.i, j + other.j); }
		Mat2 operator-(const Mat2& other) const { return Mat2(i - other.i, j - other.j); }
		Mat2 operator*(Float scalar) const { return Mat2(i * scalar, j * scalar); }
		Vec2 operator*(const Vec2& v) const { return Vec2(v.x * i.x + v.y * j.x, v.x * i.y + v.y * j.y); }

		// Матричное произведение
		Mat2 operator*(const Mat2& other) const 
		{ 
			Float this_ptr[4Ull] = {
				i.x, j.x,
				i.y, j.y
			};
			Float other_ptr[4Ull] = {
				other.i.x, other.j.x,
				other.i.y, other.j.y
			};
			Float* ptr = multipleMat(this_ptr, other_ptr, 2Ull);
			Mat2 result(ptr);
			delete[] ptr;
			return result; 
		}
	};

	// Структура матрицы 3х3
	struct Mat3
	{
		Vec3 i, j, k; // Вектор-столбцы

		// Конструкторы
		Mat3() { i = Vec3(1.0f, 0.0f, 0.0f); j = Vec3(0.0f, 1.0f, 0.0f); k = Vec3(0.0f, 0.0f, 1.0f); }
		Mat3(Vec3 _i, Vec3 _j, Vec3 _k) : i(_i), j(_j), k(_k) {}
		Mat3(Float* ptr) { i = Vec3(ptr[0Ull], ptr[3Ull], ptr[6Ull]); j = Vec3(ptr[1Ull], ptr[4Ull], ptr[7Ull]); k = Vec3(ptr[2Ull], ptr[5Ull], ptr[8Ull]); }
		Mat3(Mat2 m, Vec2 v) : i(Vec3(m.i, 0.0f)), j(Vec3(m.j, 0.0f)), k(Vec3(v, 1.0f)) {}

		// Перегруженные операторы
		Mat3 operator+(const Mat3& other) const { return Mat3(i + other.i, j + other.j, k + other.k); }
		Mat3 operator-(const Mat3& other) const { return Mat3(i - other.i, j - other.j, k - other.k); }
		Mat3 operator*(Float scalar) const { return Mat3(i * scalar, j * scalar, k * scalar); }
		Vec3 operator*(const Vec3& v) const { return Vec3(v.x * i.x + v.y * j.x + v.z * k.x, v.x * i.y + v.y * j.y + v.z * k.y, v.x * i.z + v.y * j.z + v.z * k.z); }

		// Матричное произведение
		Mat3 operator*(const Mat3& other) const
		{
			Float this_ptr[9Ull] = {
				i.x, j.x, k.x,
				i.y, j.y, k.y,
				i.z, j.z, k.z
			};
			Float other_ptr[9Ull] = {
				other.i.x, other.j.x, other.k.x,
				other.i.y, other.j.y, other.k.y,
				other.i.z, other.j.z, other.k.z
			};
			Float* ptr = multipleMat(this_ptr, other_ptr, 3Ull);
			Mat3 result(ptr);
			delete[] ptr;
			return result;
		}
	};

	// Структура матрицы 4х4
	struct Mat4
	{
		Vec4 i, j, k, l; // Вектор-столбцы

		// Конструкторы
		Mat4() { i = Vec4(1.0f, 0.0f, 0.0f, 0.0f); j = Vec4(0.0f, 1.0f, 0.0f, 0.0f); k = Vec4(0.0f, 0.0f, 1.0f, 0.0f); l = Vec4(0.0f, 0.0f, 0.0f, 1.0f); }
		Mat4(Vec4 _i, Vec4 _j, Vec4 _k, Vec4 _l) : i(_i), j(_j), k(_k), l(_l) {}
		Mat4(Float* ptr) { i = Vec4(ptr[0Ull], ptr[4Ull], ptr[8Ull], ptr[12Ull]); j = Vec4(ptr[1Ull], ptr[5Ull], ptr[9Ull], ptr[13Ull]); k = Vec4(ptr[2Ull], ptr[6Ull], ptr[10Ull], ptr[14Ull]); l = Vec4(ptr[3Ull], ptr[7Ull], ptr[11Ull], ptr[15Ull]); }
		Mat4(Mat3 m, Vec3 v) : i(Vec4(m.i, 0.0f)), j(Vec4(m.j, 0.0f)), k(Vec4(m.k, 0.0f)), l(Vec4(v, 1.0f)) {}

		// Перегруженные операторы
		Mat4 operator+(const Mat4& other) const { return Mat4(i + other.i, j + other.j, k + other.k, l + other.l); }
		Mat4 operator-(const Mat4& other) const { return Mat4(i - other.i, j - other.j, k - other.k, l - other.l); }
		Mat4 operator*(Float scalar) const { return Mat4(i * scalar, j * scalar, k * scalar, l * scalar); }
		Vec4 operator*(const Vec4& v) const { return Vec4(v.x * i.x + v.y * j.x + v.z * k.x + v.w * l.x, v.x * i.y + v.y * j.y + v.z * k.y + v.w * l.y, v.x * i.z + v.y * j.z + v.z * k.z + v.w * l.z, v.x * i.w + v.y * j.w + v.z * k.w + v.w * l.w); }

		// Матричное произведение
		Mat4 operator*(const Mat4& other) const 
		{
			Float this_ptr[16Ull] = {
				i.x, j.x, k.x, l.x,
				i.y, j.y, k.y, l.y,
				i.z, j.z, k.z, l.z,
				i.w, j.w, k.w, l.w
			};
			Float other_ptr[16Ull] = {
				other.i.x, other.j.x, other.k.x, other.l.x,
				other.i.y, other.j.y, other.k.y, other.l.y,
				other.i.z, other.j.z, other.k.z, other.l.z,
				other.i.w, other.j.w, other.k.w, other.l.w
			};
			Float* ptr = multipleMat(this_ptr, other_ptr, 4Ull);
			Mat4 result(ptr);
			delete[] ptr;
			return result;
		}
	};

	// Понижение размерности матрицы (отсечение последних строки и стобца)
	Mat2 low(Mat3 m)
	{
		return Mat2(low(m.i), low(m.j));
	}

	// Понижение размерности матрицы (отсечение последних строки и стобца)
	Mat3 low(Mat4 m)
	{
		return Mat3(low(m.i), low(m.j), low(m.k));
	}

	// Вычисление определителя матрицы
	Float det(Mat2 m)
	{
		return m.i.x * m.j.y - m.j.x * m.i.y;
	}

	// Вычисление определителя матрицы
	Float det(Mat3 m)
	{
		Float a[4Ull] = {
			m.j.y, m.k.y,
			m.j.z, m.k.z
		};
		Float b[4Ull] = {
			m.i.y, m.k.y,
			m.i.z, m.k.z
		};
		Float c[4Ull] = {
			m.i.y, m.j.y,
			m.i.z, m.j.z
		};
		Mat2 mat_a(a), mat_b(b), mat_c(c);
		return m.i.x * det(mat_a) - m.j.x * det(mat_b) + m.k.x * det(mat_c);
	}

	// Вычисление определителя матрицы
	Float det(Mat4 m)
	{
		Float a[9Ull] = {
			m.j.y, m.k.y, m.l.y,
			m.j.z, m.k.z, m.l.z,
			m.j.w, m.k.w, m.l.w,
		};
		Float b[9Ull] = {
			m.i.y, m.k.y, m.l.y,
			m.i.z, m.k.z, m.l.z,
			m.i.w, m.k.w, m.l.w,
		};
		Float c[9Ull] = {
			m.i.y, m.j.y, m.l.y,
			m.i.z, m.j.z, m.l.z,
			m.i.w, m.j.w, m.l.w,
		};
		Float d[9Ull] = {
			m.i.y, m.j.y, m.k.y,
			m.i.z, m.j.z, m.k.z,
			m.i.w, m.j.w, m.k.w,
		};
		Mat3 mat_a(a), mat_b(b), mat_c(c), mat_d(d);
		return m.i.x * det(mat_a) - m.j.x * det(mat_b) + m.k.x * det(mat_c) - m.l.x * det(mat_d);
	}

	// Тринспонирование матрицы
	Mat2 transpon(Mat2 m)
	{
		Float t[4Ull] = {
			m.i.x, m.i.y,
			m.j.x, m.j.y
		};
		return t;
	}

	// Тринспонирование матрицы
	Mat3 transpon(Mat3 m)
	{
		Float t[9Ull] = {
			m.i.x, m.i.y, m.i.z,
			m.j.x, m.j.y, m.j.z,
			m.k.x, m.k.y, m.k.z
		};
		return t;
	}

	// Тринспонирование матрицы
	Mat4 transpon(Mat4 m)
	{
		Float t[16Ull] = {
			m.i.x, m.i.y, m.i.z, m.i.w,
			m.j.x, m.j.y, m.j.z, m.j.w,
			m.k.x, m.k.y, m.k.z, m.k.w,
			m.l.x, m.l.y, m.l.z, m.l.w,
		};
		return t;
	}

	// Конвертация углов в радианы
	Float rad(Float angle)
	{
		return angle * (acos(-1.0f) / 180.0f);
	}

	// Создание матрицы поворота на плоскости
	Mat2 rotate(Float angle)
	{
		Float m[4Ull] = {
			cos(angle), -sin(angle),
			sin(angle), cos(angle)
		};
		return m;
	}

	// Создание матрицы поворота вокруг заданной оси на заданный угол в пространстве
	Mat3 rotate(Vec3 axis, Float angle)
	{
		Float m[9Ull] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
		if (axis.z == 1.0f)
		{
			m[0Ull] = cos(angle);
			m[3Ull] = sin(angle);
			m[1Ull] = -sin(angle);
			m[4Ull] = cos(angle);
		}
		else if (axis.y == 1.0f)
		{
			m[0Ull] = cos(angle);
			m[6Ull] = sin(angle);
			m[2Ull] = -sin(angle);
			m[8Ull] = cos(angle);
		}
		else if (axis.x == 1.0f)
		{
			m[4Ull] = cos(angle);
			m[7Ull] = sin(angle);
			m[5Ull] = -sin(angle);
			m[8Ull] = cos(angle);
		}
		return m;
	}

	// Создание матрицы масштабирования по осям
	Mat2 scale(Vec2 scalars)
	{
		Float m[4Ull] = {
			scalars.x, 0.0f,
			0.0f, scalars.y
		};
		return m;
	}

	// Создание матрицы масштабирования по осям
	Mat3 scale(Vec3 scalars)
	{
		Float m[9Ull] = {
			scalars.x, 0.0f, 0.0f,
			0.0f, scalars.y, 0.0f,
			0.0f, 0.0f, scalars.z
		};
		return m;
	}

	// Создание матрицы масштабирования по осям
	Mat4 scale(Vec4 scalars)
	{
		Float m[16Ull] = {
			scalars.x, 0.0f, 0.0f, 0.0f,
			0.0f, scalars.y, 0.0f, 0.0f,
			0.0f, 0.0f, scalars.z, 0.0f,
			0.0f, 0.0f, 0.0f, scalars.w
		};
		return m;
	}

	// Создание матрицы перемещения
	Mat3 move(Vec2 bias)
	{
		Vec3 i = Vec3(1.0f, 0.0f, 0.0f);
		Vec3 j = Vec3(0.0f, 1.0f, 0.0f);
		Vec3 k = Vec3(Vec2(0.0f) - bias, 1.0f);
		return Mat3(i, j, k);
	}

	// Создание матрицы перемещения
	Mat4 move(Vec3 bias)
	{
		Vec4 i = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
		Vec4 j = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
		Vec4 k = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Vec4 l = Vec4(Vec3(0.0f) - bias, 1.0f);
		return Mat4(i, j, k, l);
	}

	// Создание матрицы перспективной проекции
	Mat4 perspective(Float n, Float f, Float fov, Int width, Int height)
	{
		Float t = n * tan(fov / 2.0f);
		Float aspect = (Float)width / (Float)height;
		Float r = t * aspect;
		Float m[16Ull] = {
			n / r, 0.0f, 0.0f, 0.0f,
			0.0f, n / t, 0.0f, 0.0f,
			0.0f, 0.0f, (f + n) / (n - f), 2.0f * n * f / (n - f),
			0.0f, 0.0f, -1.0f, 0.0f
		};
		return m;
	}

	// Запись данных по заданному адресу
	void ptr(Vec2 v, Float* data)
	{
		Float arr[2Ull] = { v.x, v.y };
		for (Size i = 0; i < 2Ull; i++)
			data[i] = arr[i];
	}

	// Запись данных по заданному адресу
	void ptr(Vec3 v, Float* data)
	{
		Float arr[3Ull] = { v.x, v.y, v.z };
		for (Size i = 0; i < 3Ull; i++)
			data[i] = arr[i];
	}

	// Запись данных по заданному адресу
	void ptr(Vec4 v, Float* data)
	{
		Float arr[4Ull] = { v.x, v.y, v.z, v.w };
		for (Size i = 0; i < 4Ull; i++)
			data[i] = arr[i];
	}

	// Запись данных по заданному адресу
	void ptr(Mat2 m, Float* data)
	{
		Float arr[4Ull] = { 
			m.i.x, m.j.x,
			m.i.y, m.j.y
		};
		for (Size i = 0; i < 4Ull; i++)
			data[i] = arr[i];
	}

	// Запись данных по заданному адресу
	void ptr(Mat3 m, Float* data)
	{
		Float arr[9Ull] = {
			m.i.x, m.j.x, m.k.x,
			m.i.y, m.j.y, m.k.y,
			m.i.z, m.j.z, m.k.z
		};
		for (Size i = 0; i < 9Ull; i++)
			data[i] = arr[i];
	}

	// Запись данных по заданному адресу
	void ptr(Mat4 m, Float* data)
	{
		Float arr[16Ull] = {
			m.i.x, m.j.x, m.k.x, m.l.x,
			m.i.y, m.j.y, m.k.y, m.l.y,
			m.i.z, m.j.z, m.k.z, m.l.z,
			m.i.w, m.j.w, m.k.w, m.l.w
		};
		for (Size i = 0; i < 16Ull; i++)
			data[i] = arr[i];
	}
}

#endif