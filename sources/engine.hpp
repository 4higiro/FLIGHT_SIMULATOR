#ifndef ENGINE // ������ �� ���������� ���������
#define ENGINE

// ������� 
#define STB_IMAGE_IMPLEMENTATION

// ��������� ���������
#include <glad/glad.h>		// ����� ������� �������� ������� OpenGL
#include <GLFW/glfw3.h>		// ��������� ��� ������ � OpenGL
#include <stb/stb_image.h>	// �������� �����������

#include <iostream>			// ����-�����
#include <fstream>			// ������ � �������
#include <string>			// ��������� ������
#include <vector>			// ��������� ������������� �������

// ����������
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

// �������������� �����
typedef unsigned int Uint;
typedef int Int;
typedef size_t Size;
typedef float Float;
typedef double Double;
typedef char Char;
typedef char* Chars;
typedef unsigned char Uchar;
typedef unsigned char* Uchars;

// ��������� ������������ ������
#include "transform.hpp"			// ���������(-)��������� ��������
#include "counter.hpp"				// ��������� �������� ��������
#include "camera.hpp"				// ������ � �������
#include "shaders.hpp"				// ������ � ��������� � ��������� ����������
#include "buffer_objects.hpp"		// ������ � ��������� ���������
#include "texture.hpp"				// ������ � ����������
#include "model.hpp"				// ������ � ����������� ��������

// engine - ������������ ���� �������

namespace engine
{
	// ���������� ������� ����������� ���������� �������� ������
	void flyCamera(GLFWwindow* window, const Vec3 angle)
	{
		// window - ��������� �� ������ ���� � ���������� OpenGL
		// angle - ������� ������ � 3-� ����������

		// �������� ������� ������
		Camera* cam = Camera::getInstance();

		// ����������� ������ (����������: A(�����) S(������) D(�����) W(������) Q(�����) E(����))
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cam->move(Vec3(cam->direction().x * (-0.001f), 0.0f, cam->direction().z * (-0.001f)));
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cam->move(Vec3(cam->direction().x * 0.001f, 0.0f, cam->direction().z * 0.001f));
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cam->move(Vec3(cam->right().x * (-0.001f), 0.0f, cam->right().z * (-0.001f)));
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cam->move(Vec3(cam->right().x * 0.001f, 0.0f, cam->right().z * 0.001f));
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			cam->move(Vec3(0.0f, 0.001f, 0.0f));
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			cam->move(Vec3(0.0f, -0.001f, 0.0f));

		// ������� ������
		cam->rotate(Vec3(rad(-angle.y) / 15.0f, rad(angle.x) / 15.0f, rad(angle.z) / 15.0f));
	}
}

#endif
