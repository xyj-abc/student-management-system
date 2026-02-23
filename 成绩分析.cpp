void classRanking(Student* head) {
    if (!head) {
        printf("无学生数据\n");
        return;
    }

    int count = 0;
    Student* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }

    Student* arr[count];
    temp = head;
    for (int i = 0; i < count; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++) {
            if (arr[i]->score < arr[j]->score) {
                Student* t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }

    printf("\n--- 成绩排名 ---\n");
    for (int i = 0; i < count; i++) {
        printf("第%d名: %s %.2f\n", i + 1, arr[i]->name, arr[i]->score);
    }
}
