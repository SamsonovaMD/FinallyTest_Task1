#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include <thread>

struct Student {
    int id;
    std::string name;
    int age;
};

class StudentDatabase {
private:
    std::vector<std::shared_ptr<Student>> students;
    std::mutex mtx;

public:
    // Добавление нового студента в базу данных
    void addStudent(int id, const std::string& name, int age) {
        std::lock_guard<std::mutex> lock(mtx);
        students.push_back(std::make_shared<Student>(Student{ id, name, age }));
    }

    // Удаление студента по идентификатору
    void removeStudent(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        students.erase(
            std::remove_if(students.begin(), students.end(),
                [id](const std::shared_ptr<Student>& s) { return s->id == id; }),
            students.end());
    }

    // Получение информации о студенте по идентификатору
    std::shared_ptr<Student> getStudent(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& student : students) {
            if (student->id == id) {
                return student;
            }
        }
        return nullptr;
    }
};

void writer(StudentDatabase& db) {
    for (int i = 0; i < 5; ++i) {
        db.addStudent(i, "Student " + std::to_string(i), 20 + i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Имитация задержки
    }
}

void reader(StudentDatabase& db) {
    for (int i = 0; i < 5; ++i) {
        std::shared_ptr<Student> student = db.getStudent(i);
        if (student != nullptr) {
            std::cout << "Student ID: " << student->id << ", Name: " << student->name << ", Age: " << student->age << std::endl;
        }
        else {
            std::cout << "Student with ID " << i << " not found." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Имитация задержки
    }
}

int main() {
    StudentDatabase db;

    std::thread writerThread(writer, std::ref(db));
    std::thread readerThread(reader, std::ref(db));

    writerThread.join();
    readerThread.join();

    return 0;
}
