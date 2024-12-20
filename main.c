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
#include "data.h"
#include "utils.h"
#include "input.h"
#include "query.h"
#include "modify.h"
#include "delete.h"
#include "sort.h"

int main() {
    createDataFolder(); // 确保 Data 文件夹存在

    int choice, classIndex;

    while (1) {
        printf("\n学生成绩管理系统\n");
        printf("1. 录入学生成绩\n");
        printf("2. 查询课程平均分\n");
        printf("3. 查询学生成绩及排名\n");
        printf("4. 修改学生成绩\n");
        printf("5. 删除学生成绩\n");
        printf("6. 按学号排序输出学生总分及排名\n");
        printf("0. 退出程序\n");
        printf("请输入您的选择：");
        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请输入数字。\n");
            while (getchar() != '\n');  // 清空缓冲区
            continue;
        }

        switch (choice) {
        case 1:
            printf("请输入班级索引（0-%d）：", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("无效的班级索引，请重新输入。\n");
                while (getchar() != '\n'); // 清空缓冲区
                continue;
            }
            addStudentScore(classIndex);
            break;
        case 2:
            printf("请输入班级索引（0-%d）：", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("无效的班级索引。\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }
            queryCourseAverage(classIndex);
            break;
        case 3:
            printf("请输入班级索引（0-%d）：", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("无效的班级索引。\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }
            queryStudentRank(classIndex);
            break;
        case 4:
            printf("请输入班级索引（0-%d）：", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("无效的班级索引。\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }
            modifyStudentScore(classIndex);
            break;
        case 5:
            printf("请输入班级索引（0-%d）：", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("无效的班级索引。\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }
            deleteStudentScore(classIndex);
            break;
        case 6:
            printf("请输入班级索引（0-%d）：", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("无效的班级索引。\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }
            sortAndPrintClassRanking(classIndex);
            break;
        case 0:
            printf("程序已退出。\n");
            return 0;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }

    return 0;
}
