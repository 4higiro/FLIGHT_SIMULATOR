#ifndef TEXTURE // Защита от повторного включения
#define TEXTURE

#include "engine.hpp" // Включение всех заголовочных файлов

// engine - пространство имен проекта

namespace engine
{
	// Класс двумерной текстуры
	class Texture2D
	{
	private:
		mutable Uint id = 0U; // Идентификатор текстуры

		// Запрещено копировать и перезаписывать текстуру
		Texture2D(const Texture2D& other) {}
		Texture2D& operator=(const Texture2D& other) {}

		friend class Model; // Закрытые поля и методы доступны в классе Model
	public:
		// Отвязка текстуры от контекста OpenGL
		static void resetBind()
		{
			glBindTexture(GL_TEXTURE_2D, 0U);
		}

		// Создание текстуры
		Texture2D()
		{
			glGenTextures(1, &id);
		}

		// Геттер идентификатора текстуры
		Uint getID() const
		{
			return id;
		}

		// Установка дефолтных параметров рисования текстуры
		void setConfig(Int mode, Int filtration)
		{
			// mode			- режим рисования полигона за предлами текстурных координат 
			// filtration	- режим определения цвета текселя
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtration);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtration);
		}

		// Связывание текстуры с контекстом OpenGL
		void bind() const
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}

		// Загрузка текстуры из файла
		void load(std::string path)
		{
			// path - путь к текстуре
			Int texture_width, texture_height, texture_channels;
			Uchars texture_data = stbi_load(path.c_str(), &texture_width, &texture_height, &texture_channels, 0);
			Int color_space = GL_RGBA;
			if (texture_channels < 4)
				color_space = GL_RGB; // Если кол-во каналов изображения меньше 4-х, то альфа канал не записывается
			glTexImage2D(GL_TEXTURE_2D, 0, color_space, texture_width, texture_height, 0, color_space, GL_UNSIGNED_BYTE, (void*)(texture_data));
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(texture_data);
		}

		// Очистка текстуры
		void clear()
		{
			if (id != 0U)
			{
				glDeleteTextures(1, &id);
				id = 0U;
			}
		}

		// Уничтожение текстуры
		~Texture2D()
		{
			clear();
		}
	};
}

#endif 
