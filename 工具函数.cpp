Student* createStudent(int id, const char* name, int age, float score) {
    Student* s = (Student*)malloc(sizeof(Student));
    s->id = id;
    strncpy(s->name, name, MAX_NAME_LEN - 1);
    s->name[MAX_NAME_LEN - 1] = '\0';
    s->age = age;
    s->score = score;
    s->next = NULL;
    s->prev = NULL;
    return s;
}

void appendStudent(Student** head, Student* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Student* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void freeStudents(Student* head) {
    Student* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
