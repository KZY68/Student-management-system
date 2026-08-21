#include "StudentManager.h"

#include <fstream>
#include <iomanip>

bool StudentManager::addStudent(const Student& student) {
    if (findStudent(student.id) != NULL) {
        return false;
    }
    students.push_back(student);
    return true;
}

bool StudentManager::deleteStudent(const std::string& id) {
    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            return true;
        }
    }
    return false;
}

bool StudentManager::updateStudent(const std::string& id, const Student& student) {
    for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            *it = student;
            it->id = id;  // 学号不能被修改
            return true;
        }
    }
    return false;
}

const Student* StudentManager::findStudent(const std::string& id) const {
    for (std::vector<Student>::const_iterator it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            return &(*it);
        }
    }
    return NULL;
}

const std::vector<Student>& StudentManager::getAllStudents() const {
    return students;
}

bool StudentManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename.c_str());
    if (!file) {
        return false;
    }

    file << students.size() << '\n';
    for (std::vector<Student>::const_iterator it = students.begin(); it != students.end(); ++it) {
        file << it->id << '\n' << it->name << '\n' << it->age << '\n'
             << it->gender << '\n' << it->major << '\n'
             << std::setprecision(15) << it->score << '\n';
    }
    return true;
}

bool StudentManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file) {
        return false;
    }

    std::size_t count;
    if (!(file >> count)) {
        return false;
    }
    file.ignore(10000, '\n');

    std::vector<Student> loaded;
    for (std::size_t i = 0; i < count; ++i) {
        Student student;
        if (!std::getline(file, student.id) || !std::getline(file, student.name) ||
            !(file >> student.age)) {
            return false;
        }
        file.ignore(10000, '\n');
        if (!std::getline(file, student.gender) || !std::getline(file, student.major) ||
            !(file >> student.score)) {
            return false;
        }
        file.ignore(10000, '\n');
        loaded.push_back(student);
    }
    students = loaded;
    return true;
}
