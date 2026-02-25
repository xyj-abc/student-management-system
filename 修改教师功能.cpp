void modifyStudentScore() {
    int id;
    printf("输入要修改的学号:");
    scanf("%d", &id);

    Student* temp = studentList;
    while (temp) {
        if (temp->id == id) {
            printf("输入新成绩:");
            scanf("%f", &temp->score);

            printf("修改成功!\n");

            /* 立即保存 */
            saveStudentsToFile(studentList);
            return;
        }
        temp = temp->next;
    }

    printf("未找到该学生\n");
}

void deleteStudent() {
    int id;
    printf("输入要删除的学号:");
    scanf("%d", &id);

    Student* temp = studentList;
    while (temp) {
        if (temp->id == id) {

            if (temp->prev) {
                temp->prev->next = temp->next;
            } else {
                studentList = temp->next;
            }

            if (temp->next) {
                temp->next->prev = temp->prev;
            }

            free(temp);

            printf("删除成功\n");

            /* 立即保存 */
            saveStudentsToFile(studentList);
            return;
        }

        temp = temp->next;
    }

    printf("未找到学生\n");
}
