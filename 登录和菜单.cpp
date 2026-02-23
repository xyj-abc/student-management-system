int login() {
    char username[MAX_NAME_LEN], password[MAX_PASS_LEN];
    printf("用户名:");
    scanf("%s", username);
    printf("密码:");
    scanf("%s", password);

    FILE* file = fopen(FILE_USER_DATA, "rb");
    if (!file) {
		return 0;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            strcpy(userRole, user.role);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

/* ================= 菜单 ================= */

void studentMenu() {
    int c;
    do {
        printf("\n1.查看成绩\n2.查看排名\n0.退出\n");
        scanf("%d", &c);
        if (c == 1) {
			displayAllStudents(studentList);
        }
        if (c == 2) {
			classRanking(studentList);
        }
    } while (c != 0);
}

void teacherMenu() {
    int c;
    do {
        printf("\n1.查看\n2.修改成绩\n3.删除\n0.返回\n");
        scanf("%d", &c);
        if (c == 1) {
			displayAllStudents(studentList);
        }
        if (c == 2) {
			modifyStudentScore();
        }
        if (c == 3) {
			deleteStudent();
        }
    } while (c != 0);
}

void adminMenu() {
    int c;
    do {
        printf("\n1.添加学生\n2.查看学生\n3.注册账号\n0.返回\n");
        scanf("%d", &c);
        if (c == 1) {
			addStudent();
        }
        if (c == 2) {
			displayAllStudents(studentList);
        }
        if (c == 3) {
			registerUser();
        }
    
    } while (c != 0);
}
