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

// ��ѯĳ�ſγ̵�ƽ����
void queryCourseAverage(int classIndex) {
    char subject[MAX_SUBJECT_LEN];
    printf("�������ѯ�Ŀγ����ƣ�");
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
        printf("��Ŀ %s ��ƽ�����ǣ�%.2f\n", subject, totalScore / courseCount);
    }
    else {
        printf("û���ҵ���Ŀ %s �ĳɼ���\n", subject);
    }
}

// ��ѯĳѧ�������гɼ�������
void queryStudentRank(int classIndex) {
    char studentId[MAX_ID_LEN];
    printf("������ѧ��ѧ�ţ�");
    scanf_s("%s", studentId, (unsigned int)sizeof(studentId));

    Student* student = NULL;
    int rank = 1;

    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (strcmp(classes[classIndex].students[i].id, studentId) == 0) {
            student = &classes[classIndex].students[i];
            printf("ѧ��: %s ����: %s\n", student->id, student->name);
            printf("�ɼ����飺\n");
            for (int j = 0; j < student->courseCount; j++) {
                printf("��Ŀ: %s, �ɼ�: %.2f\n", student->courses[j].subject, student->courses[j].score);
            }
            printf("�ܷ�: %.2f\n", student->totalScore);
            break;
        }
    }

    if (student == NULL) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", studentId);
        return;
    }

    // ����༶����
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (classes[classIndex].students[i].totalScore > student->totalScore) {
            rank++;
        }
    }

    printf("�༶����: %d\n", rank);
}
