void saveStudentsToFile(Student* head) {
    FILE* file = fopen(FILE_STUDENT_DATA, "wb");
    if (!file) {
		return;
    }

    StudentData data;
    while (head) {
        data.id = head->id;
        strcpy(data.name, head->name);
        data.age = head->age;
        data.score = head->score;
        fwrite(&data, sizeof(StudentData), 1, file);
        head = head->next;
    }
    fclose(file);
}

Student* loadStudentsFromFile() {
    FILE* file = fopen(FILE_STUDENT_DATA, "rb");
    if (!file) {
		return NULL;
    }

    Student* head = NULL;
    StudentData data;

    while (fread(&data, sizeof(StudentData), 1, file)) {
        Student* newNode = createStudent(data.id, data.name, data.age, data.score);
        appendStudent(&head, newNode);
    }

    fclose(file);
    return head;
}

/* ================= 显示函数 ================= */

void displayStudent(Student* s) {
    printf("学号:%d 姓名:%s 年龄:%d 成绩:%.2f\n",s->id, s->name, s->age, s->score);
}

void displayAllStudents(Student* head) {
    while (head) {
        displayStudent(head);
        head = head->next;
    }
}
