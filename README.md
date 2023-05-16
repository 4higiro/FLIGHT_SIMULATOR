<h1>Симулятор полета</h1>
<p>Планируется разработка визуализатора будущего виртуального испытательного стенда БПЛА самолетного типа. Данный визуализатор будет включать в себя:</p>
<ul>
  <li>Графический движок, разработанный с помощью графического API - OpenGL 3.3 Core Profile</li>
  <li>Физический движок (самописный), оснван на численном решении задачи Коши для расчета траектории полета БПЛА.
  <li>GUI для взаимодействия инженеров-расчетчиков с визуализатором</li>
  <li>Возможна интеграция с любыми программными инструментами</li>
</ul>
<p>На данный момент был разработан программный интерфейс графического движка, с помощью которого имеется возможность загружать и проводить линейные преобразования над трехмерными моделями. По части графического движка осталось только смоделировать модель освещения Фонга. В дальнейшем возможно более детальное развитие этого компонента визуализатора. Все вышеперечисленное будет разработанно в ближайшем будущем.</p>
<p>На данный момент демонстрационная версия выглядит так:</p>
<img src="resources/demo.gif" width=500px>
<h2>Программная составляющая</h2>
<ul>
  <li>Вектора и матрицы (файл sources/transform.hpp), необходим для взаимодействия с трехмерным пространством сцены. Переводу между разлиxными системами координат, а   в общем случае - произведению аффинных преобразований</li>
  <li>Класс модели (файл sources/model.hpp), необходим для загрузки модели и применению к ней аффинных преобразований в собственном локальном пространстве и переводу   в общее для всех моделей мировое пространство</li>
  <li>Класс камеры (файл sources/camera.hpp), необходим для перевода всех моделей на сцене в пространство обзора камеры. Позволяет менять точку и ракурс обзора на     усмотрение пользователя</li>
  <li>Прочие классы, являющиеся по большей части объектной оболочкой, необхожимой для взаимодействия с OpenGL.</li>
</ul>
<p>Разработка на данный момент активно ведется, почти каждый день будут появляться новые коммиты. В ближайшее время будет начата разработка физического движка!</p>
