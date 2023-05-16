#ifndef CAMERA // ������ �� ���������� ���������
#define CAMERA

#include "engine.hpp" // ��������� ���� ������������ ������

/*
	�������� ������ ������ - ������������ ������� �������� �� ������� ������� ���������
	� ������������ ������ - ������� view. ������ - ����� ������, ����� ������� ��������������
	����� ������ ��������� � ��������� �������� ������������ ���, ��� ������������ � ���������
	������.
*/

// engine - ������������ ���� �������

namespace engine
{
	// ����� ������
	class Camera
	{
	private:
		Mat4 m_move;	// ������� �����������
		Mat3 m_rot;		// ������� ��������
		Mat4 matrix;	// ����� ��������������

		// ��� �������� ����������� �� ��������� �����
		Camera() {}
	public:
		// ������ ��������� �� ��������
		static Camera* getInstance()
		{
			static Camera instance;
			return &instance;
		}

		// ������ ������� ������
		Vec3 position() const 
		{
			return low(m_move.l);
		}

		// ������ ����������� ������ ������
		Vec3 direction() const 
		{
			return Vec3(m_rot.i.z, m_rot.j.z, m_rot.k.z);
		}

		// ������ �������-������ ������ ������
		Vec3 right() const 
		{
			return Vec3(m_rot.i.x, m_rot.j.x, m_rot.k.x);
		}

		// �������� ������ � 3-� ���������� (yOz, xOz, xOy)
		void rotate(Vec3 angle)
		{
			// angle - ���� �������� �� ���� ����������
			Mat3 yoz = engine::rotate(Vec3(1.0f, 0.0f, 0.0f), angle.x);
			Mat3 xoz = engine::rotate(Vec3(0.0f, 1.0f, 0.0f), angle.y);
			Mat3 xoy = engine::rotate(Vec3(0.0f, 0.0f, 1.0f), angle.z);
			m_rot = yoz * xoz * xoy;
			matrix = Mat4(m_rot, Vec3(0.0f)) * m_move;
		}

		// ����������� ������ 
		void move(Vec3 bias)
		{
			// bias - ������ �����������
			m_move = m_move * engine::move(bias);
			matrix = Mat4(m_rot, Vec3(0.0f)) * m_move;
		}

		// ������ ������� �������������� � ������������ ������
		Mat4 view() const
		{
			return matrix;
		}
	};
}

#endif
