#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// 学生信息的数据模型
struct Student {
    std::string id;
    std::string name;
    int age;
    std::string gender;
    std::string major;
    double score;
};

#endif
