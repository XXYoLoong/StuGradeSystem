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
#include "sort.h"

// 按学号排序并输出学生总分及排名
void sortAndPrintClassRanking(int classIndex) {
    if (classes[classIndex].studentCount == 0) {
        printf("班级中没有学生，无法排序！\n");
        return;
    }

    // 创建临时数组用于排序
    Student sortedStudents[MAX_STUDENTS];
    memcpy(sortedStudents, classes[classIndex].students, sizeof(classes[classIndex].students));

    // 冒泡排序，按学号升序排序
    for (int i = 0; i < classes[classIndex].studentCount - 1; i++) {
        for (int j = 0; j < classes[classIndex].studentCount - i - 1; j++) {
            if (strcmp(sortedStudents[j].id, sortedStudents[j + 1].id) > 0) {
                Student temp = sortedStudents[j];
                sortedStudents[j] = sortedStudents[j + 1];
                sortedStudents[j + 1] = temp;
            }
        }
    }

    // 打印排序后的学生信息
    printf("\n学号\t姓名\t总分\t排名\n");
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        printf("%s\t%s\t%.2f\t%d\n", sortedStudents[i].id, sortedStudents[i].name, sortedStudents[i].totalScore, i + 1);
    }

    // 提示是否保存数据
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

}
