void initUserFile() {
    FILE* file = fopen(FILE_USER_DATA, "rb");

    if (!file) {
        printf("当前无用户，正在创建默认管理员账号...\n");

        file = fopen(FILE_USER_DATA, "wb");
        if (!file) return;

        User admin;
        strcpy(admin.username, "admin");
        strcpy(admin.password, "admin");
        strcpy(admin.role, "管理员");

        fwrite(&admin, sizeof(User), 1, file);
        fclose(file);

        printf("默认管理员创建成功!\n");
        printf("用户名: admin\n密码: admin\n\n");
    } else {
        fclose(file);
    }
}
