void addStudent() {
    int id, age;
    char name[MAX_NAME_LEN];
    float score;

    printf("学号:");
    scanf("%d", &id);
    printf("姓名:");
    scanf("%s", name);
    printf("年龄:");
    scanf("%d", &age);
    printf("成绩:");
    scanf("%f", &score);

    Student* s = createStudent(id, name, age, score);
    appendStudent(&studentList, s);
    printf("添加成功\n");
}

void registerUser() {
    FILE* file = fopen(FILE_USER_DATA, "ab");
    if (!file) {
		return;
    }

    User user;
    printf("用户名:");
    scanf("%s", user.username);
    printf("密码:");
    scanf("%s", user.password);
    printf("角色(学生/教师/管理员):");
    scanf("%s", user.role);

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
    printf("注册成功\n");
}
