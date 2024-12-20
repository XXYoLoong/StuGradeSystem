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
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include "data.h"
#include "utils.h"

// ���� Data �ļ���
void createDataFolder() {
    struct stat st = { 0 };
    if (stat(DATA_FOLDER, &st) == -1) {
        _mkdir(DATA_FOLDER);
        printf("Data �ļ����Ѵ�����\n");
    }
}

void clearInputBuffer() {
    while (getchar() != '\n'); // ��ȡ��������ʣ��������ַ�ֱ�����з�
}

// ����༶���ݵ��ļ�
void saveDataToFile(int classIndex) {
    

    char filePath[150];
    snprintf(filePath, sizeof(filePath), "%s/class_%d.txt", DATA_FOLDER, classIndex);

    FILE* file = fopen(filePath, "w");
    if (!file) {
        printf("�޷��������ݵ��ļ���\n");
        return;
    }

    fprintf(file, "Class: %s\n", classes[classIndex].className);
    for (int i = 0; i < classes[classIndex].studentCount; i++) {
        fprintf(file, "Student: %s %s %c %.2f\n", classes[classIndex].students[i].id,
            classes[classIndex].students[i].name, classes[classIndex].students[i].gender,
            classes[classIndex].students[i].totalScore);
        for (int j = 0; j < classes[classIndex].students[i].courseCount; j++) {
            fprintf(file, "  Course: %s %.2f\n", classes[classIndex].students[i].courses[j].subject,
                classes[classIndex].students[i].courses[j].score);
        }
    }

    fclose(file);
    printf("�༶�����ѱ��浽��%s\n", filePath);
}
