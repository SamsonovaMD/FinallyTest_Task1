Напишите класс на C++, который реализует простую систему управления базой данных студентов. Каждый студент представлен структурой Student, 
содержащей следующие поля: id (целочисленный идентификатор), name (строка с именем студента), и age (целочисленный возраст студента). 
Ваш класс должен обеспечивать следующие возможности:
- Добавление нового студента в базу данных. 
- Удаление студента по идентификатору.
- Получение информации о студенте по идентификатору. 
- Используйте умный указатель std::shared_ptr для хранения и управления объектами студентов в контейнере внутри класса (например, std::vector или std::map). 
- Разработайте программу, демонстрирующую создание двух потоков в C++, где один поток пишет данные в переменную, а другой читает из нее,
с использованием мьютексов для синхронизации доступа.

Структура Student: 
  В структуре Student определены поля id, name и age, которые представляют идентификатор, имя и возраст студента соответственно.
Класс StudentDatabase:
  В приватной секции класса StudentDatabase определены поля:
    students: вектор указателей std::shared_ptr на объекты Student, представляющие базу данных студентов.
    mtx: мьютекс для синхронизации доступа к базе данных из разных потоков.
  В публичной секции класса определены методы:
    addStudent: добавляет нового студента в базу данных.
    removeStudent: удаляет студента из базы данных по идентификатору.
    getStudent: получает информацию о студенте по его идентификатору.
Метод addStudent:
  Метод addStudent принимает идентификатор, имя и возраст студента.
  Создается объект Student с переданными данными.
  Создается std::shared_ptr для этого объекта Student.
  Получив доступ к мьютексу, указатель на студента добавляется в вектор students.
Метод removeStudent:
  Метод removeStudent принимает идентификатор студента, которого нужно удалить.
  Получив доступ к мьютексу, происходит поиск студента с данным идентификатором в векторе students.
  Если студент найден, он удаляется из вектора.
Метод getStudent:
  Метод getStudent принимает идентификатор студента.
  Получив доступ к мьютексу, происходит поиск студента с данным идентификатором в векторе students.
  Если студент найден, возвращается указатель на него. Если нет — возвращается nullptr.
