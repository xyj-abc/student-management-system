int main() {
    studentList = loadStudentsFromFile();

    initUserFile();

    int choice;

    printf("1.登录\n2.注册\n请选择:");
    scanf("%d", &choice);

    if (choice == 2) {
        registerUser();
        printf("请重新登录\n");
    }

    if (!login()) {
        printf("登录失败\n");
        return 0;
    }

    if (strcmp(userRole, "学生") == 0) {
        studentMenu();
    } else if (strcmp(userRole, "教师") == 0) {
        teacherMenu();
    } else if (strcmp(userRole, "管理员") == 0) {
        adminMenu();
    }

    saveStudentsToFile(studentList);
    freeStudents(studentList);
    return 0;
}
