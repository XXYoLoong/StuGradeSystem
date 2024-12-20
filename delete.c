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

// ɾ��ĳѧ���ĳɼ�
void deleteStudentScore(int classIndex) {
    char studentId[MAX_ID_LEN];
    char subject[MAX_SUBJECT_LEN];

    printf("������ѧ��ѧ�ţ�");
    scanf_s("%s", studentId, (unsigned int)sizeof(studentId));

    Student* student = NULL;
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (strcmp(classes[classIndex].students[i].id, studentId) == 0) {
            student = &classes[classIndex].students[i];
            break;
        }
    }

    if (student == NULL) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", studentId);
        return;
    }

    printf("��������Ҫɾ���Ŀγ����ƣ�");
    scanf_s("%s", subject, (unsigned int)sizeof(subject));

    for (int i = 0; i < student->courseCount; i++) {
        if (strcmp(student->courses[i].subject, subject) == 0) {
            // ɾ���γ�
            for (int j = i; j < student->courseCount - 1; j++) {
                student->courses[j] = student->courses[j + 1];
            }
            student->courseCount--;

            // �����ܷ�
            float total = 0;
            for (int j = 0; j < student->courseCount; j++) {
                total += student->courses[j].score;
            }
            student->totalScore = total;

            printf("�γ� %s ��ɾ����\n", subject);

            char choice;
            while (1) {  // ʹ��ѭ��ȷ��������Ч
                printf("�Ƿ񱣴����ݵ��ļ�����Y/N����");
                scanf_s(" %c", &choice, 1);
                while (getchar() != '\n');  // ��ջ�����
                if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
                    break;  // ���������Ч�����˳�ѭ��
                }
                printf("������Ч���������д��Сд�� Y �� N��\n");
            }

            // �ж��û�ѡ���Ƿ񱣴�
            if (choice == 'Y' || choice == 'y') {
                saveDataToFile();
            }

            return;
        }
    }

    printf("δ�ҵ��γ� %s��\n", subject);
}
