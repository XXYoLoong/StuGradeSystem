//Copyright 2024 Jiacheng Ni
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLASSES 5         // 最大班级数量
#define MAX_STUDENTS 100      // 每个班级最大学生人数
#define MAX_COURSES 5         // 每个学生最多课程数
#define MAX_NAME_LEN 50       // 学生姓名最大长度
#define MAX_ID_LEN 15         // 学号最大长度
#define MAX_SUBJECT_LEN 50    // 科目名称最大长度

// 定义成绩结构体
typedef struct {
    char subject[MAX_SUBJECT_LEN];  // 科目名称
    float score;                    // 成绩
} Course;

// 定义学生结构体
typedef struct {
    char name[MAX_NAME_LEN];        // 学生姓名
    char id[MAX_ID_LEN];            // 学号
    char gender;                    // 性别
    Course courses[MAX_COURSES];    // 课程信息
    int courseCount;                // 课程数量
    float totalScore;               // 总分
} Student;

// 定义班级结构体
typedef struct {
    char className[MAX_NAME_LEN];   // 班级名称
    Student students[MAX_STUDENTS]; // 学生数组
    int studentCount;               // 学生数量
} Class;

// 全局班级数组
Class classes[MAX_CLASSES];

// 录入学生成绩
void addStudentScore(int classIndex, char* name, char* id, char gender, Course* courses, int courseCount) {
    if (classes[classIndex].studentCount < MAX_STUDENTS) {
        Student* student = &classes[classIndex].students[classes[classIndex].studentCount];

        strncpy_s(student->name, MAX_NAME_LEN, name, strlen(name));
        strncpy_s(student->id, MAX_ID_LEN, id, strlen(id));
        student->gender = gender;
        student->courseCount = courseCount;

        float total = 0;
        for (int i = 0; i < courseCount; i++) {
            student->courses[i] = courses[i];
            total += courses[i].score;
        }
        student->totalScore = total;

        classes[classIndex].studentCount++;
    }
    else {
        printf("班级学生已满，无法录入新学生。\n");
    }
}

// 查询某门课程的平均分
void queryCourseAverage(int classIndex, char* subject) {
    float totalScore = 0;
    int courseCount = 0;
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        for (int j = 0; j < classes[classIndex].students[i].courseCount; j++) {
            if (strcmp(classes[classIndex].students[i].courses[j].subject, subject) == 0) {
                totalScore += classes[classIndex].students[i].courses[j].score;
                courseCount++;
                break;
            }
        }
    }

    if (courseCount > 0) {
        printf("科目 %s 的平均分是: %.2f\n", subject, totalScore / courseCount);
    }
    else {
        printf("没有找到科目 %s。\n", subject);
    }
}

// 查询某学生的各课程分数、总分及班级排名
void queryStudentRank(int classIndex, char* studentId) {
    int rank = 1;
    Student* student = NULL;

    // 查找学生
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (strcmp(classes[classIndex].students[i].id, studentId) == 0) {
            student = &classes[classIndex].students[i];
            printf("学号: %s 姓名: %s\n", student->id, student->name);
            printf("成绩详情:\n");
            for (int j = 0; j < student->courseCount; j++) {
                printf("科目: %s, 成绩: %.2f\n", student->courses[j].subject, student->courses[j].score);
            }
            printf("总分: %.2f\n", student->totalScore);
            break;
        }
    }

    if (!student) {
        printf("未找到学号为 %s 的学生。\n", studentId);
        return;
    }

    // 计算排名
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (classes[classIndex].students[i].totalScore > student->totalScore) {
            rank++;
        }
    }

    printf("班级排名: %d\n", rank);
}

// 按学号排序输出学生总分及班级排名
void sortAndPrintClassRanking(int classIndex) {
    // 按照总分排序学生
    for (int i = 0; i < classes[classIndex].studentCount - 1; i++) {
        for (int j = i + 1; j < classes[classIndex].studentCount; j++) {
            if (classes[classIndex].students[i].totalScore < classes[classIndex].students[j].totalScore) {
                Student temp = classes[classIndex].students[i];
                classes[classIndex].students[i] = classes[classIndex].students[j];
                classes[classIndex].students[j] = temp;
            }
        }
    }

    printf("学号\t姓名\t总分\t排名\n");
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        printf("%s\t%s\t%.2f\t%d\n", classes[classIndex].students[i].id, classes[classIndex].students[i].name,
            classes[classIndex].students[i].totalScore, i + 1);
    }
}

// 显示菜单并获取用户输入
void displayMenu() {
    printf("\n学生成绩管理系统\n");
    printf("1. 录入学生成绩\n");
    printf("2. 查询课程平均分\n");
    printf("3. 查询学生成绩及班级排名\n");
    printf("4. 按学号排序输出学生总分及班级排名\n");
    printf("5. 退出\n");
    printf("请输入您的选择: ");
}

int main() {
    int choice, classIndex;
    char studentId[MAX_ID_LEN];
    char subject[MAX_SUBJECT_LEN];
    char name[MAX_NAME_LEN], gender;
    Course courses[MAX_COURSES];
    int courseCount;

    while (1) {
        displayMenu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            // 录入学生成绩
            printf("请输入班级编号 (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);

            if (classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("无效的班级编号！\n");
                break;
            }

            printf("请输入学生姓名: ");
            scanf_s("%s", name, MAX_NAME_LEN);
            printf("请输入学号: ");
            scanf_s("%s", studentId, MAX_ID_LEN);
            printf("请输入性别 (M/F): ");
            scanf_s(" %c", &gender, 1);

            printf("请输入课程数量: ");
            scanf_s("%d", &courseCount);
            for (int i = 0; i < courseCount; i++) {
                printf("请输入课程 %d 的名称: ", i + 1);
                scanf_s("%s", courses[i].subject, MAX_SUBJECT_LEN);
                printf("请输入课程 %d 的成绩: ", i + 1);
                scanf_s("%f", &courses[i].score);
            }

            addStudentScore(classIndex, name, studentId, gender, courses, courseCount);
            printf("学生成绩录入成功！\n");
            break;

        case 2:
            // 查询课程平均分
            printf("请输入班级编号 (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);
            printf("请输入查询的课程名称: ");
            scanf_s("%s", subject, MAX_SUBJECT_LEN);
            queryCourseAverage(classIndex, subject);
            break;

        case 3:
            // 查询学生成绩及班级排名
            printf("请输入班级编号 (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);
            printf("请输入学生学号: ");
            scanf_s("%s", studentId, MAX_ID_LEN);
            queryStudentRank(classIndex, studentId);
            break;

        case 4:
            // 按学号排序输出学生总分及班级排名
            printf("请输入班级编号 (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);
            sortAndPrintClassRanking(classIndex);
            break;

        case 5:
            // 退出
            printf("退出系统。\n");
            return 0;

        default:
            printf("无效的选择，请重新输入。\n");
        }
    }
    return 0;
}
