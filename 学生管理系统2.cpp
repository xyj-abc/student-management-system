#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 50
#define PAGE_SIZE 5

#define FILE_STUDENT_DATA "students.dat"
#define FILE_USER_DATA "users.dat"

/* ================= 学生链表结构 ================= */

typedef struct Student {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    float score;
    struct Student* next;
    struct Student* prev;
} Student;

/* 用于文件存储（不含指针） */
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    float score;
} StudentData;

typedef struct {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    char role[MAX_NAME_LEN];
} User;

Student* studentList = NULL;
char userRole[MAX_NAME_LEN];

/* ================= 工具函数 ================= */

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

/* ================= 文件操作 ================= */

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

/* ================= 成绩分析 ================= */

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

/* ================= 教师功能 ================= */

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
            }else{
                studentList = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("删除成功\n");
            return;
        }
        temp = temp->next;
    }
    printf("未找到学生\n");
}

/* ================= 管理员功能 ================= */

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

/* ================= 登录 ================= */

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

/* ================= 主函数 ================= */

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
