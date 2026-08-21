#include "StudentManager.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

const char* DATA_FILE = "students.txt";

void printStudent(const Student& s) {
    cout << left << setw(12) << s.id << setw(14) << s.name
         << setw(8) << s.age << setw(10) << s.gender
         << setw(16) << s.major << fixed << setprecision(1) << s.score << '\n';
}

void showAll(const StudentManager& manager) {
    const vector<Student>& students = manager.getAllStudents();
    if (students.empty()) {
        cout << "暂无学生信息。\n";
        return;
    }
    cout << left << setw(12) << "学号" << setw(14) << "姓名" << setw(8) << "年龄"
         << setw(10) << "性别" << setw(16) << "专业" << "成绩\n";
    cout << "----------------------------------------------------------------\n";
    for (vector<Student>::const_iterator it = students.begin(); it != students.end(); ++it) {
        printStudent(*it);
    }
}

Student inputStudent() {
    Student s;
    cout << "学号：";
    cin >> s.id;
    cout << "姓名：";
    cin >> s.name;
    cout << "年龄：";
    cin >> s.age;
    cout << "性别：";
    cin >> s.gender;
    cout << "专业：";
    cin >> s.major;
    cout << "成绩：";
    cin >> s.score;
    return s;
}

void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    StudentManager manager;
    manager.loadFromFile(DATA_FILE);  // 第一次运行时文件不存在，忽略即可

    int choice = 0;
    while (choice != 6) {
        cout << "\n========== 学生管理系统 ==========\n"
             << "1. 添加学生\n2. 删除学生\n3. 修改学生\n"
             << "4. 查询学生\n5. 显示全部\n6. 保存并退出\n"
             << "请选择：";

        if (!(cin >> choice)) {
            clearBadInput();
            cout << "请输入菜单编号。\n";
            continue;
        }

        string id;
        const Student* student;
        switch (choice) {
        case 1:
            if (manager.addStudent(inputStudent())) cout << "添加成功。\n";
            else cout << "添加失败：学号已存在。\n";
            break;
        case 2:
            cout << "请输入要删除的学号：";
            cin >> id;
            cout << (manager.deleteStudent(id) ? "删除成功。\n" : "未找到该学生。\n");
            break;
        case 3:
            cout << "请输入要修改的学号：";
            cin >> id;
            if (manager.findStudent(id) == NULL) {
                cout << "未找到该学生。\n";
            } else if (manager.updateStudent(id, inputStudent())) {
                cout << "修改成功。\n";
            }
            break;
        case 4:
            cout << "请输入要查询的学号：";
            cin >> id;
            student = manager.findStudent(id);
            if (student == NULL) cout << "未找到该学生。\n";
            else {
                cout << left << setw(12) << "学号" << setw(14) << "姓名" << setw(8) << "年龄"
                     << setw(10) << "性别" << setw(16) << "专业" << "成绩\n";
                printStudent(*student);
            }
            break;
        case 5:
            showAll(manager);
            break;
        case 6:
            if (manager.saveToFile(DATA_FILE)) cout << "数据已保存，再见！\n";
            else cout << "数据保存失败。\n";
            break;
        default:
            cout << "无效选项，请重新输入。\n";
        }
    }
    return 0;
}
