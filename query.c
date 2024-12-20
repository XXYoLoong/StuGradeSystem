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
#include "query.h"

// 查询某门课程的平均分
void queryCourseAverage(int classIndex) {
    char subject[MAX_SUBJECT_LEN];
    printf("请输入查询的课程名称：");
    scanf_s("%s", subject, (unsigned int)sizeof(subject));

    float totalScore = 0;
    int courseCount = 0;

    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        for (int j = 0; j < classes[classIndex].students[i].courseCount; j++) {
            if (strcmp(classes[classIndex].students[i].courses[j].subject, subject) == 0) {
                totalScore += classes[classIndex].students[i].courses[j].score;
                courseCount++;
            }
        }
    }

    if (courseCount > 0) {
        printf("科目 %s 的平均分是：%.2f\n", subject, totalScore / courseCount);
    }
    else {
        printf("没有找到科目 %s 的成绩。\n", subject);
    }
}

// 查询某学生的所有成绩及排名
void queryStudentRank(int classIndex) {
    char studentId[MAX_ID_LEN];
    printf("请输入学生学号：");
    scanf_s("%s", studentId, (unsigned int)sizeof(studentId));

    Student* student = NULL;
    int rank = 1;

    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (strcmp(classes[classIndex].students[i].id, studentId) == 0) {
            student = &classes[classIndex].students[i];
            printf("学号: %s 姓名: %s\n", student->id, student->name);
            printf("成绩详情：\n");
            for (int j = 0; j < student->courseCount; j++) {
                printf("科目: %s, 成绩: %.2f\n", student->courses[j].subject, student->courses[j].score);
            }
            printf("总分: %.2f\n", student->totalScore);
            break;
        }
    }

    if (student == NULL) {
        printf("未找到学号为 %s 的学生。\n", studentId);
        return;
    }

    // 计算班级排名
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (classes[classIndex].students[i].totalScore > student->totalScore) {
            rank++;
        }
    }

    printf("班级排名: %d\n", rank);
}
