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

#define MAX_CLASSES 10         // 最大班级数量
#define MAX_STUDENTS 100      // 每个班级最大学生人数
#define MAX_COURSES 5         // 每个学生最多课程数
#define MAX_NAME_LEN 50       // 学生姓名最大长度
#define MAX_ID_LEN 10         // 学号最大长度
#define MAX_SUBJECT_LEN 50    // 科目名称最大长度
#define DATA_FOLDER "Data"    // 数据保存的文件夹名称

// 成绩结构体
typedef struct {
    char subject[MAX_SUBJECT_LEN];  // 科目名称
    float score;                    // 成绩
} Course;

// 学生结构体
typedef struct {
    char name[MAX_NAME_LEN];        // 学生姓名
    char id[MAX_ID_LEN];            // 学号
    char gender;                    // 性别
    Course courses[MAX_COURSES];    // 课程信息
    int courseCount;                // 课程数量
    float totalScore;               // 总分
} Student;

// 班级结构体
typedef struct {
    char className[MAX_NAME_LEN];   // 班级名称
    Student students[MAX_STUDENTS]; // 学生数组
    int studentCount;               // 学生数量
} Class;

// 声明全局变量
extern Class classes[MAX_CLASSES];

#endif
