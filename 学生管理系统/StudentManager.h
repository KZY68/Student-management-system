#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "Student.h"
#include <string>
#include <vector>

class StudentManager {
public:
    bool addStudent(const Student& student);
    bool deleteStudent(const std::string& id);
    bool updateStudent(const std::string& id, const Student& student);
    const Student* findStudent(const std::string& id) const;
    const std::vector<Student>& getAllStudents() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

private:
    std::vector<Student> students;
};

#endif
