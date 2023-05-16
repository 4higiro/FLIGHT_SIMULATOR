#ifndef COUNTER // Защита от повторного включения
#define COUNTER

#include "engine.hpp" // Включение всех заголовочных файлов

/*
	Идия в том, чтобы не создавать 500+ счетчиков, а собрать их в единый объект,
	задав каждому шаг изменения и перегрузить операторы инкремирования и декремирования
*/

// engine - пространство имен проекта

namespace engine
{
	// Объектная оболочка счетчика
	struct Counter
	{
		Float f = 0.0f;			// Счетчик типа float
		Int i = 0;				// Счетчик типа int
		Vec3 angle = 0.0f;		// Счетчик углов поворота в трех плоскостях
		Vec3 v = 0.0f;			// Счетчик координат вектора

		Float fstep = 0.1f;		// Шаг дробного счетчика
		Int istep = 1;			// Шаг целочисленного счетчика
		Vec3 astep = rad(1.0f);	// Шаг углового счетчика
		Vec3 vstep = 0.01f;		// Шаг координатного счетчика

		// Префиксный инкремент
		Counter& operator++()
		{
			f = f + fstep;
			i = i + istep;
			angle = angle + astep;
			v = v + vstep;
			return *this;
		}

		// Префексный декремент
		Counter& operator--()
		{
			f = f - fstep;
			i = i - istep;
			angle = angle - astep;
			v = v - vstep;
			return *this;
		}

		// Постфиксный инкремент
		Counter& operator++(int)
		{
			Counter temp = *this;
			f = f + fstep;
			i = i + istep;
			angle = angle + astep;
			v = v + vstep;
			return temp;
		}

		// Постфиксный декремент
		Counter& operator--(int)
		{
			Counter temp = *this;
			f = f - fstep;
			i = i - istep;
			angle = angle - astep;
			v = v - vstep;
			return temp;
		}
	};
}

#endif
