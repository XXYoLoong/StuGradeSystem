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
    createDataFolder(); // ȷ�� Data �ļ��д���

    int choice, classIndex;

    while (1) {
        printf("\nѧ���ɼ�����ϵͳ\n");
        printf("1. ¼��ѧ���ɼ�\n");
        printf("2. ��ѯ�γ�ƽ����\n");
        printf("3. ��ѯѧ���ɼ�������\n");
        printf("4. �޸�ѧ���ɼ�\n");
        printf("5. ɾ��ѧ���ɼ�\n");
        printf("6. ��ѧ���������ѧ���ּܷ�����\n");
        printf("0. �˳�����\n");
        printf("����������ѡ��");
        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч�����������֡�\n");
            while (getchar() != '\n');  // ��ջ�����
            continue;
        }

        switch (choice) {
        case 1:
            printf("������༶������0-%d����", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("��Ч�İ༶���������������롣\n");
                while (getchar() != '\n'); // ��ջ�����
                continue;
            }
            addStudentScore(classIndex);
            break;
        case 2:
            printf("������༶������0-%d����", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("��Ч�İ༶������\n");
                while (getchar() != '\n');  // ��ջ�����
                break;
            }
            queryCourseAverage(classIndex);
            break;
        case 3:
            printf("������༶������0-%d����", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("��Ч�İ༶������\n");
                while (getchar() != '\n');  // ��ջ�����
                break;
            }
            queryStudentRank(classIndex);
            break;
        case 4:
            printf("������༶������0-%d����", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("��Ч�İ༶������\n");
                while (getchar() != '\n');  // ��ջ�����
                break;
            }
            modifyStudentScore(classIndex);
            break;
        case 5:
            printf("������༶������0-%d����", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("��Ч�İ༶������\n");
                while (getchar() != '\n');  // ��ջ�����
                break;
            }
            deleteStudentScore(classIndex);
            break;
        case 6:
            printf("������༶������0-%d����", MAX_CLASSES - 1);
            if (scanf_s("%d", &classIndex) != 1 || classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("��Ч�İ༶������\n");
                while (getchar() != '\n');  // ��ջ�����
                break;
            }
            sortAndPrintClassRanking(classIndex);
            break;
        case 0:
            printf("�������˳���\n");
            return 0;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }
    }

    return 0;
}
