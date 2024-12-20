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
#include "data.h"
#include "utils.h"
#include "modify.h"

// 修改某学生的成绩
void modifyStudentScore(int classIndex) {
    char studentId[MAX_ID_LEN];
    char subject[MAX_SUBJECT_LEN];
    float newScore;

    printf("请输入学生学号：");
    scanf_s("%s", studentId, (unsigned int)sizeof(studentId));

    Student* student = NULL;
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (strcmp(classes[classIndex].students[i].id, studentId) == 0) {
            student = &classes[classIndex].students[i];
            break;
        }
    }

    if (student == NULL) {
        printf("未找到学号为 %s 的学生。\n", studentId);
        return;
    }

    printf("请输入需要修改的课程名称：");
    scanf_s("%s", subject, (unsigned int)sizeof(subject));

    for (int i = 0; i < student->courseCount; i++) {
        if (strcmp(student->courses[i].subject, subject) == 0) {
            printf("当前成绩为：%.2f\n", student->courses[i].score);
            printf("请输入新成绩：");
            while (scanf_s("%f", &newScore) != 1) {
                printf("输入无效，请重新输入数字：");
                while (getchar() != '\n');  // 清空缓冲区
            }
            student->courses[i].score = newScore;

            // 更新总分
            float total = 0;
            for (int j = 0; j < student->courseCount; j++) {
                total += student->courses[j].score;
            }
            student->totalScore = total;

            printf("成绩已更新！\n");

            char choice;
            while (1) {  // 使用循环确保输入有效
                printf("是否保存数据到文件？（Y/N）：");
                scanf_s(" %c", &choice, 1);
                while (getchar() != '\n');  // 清空缓冲区
                if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
                    break;  // 如果输入有效，则退出循环
                }
                printf("输入无效，请输入大写或小写的 Y 或 N。\n");
            }

            // 判断用户选择是否保存
            if (choice == 'Y' || choice == 'y') {
                saveDataToFile();
            }

            return;
        }
    }

    printf("未找到课程 %s。\n", subject);
}
