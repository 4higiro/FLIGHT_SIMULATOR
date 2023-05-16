#ifndef TEXTURE // ������ �� ���������� ���������
#define TEXTURE

#include "engine.hpp" // ��������� ���� ������������ ������

// engine - ������������ ���� �������

namespace engine
{
	// ����� ��������� ��������
	class Texture2D
	{
	private:
		mutable Uint id = 0U; // ������������� ��������

		// ��������� ���������� � �������������� ��������
		Texture2D(const Texture2D& other) {}
		Texture2D& operator=(const Texture2D& other) {}

		friend class Model; // �������� ���� � ������ �������� � ������ Model
	public:
		// ������� �������� �� ��������� OpenGL
		static void resetBind()
		{
			glBindTexture(GL_TEXTURE_2D, 0U);
		}

		// �������� ��������
		Texture2D()
		{
			glGenTextures(1, &id);
		}

		// ������ �������������� ��������
		Uint getID() const
		{
			return id;
		}

		// ��������� ��������� ���������� ��������� ��������
		void setConfig(Int mode, Int filtration)
		{
			// mode			- ����� ��������� �������� �� �������� ���������� ��������� 
			// filtration	- ����� ����������� ����� �������
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtration);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtration);
		}

		// ���������� �������� � ���������� OpenGL
		void bind() const
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}

		// �������� �������� �� �����
		void load(std::string path)
		{
			// path - ���� � ��������
			Int texture_width, texture_height, texture_channels;
			Uchars texture_data = stbi_load(path.c_str(), &texture_width, &texture_height, &texture_channels, 0);
			Int color_space = GL_RGBA;
			if (texture_channels < 4)
				color_space = GL_RGB; // ���� ���-�� ������� ����������� ������ 4-�, �� ����� ����� �� ������������
			glTexImage2D(GL_TEXTURE_2D, 0, color_space, texture_width, texture_height, 0, color_space, GL_UNSIGNED_BYTE, (void*)(texture_data));
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(texture_data);
		}

		// ������� ��������
		void clear()
		{
			if (id != 0U)
			{
				glDeleteTextures(1, &id);
				id = 0U;
			}
		}

		// ����������� ��������
		~Texture2D()
		{
			clear();
		}
	};
}

#endif 
