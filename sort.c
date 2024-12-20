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

// ��ѧ���������ѧ���ּܷ�����
void sortAndPrintClassRanking(int classIndex) {
    if (classes[classIndex].studentCount == 0) {
        printf("�༶��û��ѧ�����޷�����\n");
        return;
    }

    // ������ʱ������������
    Student sortedStudents[MAX_STUDENTS];
    memcpy(sortedStudents, classes[classIndex].students, sizeof(classes[classIndex].students));

    // ð�����򣬰�ѧ����������
    for (int i = 0; i < classes[classIndex].studentCount - 1; i++) {
        for (int j = 0; j < classes[classIndex].studentCount - i - 1; j++) {
            if (strcmp(sortedStudents[j].id, sortedStudents[j + 1].id) > 0) {
                Student temp = sortedStudents[j];
                sortedStudents[j] = sortedStudents[j + 1];
                sortedStudents[j + 1] = temp;
            }
        }
    }

    // ��ӡ������ѧ����Ϣ
    printf("\nѧ��\t����\t�ܷ�\t����\n");
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        printf("%s\t%s\t%.2f\t%d\n", sortedStudents[i].id, sortedStudents[i].name, sortedStudents[i].totalScore, i + 1);
    }

    // ��ʾ�Ƿ񱣴�����
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

}
