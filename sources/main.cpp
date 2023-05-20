#include "engine.hpp" // Включение всех заголовочных файлов

// Точка входа
int main()
{
	// Инициализация GLFW c версией OpenGL 3.3 Core Profile 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Cоздание окна
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Engine", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Создание контекста OpenGL для созданного окна
	glfwMakeContextCurrent(window);

	// Поиск и запись функций OpenGL 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Скрытие курсора
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Создание общего вершинного шейдера
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

	// Создание общего фрагментного шейдера
	engine::Shader general_fsh(GL_FRAGMENT_SHADER);
	Chars general_fsh_source;
	engine::loadShaderSource("shaders/general.frag", general_fsh_source);
	general_fsh.changeSource(general_fsh_source);
	if (!general_fsh.compile(info_log))
	{
		std::cout << "ERROR COMPILE GENERAL FRAGMENT SHADER:" << std::endl << info_log << std::endl;
		return -1;
	}

	// Создание общего вершинного шейдера
	engine::Shader light_vsh(GL_VERTEX_SHADER);
	Chars light_vsh_source;
	engine::loadShaderSource("shaders/light_source.vert", light_vsh_source);
	light_vsh.changeSource(light_vsh_source);
	if (!light_vsh.compile(info_log))
	{
		std::cout << "ERROR COMPILE GENERAL VERTEX SHADER:" << std::endl << info_log << std::endl;
		return -1;
	}

	// Создание фрагментного шейдера рендера источника света
	engine::Shader light_fsh(GL_FRAGMENT_SHADER);
	Chars light_fsh_source;
	engine::loadShaderSource("shaders/light_source.frag", light_fsh_source);
	light_fsh.changeSource(light_fsh_source);
	if (!light_fsh.compile(info_log))
	{
		std::cout << "ERROR COMPILE LIGHT FRAGMENT SHADER:" << std::endl << info_log << std::endl;
		return -1;
	}

	// Запись идентификаторов шейдеров 
	Uint general_vsh_id = general_vsh.getID();
	Uint general_fsh_id = general_fsh.getID();
	Uint light_vsh_id = light_vsh.getID();
	Uint light_fsh_id = light_fsh.getID();

	// Создание общей шейдерной программы
	engine::ShaderProgram general_shp(general_vsh_id, general_fsh_id);
	if (!general_shp.link(info_log))
	{
		std::cout << "ERROR LINK GENERAL SHADER PROGRAM:" << std::endl << info_log << std::endl;
		return -1;
	}

	// Создание шейдерной программы для рендера источника света
	engine::ShaderProgram light_shp(light_vsh_id, light_fsh_id);
	if (!light_shp.link(info_log))
	{
		std::cout << "ERROR LINK LIGHT SHADER PROGRAM:" << std::endl << info_log << std::endl;
		return -1;
	}

	// Удаление шейдеров
	general_vsh.clear();
	general_fsh.clear();
	light_vsh.clear();
	light_fsh.clear();

	// Запись идентификатора шейдерных программ
	Uint general_shp_id = general_shp.getID();
	Uint light_shp_id = light_shp.getID();

	// Установка вьюпорта на все окно
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

	/*
	// Создание и загрузка модели "Самолет"
	engine::Mesh plane_mesh;
	plane_mesh.load("resources/models/plane.mdl", "resources/textures/plane.png");
	std::vector<engine::Mesh*> plane_meshes;
	plane_meshes.push_back(&plane_mesh);
	engine::Model plane(plane_meshes);
	plane.move(engine::Vec3(0.0f, -0.75f, 4.0f));

	// Создание и загрузка модели "Куб"
	engine::Mesh cube_mesh;
	cube_mesh.load("resources/models/cube.mdl", "resources/textures/cube.png");
	std::vector<engine::Mesh*> cube_meshes;
	cube_meshes.push_back(&cube_mesh);
	engine::Model cube(cube_meshes);
	cube.move(engine::Vec3(0.0f, 0.0f, 4.0f));

	// Cоздание и загрузка модели "Источник света"
	engine::Mesh light_source_mesh;
	light_source_mesh.load("resources/models/light_source.mdl", " ");
	std::vector<engine::Mesh*> light_source_meshes;
	light_source_meshes.push_back(&light_source_mesh);
	engine::Model light_source(light_source_meshes);
	light_source.scale(engine::Vec3(0.25f));
	light_source.move(engine::Vec3(1.0f, -1.0f, 4.0f));
	*/

	std::string path = "resources/models/sphere/sphere.obj";
	std::vector<engine::Mesh*> meshes;
	engine::loadModel(path, meshes);
	engine::Model sphere(meshes);
	sphere.scale(engine::Vec3(0.25f));
	sphere.move(engine::Vec3(0.0f, 0.0f, 2.0f));
	sphere.transform(engine::Vec3(1.0f, 2.0f, 3.0f));

	// Параметры освещения
	general_shp.use();
	general_shp.setUniform("light_color", engine::Vec3(1.0f, 1.0f, 1.0f));

	// Создание объекта камеры
	engine::Camera* cam = engine::Camera::getInstance();
	engine::Mat4 view, projection; // Создание матриц перехожа между системами координат
	// Создание матрицы перспективной проекции
	projection = engine::perspective(0.1f, 1000.0f, engine::rad(30.0f), WIN_WIDTH, WIN_HEIGHT);

	glEnable(GL_DEPTH_TEST); // Включение теста глубины

	// Итерационно-вычисляемые переменные
	engine::Counter t, u;
	std::vector<Double> cursor_pos(2Ull);

	// Шаги счетчиков
	u.astep = engine::Vec3(0.0f, engine::rad(0.025f), 0.0f);

	// Установка позиции курсора в центре экрана
	glfwSetCursorPos(window, WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0);

	// Цикл рендера (Пока открыто окно)
	while (!glfwWindowShouldClose(window))
	{
		// Получение позиции курсора мыши
		glfwGetCursorPos(window, &cursor_pos[0], &cursor_pos[1]);

		// Обработка событий
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true); // Нажатие Escape - закрытие окна

		// Очистка буфера кадра (цвет и глубина)
		glClearColor(0.15f, 0.15f, 0.16f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Перемещение камеры
		t.astep = { static_cast<Float>(WIN_WIDTH / 2.0 - cursor_pos[0]), static_cast<Float>(WIN_HEIGHT / 2.0 - cursor_pos[1]), 0.0f };
		engine::flyCamera(window, t.angle);
		view = cam->view();

		// Запись матриц view и projection в шейдерные программы
		general_shp.use();
		general_shp.setUniform("view", view);
		general_shp.setUniform("projection", projection);
		light_shp.use();
		light_shp.setUniform("view", view);
		light_shp.setUniform("projection", projection);

		/*
		// Трансормации над моделью "Самолет"
		plane.rotate(u.angle);
		plane.transform(engine::Vec3(1.0f, 2.0f, 3.0f));
		plane.draw(general_shp); // Рендер "Самолета"

		// Трансформации над моделью "Куб"
		cube.transform(engine::Vec3(1.0f, 2.0f, 3.0f));
		cube.draw(general_shp); // Рендер "Куба"

		// Трансформации над моделью "Источник света"
		light_source.transform(engine::Vec3(1.0f, 2.0f, 3.0f));
		light_source.draw(light_shp); // Рендер "Источника света"
		*/

		sphere.draw(general_shp);

		// Замена буфера кудра и загрузка событий
		glfwSwapBuffers(window);
		glfwPollEvents();

		if(t.i % 2 == 0) // Раз в 2 кадра перемещение курсора на середину экрана
			glfwSetCursorPos(window, WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0);

		// Увеличение счетчиков
		t++; 
		u++;
	}

	// Завершение работы
	glfwTerminate();
	return 0;
}