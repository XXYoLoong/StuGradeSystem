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
#ifndef DATA_H
#define DATA_H

#define MAX_CLASSES 10         // ���༶����
#define MAX_STUDENTS 100      // ÿ���༶���ѧ������
#define MAX_COURSES 5         // ÿ��ѧ�����γ���
#define MAX_NAME_LEN 50       // ѧ��������󳤶�
#define MAX_ID_LEN 10         // ѧ����󳤶�
#define MAX_SUBJECT_LEN 50    // ��Ŀ������󳤶�
#define DATA_FOLDER "Data"    // ���ݱ�����ļ�������

// �ɼ��ṹ��
typedef struct {
    char subject[MAX_SUBJECT_LEN];  // ��Ŀ����
    float score;                    // �ɼ�
} Course;

// ѧ���ṹ��
typedef struct {
    char name[MAX_NAME_LEN];        // ѧ������
    char id[MAX_ID_LEN];            // ѧ��
    char gender;                    // �Ա�
    Course courses[MAX_COURSES];    // �γ���Ϣ
    int courseCount;                // �γ�����
    float totalScore;               // �ܷ�
} Student;

// �༶�ṹ��
typedef struct {
    char className[MAX_NAME_LEN];   // �༶����
    Student students[MAX_STUDENTS]; // ѧ������
    int studentCount;               // ѧ������
} Class;

// ����ȫ�ֱ���
extern Class classes[MAX_CLASSES];

#endif
