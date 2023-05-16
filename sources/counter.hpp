#ifndef COUNTER // ������ �� ���������� ���������
#define COUNTER

#include "engine.hpp" // ��������� ���� ������������ ������

/*
	���� � ���, ����� �� ��������� 500+ ���������, � ������� �� � ������ ������,
	����� ������� ��� ��������� � ����������� ��������� �������������� � ��������������
*/

// engine - ������������ ���� �������

namespace engine
{
	// ��������� �������� ��������
	struct Counter
	{
		Float f = 0.0f;			// ������� ���� float
		Int i = 0;				// ������� ���� int
		Vec3 angle = 0.0f;		// ������� ����� �������� � ���� ����������
		Vec3 v = 0.0f;			// ������� ��������� �������

		Float fstep = 0.1f;		// ��� �������� ��������
		Int istep = 1;			// ��� �������������� ��������
		Vec3 astep = rad(1.0f);	// ��� �������� ��������
		Vec3 vstep = 0.01f;		// ��� ������������� ��������

		// ���������� ���������
		Counter& operator++()
		{
			f = f + fstep;
			i = i + istep;
			angle = angle + astep;
			v = v + vstep;
			return *this;
		}

		// ���������� ���������
		Counter& operator--()
		{
			f = f - fstep;
			i = i - istep;
			angle = angle - astep;
			v = v - vstep;
			return *this;
		}

		// ����������� ���������
		Counter& operator++(int)
		{
			Counter temp = *this;
			f = f + fstep;
			i = i + istep;
			angle = angle + astep;
			v = v + vstep;
			return temp;
		}

		// ����������� ���������
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
