int main() {
    studentList = loadStudentsFromFile();

    if (!login()) {
        printf("登录失败\n");
        return 0;
    }

    if (strcmp(userRole, "学生") == 0) {
        studentMenu();
    }else if (strcmp(userRole, "教师") == 0) {
        teacherMenu();
    }else if (strcmp(userRole, "管理员") == 0) {
        adminMenu();
    }

    saveStudentsToFile(studentList);
    freeStudents(studentList);
    return 0;
}
