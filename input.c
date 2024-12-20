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
    // ���༶�����Ƿ���Ч
    if (classIndex < 0 || classIndex >= MAX_CLASSES) {
        printf("��Ч�İ༶������������ 0-%d ��Χ�ڵ�ֵ��\n", MAX_CLASSES - 1);
        return;
    }

    // ���༶�Ƿ�����
    if (classes[classIndex].studentCount >= MAX_STUDENTS) {
        printf("�༶ %d ѧ�������Ѵﵽ���ޣ�%d �ˣ����޷�¼����ѧ����\n", classIndex, MAX_STUDENTS);
        return;
    }

    Student* student = &classes[classIndex].students[classes[classIndex].studentCount];

    // ����ѧ����Ϣ
    printf("������ѧ��������");
    scanf_s("%s", student->name, (unsigned int)sizeof(student->name));
    clearInputBuffer();

    printf("������ѧ�ţ�");
    scanf_s("%s", student->id, (unsigned int)sizeof(student->id));
    clearInputBuffer();

    while (1) {
        printf("�������Ա�M/F����");
        scanf_s(" %c", &student->gender, 1);
        clearInputBuffer();
        if (student->gender == 'M' || student->gender == 'm' || student->gender == 'F' || student->gender == 'f') {
            break;
        }
        printf("������Ч���������д��Сд�� M �� F��\n");
    }

    printf("�������ѧ���Ŀγ���������� %d �ţ���", MAX_COURSES);
    if (scanf_s("%d", &student->courseCount) != 1 || student->courseCount < 1 || student->courseCount > MAX_COURSES) {
        printf("�γ�������Ч��¼��ʧ�ܡ�\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // ����γ̺ͳɼ�
    float total = 0;
    for (int i = 0; i < student->courseCount; i++) {
        printf("������γ� %d ���ƣ�", i + 1);
        scanf_s("%s", student->courses[i].subject, (unsigned int)sizeof(student->courses[i].subject));
        clearInputBuffer();

        printf("������γ� %d �ɼ���", i + 1);
        while (scanf_s("%f", &student->courses[i].score) != 1) {
            printf("������Ч�����������֣�");
            while (getchar() != '\n'); // ��ջ�����
        }
        clearInputBuffer();
        total += student->courses[i].score;
    }

    student->totalScore = total;
    classes[classIndex].studentCount++;
    saveDataToFile(classIndex);
    printf("ѧ���ɼ�¼��ɹ���\n");

    // ��ʾ�Ƿ񱣴�����
    char choice;
    while (1) {  // ʹ��ѭ��ȷ��������Ч
        printf("�Ƿ񱣴����ݵ��ļ�����Y/N����");
        scanf_s(" %c", &choice, 1);
        clearInputBuffer();
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
