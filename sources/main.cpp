#include "engine.hpp" // ��������� ���� ������������ ������

// ����� �����
int main()
{
	// ������������� GLFW c ������� OpenGL 3.3 Core Profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// C������� ����
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Engine", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// �������� ��������� OpenGL ��� ���������� ����
	glfwMakeContextCurrent(window);

	// ����� � ������ ������� OpenGL 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ������� �������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// �������� ������ ���������� �������
	engine::Shader general_vsh(GL_VERTEX_SHADER);
	Chars general_vsh_source;
	engine::loadShaderSource("shaders/general.vert", general_vsh_source);
	general_vsh.changeSource(general_vsh_source);
	Char info_log[512];
	if (!general_vsh.compile(info_log))
	{
		std::cout << "ERROR COMPILE GENERAL VERTEX SHADER:" << std::endl << info_log << std::endl;
		return -1;
	}

	// �������� ������ ������������ �������
	engine::Shader general_fsh(GL_FRAGMENT_SHADER);
	Chars general_fsh_source;
	engine::loadShaderSource("shaders/general.frag", general_fsh_source);
	general_fsh.changeSource(general_fsh_source);
	if (!general_fsh.compile(info_log))
	{
		std::cout << "ERROR COMPILE GENERAL FRAGMENT SHADER:" << std::endl << info_log << std::endl;
		return -1;
	}

	// �������� ������ ���������� �������
	engine::Shader light_vsh(GL_VERTEX_SHADER);
	Chars light_vsh_source;
	engine::loadShaderSource("shaders/light_source.vert", light_vsh_source);
	light_vsh.changeSource(light_vsh_source);
	if (!light_vsh.compile(info_log))
	{
		std::cout << "ERROR COMPILE GENERAL VERTEX SHADER:" << std::endl << info_log << std::endl;
		return -1;
	}

	// �������� ������������ ������� ������� ��������� �����
	engine::Shader light_fsh(GL_FRAGMENT_SHADER);
	Chars light_fsh_source;
	engine::loadShaderSource("shaders/light_source.frag", light_fsh_source);
	light_fsh.changeSource(light_fsh_source);
	if (!light_fsh.compile(info_log))
	{
		std::cout << "ERROR COMPILE LIGHT FRAGMENT SHADER:" << std::endl << info_log << std::endl;
		return -1;
	}

	// ������ ��������������� �������� 
	Uint general_vsh_id = general_vsh.getID();
	Uint general_fsh_id = general_fsh.getID();
	Uint light_vsh_id = light_vsh.getID();
	Uint light_fsh_id = light_fsh.getID();

	// �������� ����� ��������� ���������
	engine::ShaderProgram general_shp(general_vsh_id, general_fsh_id);
	if (!general_shp.link(info_log))
	{
		std::cout << "ERROR LINK GENERAL SHADER PROGRAM:" << std::endl << info_log << std::endl;
		return -1;
	}

	// �������� ��������� ��������� ��� ������� ��������� �����
	engine::ShaderProgram light_shp(light_vsh_id, light_fsh_id);
	if (!light_shp.link(info_log))
	{
		std::cout << "ERROR LINK LIGHT SHADER PROGRAM:" << std::endl << info_log << std::endl;
		return -1;
	}

	// �������� ��������
	general_vsh.clear();
	general_fsh.clear();
	light_vsh.clear();
	light_fsh.clear();

	// ������ �������������� ��������� ��������
	Uint general_shp_id = general_shp.getID();
	Uint light_shp_id = light_shp.getID();

	// ��������� �������� �� ��� ����
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	// �������� � �������� ������ "�������"
	engine::Model plane;
	plane.load("resources/models/plane.mdl", "resources/textures/plane.png");
	plane.move(engine::Vec3(0.0f, -0.75f, 4.0f));

	// �������� � �������� ������ "���"
	engine::Model cube;
	cube.load("resources/models/cube.mdl", "resources/textures/cube.png");
	cube.move(engine::Vec3(0.0f, 0.0f, 4.0f));

	// C������� � �������� ������ "�������� �����"
	engine::Model light_source;
	light_source.load("resources/models/light_source.mdl", " ");
	light_source.scale(engine::Vec3(0.025f));
	light_source.move(engine::Vec3(1.0f, -1.0f, 4.0f));

	// ��������� ���������
	general_shp.use();
	general_shp.setUniform("light_color", engine::Vec3(1.0f, 1.0f, 1.0f));

	// �������� ������� ������
	engine::Camera* cam = engine::Camera::getInstance();
	engine::Mat4 view, projection; // �������� ������ �������� ����� ��������� ���������
	// �������� ������� ������������� ��������
	projection = engine::perspective(0.1f, 1000.0f, engine::rad(30.0f), WIN_WIDTH, WIN_HEIGHT);

	glEnable(GL_DEPTH_TEST); // ��������� ����� �������

	// �����������-����������� ����������
	engine::Counter t, u;
	std::vector<Double> cursor_pos(2Ull);

	// ���� ���������
	u.astep = engine::Vec3(0.0f, engine::rad(0.025f), 0.0f);

	// ��������� ������� ������� � ������ ������
	glfwSetCursorPos(window, WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0);

	// ���� ������� (���� ������� ����)
	while (!glfwWindowShouldClose(window))
	{
		// ��������� ������� ������� ����
		glfwGetCursorPos(window, &cursor_pos[0], &cursor_pos[1]);

		// ��������� �������
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true); // ������� Escape - �������� ����

		// ������� ������ ����� (���� � �������)
		glClearColor(0.15f, 0.15f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ����������� ������
		t.astep = { static_cast<Float>(WIN_WIDTH / 2.0 - cursor_pos[0]), static_cast<Float>(WIN_HEIGHT / 2.0 - cursor_pos[1]), 0.0f };
		engine::flyCamera(window, t.angle);
		view = cam->view();

		// ������ ������ view � projection � ��������� ���������
		general_shp.use();
		general_shp.setUniform("view", view);
		general_shp.setUniform("projection", projection);
		light_shp.use();
		light_shp.setUniform("view", view);
		light_shp.setUniform("projection", projection);

		// ������������ ��� ������� "�������"
		plane.rotate(u.angle);
		plane.transform(engine::Vec3(1.0f, 2.0f, 3.0f));
		plane.draw(general_shp); // ������ "��������"

		// ������������� ��� ������� "���"
		cube.transform(engine::Vec3(1.0f, 2.0f, 3.0f));
		cube.draw(general_shp); // ������ "����"

		// ������������� ��� ������� "�������� �����"
		light_source.transform(engine::Vec3(1.0f, 2.0f, 3.0f));
		light_source.draw(light_shp); // ������ "��������� �����"

		// ������ ������ ����� � �������� �������
		glfwSwapBuffers(window);
		glfwPollEvents();

		if(t.i % 2 == 0) // ��� � 2 ����� ����������� ������� �� �������� ������
			glfwSetCursorPos(window, WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0);

		// ���������� ���������
		t++; 
		u++;
	}

	// ���������� ������
	glfwTerminate();
	return 0;
}