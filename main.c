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
#include <stdlib.h>

#define MAX_CLASSES 5         // ���༶����
#define MAX_STUDENTS 100      // ÿ���༶���ѧ������
#define MAX_COURSES 5         // ÿ��ѧ�����γ���
#define MAX_NAME_LEN 50       // ѧ��������󳤶�
#define MAX_ID_LEN 15         // ѧ����󳤶�
#define MAX_SUBJECT_LEN 50    // ��Ŀ������󳤶�

// ����ɼ��ṹ��
typedef struct {
    char subject[MAX_SUBJECT_LEN];  // ��Ŀ����
    float score;                    // �ɼ�
} Course;

// ����ѧ���ṹ��
typedef struct {
    char name[MAX_NAME_LEN];        // ѧ������
    char id[MAX_ID_LEN];            // ѧ��
    char gender;                    // �Ա�
    Course courses[MAX_COURSES];    // �γ���Ϣ
    int courseCount;                // �γ�����
    float totalScore;               // �ܷ�
} Student;

// ����༶�ṹ��
typedef struct {
    char className[MAX_NAME_LEN];   // �༶����
    Student students[MAX_STUDENTS]; // ѧ������
    int studentCount;               // ѧ������
} Class;

// ȫ�ְ༶����
Class classes[MAX_CLASSES];

// ¼��ѧ���ɼ�
void addStudentScore(int classIndex, char* name, char* id, char gender, Course* courses, int courseCount) {
    if (classes[classIndex].studentCount < MAX_STUDENTS) {
        Student* student = &classes[classIndex].students[classes[classIndex].studentCount];

        strncpy_s(student->name, MAX_NAME_LEN, name, strlen(name));
        strncpy_s(student->id, MAX_ID_LEN, id, strlen(id));
        student->gender = gender;
        student->courseCount = courseCount;

        float total = 0;
        for (int i = 0; i < courseCount; i++) {
            student->courses[i] = courses[i];
            total += courses[i].score;
        }
        student->totalScore = total;

        classes[classIndex].studentCount++;
    }
    else {
        printf("�༶ѧ���������޷�¼����ѧ����\n");
    }
}

// ��ѯĳ�ſγ̵�ƽ����
void queryCourseAverage(int classIndex, char* subject) {
    float totalScore = 0;
    int courseCount = 0;
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        for (int j = 0; j < classes[classIndex].students[i].courseCount; j++) {
            if (strcmp(classes[classIndex].students[i].courses[j].subject, subject) == 0) {
                totalScore += classes[classIndex].students[i].courses[j].score;
                courseCount++;
                break;
            }
        }
    }

    if (courseCount > 0) {
        printf("��Ŀ %s ��ƽ������: %.2f\n", subject, totalScore / courseCount);
    }
    else {
        printf("û���ҵ���Ŀ %s��\n", subject);
    }
}

// ��ѯĳѧ���ĸ��γ̷������ּܷ��༶����
void queryStudentRank(int classIndex, char* studentId) {
    int rank = 1;
    Student* student = NULL;

    // ����ѧ��
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (strcmp(classes[classIndex].students[i].id, studentId) == 0) {
            student = &classes[classIndex].students[i];
            printf("ѧ��: %s ����: %s\n", student->id, student->name);
            printf("�ɼ�����:\n");
            for (int j = 0; j < student->courseCount; j++) {
                printf("��Ŀ: %s, �ɼ�: %.2f\n", student->courses[j].subject, student->courses[j].score);
            }
            printf("�ܷ�: %.2f\n", student->totalScore);
            break;
        }
    }

    if (!student) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", studentId);
        return;
    }

    // ��������
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        if (classes[classIndex].students[i].totalScore > student->totalScore) {
            rank++;
        }
    }

    printf("�༶����: %d\n", rank);
}

// ��ѧ���������ѧ���ּܷ��༶����
void sortAndPrintClassRanking(int classIndex) {
    // �����ܷ�����ѧ��
    for (int i = 0; i < classes[classIndex].studentCount - 1; i++) {
        for (int j = i + 1; j < classes[classIndex].studentCount; j++) {
            if (classes[classIndex].students[i].totalScore < classes[classIndex].students[j].totalScore) {
                Student temp = classes[classIndex].students[i];
                classes[classIndex].students[i] = classes[classIndex].students[j];
                classes[classIndex].students[j] = temp;
            }
        }
    }

    printf("ѧ��\t����\t�ܷ�\t����\n");
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        printf("%s\t%s\t%.2f\t%d\n", classes[classIndex].students[i].id, classes[classIndex].students[i].name,
            classes[classIndex].students[i].totalScore, i + 1);
    }
}

// ��ʾ�˵�����ȡ�û�����
void displayMenu() {
    printf("\nѧ���ɼ�����ϵͳ\n");
    printf("1. ¼��ѧ���ɼ�\n");
    printf("2. ��ѯ�γ�ƽ����\n");
    printf("3. ��ѯѧ���ɼ����༶����\n");
    printf("4. ��ѧ���������ѧ���ּܷ��༶����\n");
    printf("5. �˳�\n");
    printf("����������ѡ��: ");
}

int main() {
    int choice, classIndex;
    char studentId[MAX_ID_LEN];
    char subject[MAX_SUBJECT_LEN];
    char name[MAX_NAME_LEN], gender;
    Course courses[MAX_COURSES];
    int courseCount;

    while (1) {
        displayMenu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            // ¼��ѧ���ɼ�
            printf("������༶��� (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);

            if (classIndex < 0 || classIndex >= MAX_CLASSES) {
                printf("��Ч�İ༶��ţ�\n");
                break;
            }

            printf("������ѧ������: ");
            scanf_s("%s", name, MAX_NAME_LEN);
            printf("������ѧ��: ");
            scanf_s("%s", studentId, MAX_ID_LEN);
            printf("�������Ա� (M/F): ");
            scanf_s(" %c", &gender, 1);

            printf("������γ�����: ");
            scanf_s("%d", &courseCount);
            for (int i = 0; i < courseCount; i++) {
                printf("������γ� %d ������: ", i + 1);
                scanf_s("%s", courses[i].subject, MAX_SUBJECT_LEN);
                printf("������γ� %d �ĳɼ�: ", i + 1);
                scanf_s("%f", &courses[i].score);
            }

            addStudentScore(classIndex, name, studentId, gender, courses, courseCount);
            printf("ѧ���ɼ�¼��ɹ���\n");
            break;

        case 2:
            // ��ѯ�γ�ƽ����
            printf("������༶��� (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);
            printf("�������ѯ�Ŀγ�����: ");
            scanf_s("%s", subject, MAX_SUBJECT_LEN);
            queryCourseAverage(classIndex, subject);
            break;

        case 3:
            // ��ѯѧ���ɼ����༶����
            printf("������༶��� (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);
            printf("������ѧ��ѧ��: ");
            scanf_s("%s", studentId, MAX_ID_LEN);
            queryStudentRank(classIndex, studentId);
            break;

        case 4:
            // ��ѧ���������ѧ���ּܷ��༶����
            printf("������༶��� (0-%d): ", MAX_CLASSES - 1);
            scanf_s("%d", &classIndex);
            sortAndPrintClassRanking(classIndex);
            break;

        case 5:
            // �˳�
            printf("�˳�ϵͳ��\n");
            return 0;

        default:
            printf("��Ч��ѡ�����������롣\n");
        }
    }
    return 0;
}
