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
#include "input.h"


void addStudentScore(int classIndex) {
    // 检查班级索引是否有效
    if (classIndex < 0 || classIndex >= MAX_CLASSES) {
        printf("无效的班级索引，请输入 0-%d 范围内的值。\n", MAX_CLASSES - 1);
        return;
    }

    // 检查班级是否已满
    if (classes[classIndex].studentCount >= MAX_STUDENTS) {
        printf("班级 %d 学生人数已达到上限（%d 人），无法录入新学生。\n", classIndex, MAX_STUDENTS);
        return;
    }

    Student* student = &classes[classIndex].students[classes[classIndex].studentCount];

    // 输入学生信息
    printf("请输入学生姓名：");
    scanf_s("%s", student->name, (unsigned int)sizeof(student->name));
    clearInputBuffer();

    printf("请输入学号：");
    scanf_s("%s", student->id, (unsigned int)sizeof(student->id));
    clearInputBuffer();

    while (1) {
        printf("请输入性别（M/F）：");
        scanf_s(" %c", &student->gender, 1);
        clearInputBuffer();
        if (student->gender == 'M' || student->gender == 'm' || student->gender == 'F' || student->gender == 'f') {
            break;
        }
        printf("输入无效，请输入大写或小写的 M 或 F。\n");
    }

    printf("请输入该学生的课程数量（最多 %d 门）：", MAX_COURSES);
    if (scanf_s("%d", &student->courseCount) != 1 || student->courseCount < 1 || student->courseCount > MAX_COURSES) {
        printf("课程数量无效，录入失败。\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // 输入课程和成绩
    float total = 0;
    for (int i = 0; i < student->courseCount; i++) {
        printf("请输入课程 %d 名称：", i + 1);
        scanf_s("%s", student->courses[i].subject, (unsigned int)sizeof(student->courses[i].subject));
        clearInputBuffer();

        printf("请输入课程 %d 成绩：", i + 1);
        while (scanf_s("%f", &student->courses[i].score) != 1) {
            printf("输入无效，请输入数字：");
            while (getchar() != '\n'); // 清空缓冲区
        }
        clearInputBuffer();
        total += student->courses[i].score;
    }

    student->totalScore = total;
    classes[classIndex].studentCount++;
    saveDataToFile(classIndex);
    printf("学生成绩录入成功！\n");

    // 提示是否保存数据
    char choice;
    while (1) {  // 使用循环确保输入有效
        printf("是否保存数据到文件？（Y/N）：");
        scanf_s(" %c", &choice, 1);
        clearInputBuffer();
        if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
            break;  // 如果输入有效，则退出循环
        }
        printf("输入无效，请输入大写或小写的 Y 或 N。\n");
    }

    // 判断用户选择是否保存
    if (choice == 'Y' || choice == 'y') {
        saveDataToFile();
    }

}
