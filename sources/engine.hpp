#ifndef ENGINE // Защита от повторного включения
#define ENGINE

// Макросы 
#define STB_IMAGE_IMPLEMENTATION

// Включение библиотек
#include <glad/glad.h>		// Поиск адресов хранения функций OpenGL
#include <GLFW/glfw3.h>		// Фреймворк для работы с OpenGL
#include <stb/stb_image.h>	// Загрузка изображений

#include <iostream>			// Ввод-вывод
#include <fstream>			// Работа с файлами
#include <string>			// Контейнер строки
#include <vector>			// Контейнер динамического массива

// Постоянные
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

// Переименование типов
typedef unsigned int Uint;
typedef int Int;
typedef size_t Size;
typedef float Float;
typedef double Double;
typedef char Char;
typedef char* Chars;
typedef unsigned char Uchar;
typedef unsigned char* Uchars;

// Включение заголовочных файлов
#include "transform.hpp"			// Матричные(-)векторные операции
#include "counter.hpp"				// Объектная оболочка счетчика
#include "camera.hpp"				// Работа с камерой
#include "shaders.hpp"				// Работа с шейдерами и шейдерной программой
#include "buffer_objects.hpp"		// Работа с буферными объектами
#include "texture.hpp"				// Работа с текстурами
#include "model.hpp"				// Работа с трехмерными моделями

// engine - пространство имен проекта

namespace engine
{
	// Обработчик событий стандартной реализации летающей камеры
	void flyCamera(GLFWwindow* window, const Vec3 angle)
	{
		// window - указатель на объект окна с контекстом OpenGL
		// angle - поворот камеры в 3-х плоскостях

		// Создание обхекта камеры
		Camera* cam = Camera::getInstance();

		// Перемещение камеры (Управление: A(влево) S(вправо) D(назад) W(вперед) Q(вверх) E(вниз))
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

		// Поворот камеры
		cam->rotate(Vec3(rad(-angle.y) / 15.0f, rad(angle.x) / 15.0f, rad(angle.z) / 15.0f));
	}
}

#endif
