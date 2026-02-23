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
