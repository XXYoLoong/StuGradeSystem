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
#include "delete.h"

// 删除某学生的成绩
void deleteStudentScore(int classIndex) {
    char studentId[MAX_ID_LEN];
    char subject[MAX_SUBJECT_LEN];

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

    printf("请输入需要删除的课程名称：");
    scanf_s("%s", subject, (unsigned int)sizeof(subject));

    for (int i = 0; i < student->courseCount; i++) {
        if (strcmp(student->courses[i].subject, subject) == 0) {
            // 删除课程
            for (int j = i; j < student->courseCount - 1; j++) {
                student->courses[j] = student->courses[j + 1];
            }
            student->courseCount--;

            // 更新总分
            float total = 0;
            for (int j = 0; j < student->courseCount; j++) {
                total += student->courses[j].score;
            }
            student->totalScore = total;

            printf("课程 %s 已删除！\n", subject);

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
