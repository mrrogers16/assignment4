#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_BUFF_SIZE 4096
#define COURSE_FILENAME "courses.dat"

typedef struct COURSE
{
    char course_Name[84];
    char course_Sched[4];
    unsigned course_Size;
    unsigned course_Hours;
} Course;

int main(int argc, char *argv[])
{

    Course course;
    Course temp;
    char input[STD_BUFF_SIZE];
    int course_hours;
    int course_num;
    int course_read;
    int course_size;
    int seek;
    int read;

    char course_name_buff[STD_BUFF_SIZE];
    char course_size_buff[STD_BUFF_SIZE];
    char course_hours_buff[STD_BUFF_SIZE];
    char course_schedule_buff[STD_BUFF_SIZE];
    char course_number_buff[STD_BUFF_SIZE];

    char *file_name = argv[1];
    FILE *fp = fopen(file_name, "rb+");
    if (fp == NULL)
    {
        printf("FIRST: Error opening file %s", file_name);
        return 1;
    }

    do
    {
        printf("Enter one of the following actions or press CTRL-D to exit.\nC - create a new course record\nU - update an existing course record\nR - read an existing course record\nD - delete an existing course record\n");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }
        input[strlen(input) - 1] = '\0';

        switch (input[0])
        {
        case 'C':
        case 'c':
            printf("Course number: \n");
            fgets(input, STD_BUFF_SIZE, stdin);
            sscanf(input, "%d", &course_num);

            printf("Course Name: \n");
            fgets(course_name_buff, 84, stdin);
            course_name_buff[strlen(course_name_buff) - 1] = '\0';
            strcpy(course.course_Name, course_name_buff);

            printf("Course Schedule: \n");
            fgets(course_schedule_buff, 5, stdin);
            course_schedule_buff[strlen(course_schedule_buff) - 1] = '\0';
            strcpy(course.course_Sched, course_schedule_buff);

            printf("Course Hours: \n");
            fgets(input, STD_BUFF_SIZE, stdin);
            sscanf(input, "%d", &course.course_Hours);

            printf("Course Enrollment: \n");
            fgets(input, STD_BUFF_SIZE, stdin);
            sscanf(input, "%d", &course.course_Size);

            fseek(fp, course_num * sizeof(Course), SEEK_SET);

            if (fseek(fp, course_num * sizeof(Course), SEEK_SET) != 0)
            {
                printf("Error seeking file");
                return 1;
            }
            if (strcmp(course.course_Name, "") == 0)
            {
                printf("ERROR: Course already exists\n");
                break;
            }
            if (fwrite(&course, sizeof(Course), 1L, fp) != 1L)
            {
                printf("ERROR: Problem writing to file");
                return 1;
            }
            printf("Success\n");

            break;
        case 'U':
        case 'u':
            printf("Course number: \n");
            fgets(input, STD_BUFF_SIZE, stdin);
            sscanf(input, "%d", &course_num);

            fseek(fp, course_num * sizeof(Course), SEEK_SET);
            read = fread(&course, sizeof(Course), 1L, fp);

            printf("Course name: \n");
            fgets(input, 84, stdin);
            if (input[0] != '\n')
            {
                strcpy(course.course_Name, input);
                course.course_Name[strlen(course.course_Name) - 1] = 0;
            }

            printf("Course schedule: \n");
            fgets(input, 5, stdin);
            if (input[0] != '\n')
            {
                strcpy(course.course_Sched, input);
                course.course_Sched[strlen(course.course_Sched) - 1] = 0;
            }

            printf("Course hours: \n");
            fgets(input, STD_BUFF_SIZE, stdin);
            if (input[0] != '\n')
            {
                sscanf(input, "%d", &course.course_Hours);
            }

            printf("Course size: \n");
            fgets(input, STD_BUFF_SIZE, stdin);
            if (input[0] != '\n')
            {
                sscanf(input, "%d", &course.course_Size);
            }

            if (!read || course.course_Hours == 0)
            {
                fprintf(stderr, "ERROR: course does not exist\n");
            }

            fseek(fp, course_num * sizeof(Course), SEEK_SET);

            if (fwrite(&course, sizeof(Course), 1L, fp) != 1)
            {
                fprintf(stderr, "ERROR: fwrite failed in update\n");
                return;
            }
            break;
        case 'R':
        case 'r':
            printf("Course number: \n");
            fgets(course_number_buff, STD_BUFF_SIZE, stdin);
            course_num = (int)strtol(course_number_buff, NULL, 10);

            if (fseek(fp, course_num * sizeof(Course), SEEK_SET) != 0)
            {
                printf("Error seeking file\n");
                return 1;
            }
            if (fread(&temp, sizeof(Course), 1L, fp) == 0)
            {
                printf("ERROR: File not read\n");
                return 1;
            }

            if (temp.course_Hours != 0)
            {
                printf("Course number: %d\n", course_num);
                printf("Course name: %s\n", temp.course_Name);
                printf("Scheduled days: %s\n", temp.course_Sched);
                printf("Credit hours: %u\n", temp.course_Hours);
                printf("Enrolled students: %u\n", temp.course_Size);
            }
            else if (temp.course_Hours == 0)
            {
                printf("ERROR: Course not found\n");
            }
            break;

        case 'D':
        case 'd':
            printf("Enter a course number: \n");
            fgets(input, STD_BUFF_SIZE, stdin);
            sscanf(input, "%d", &course_num);

            seek = fseek(fp, course_num * sizeof(Course), SEEK_SET);

            if (seek != 0 || fread(&course, sizeof(Course), 1, fp) == 0)
            {
                fprintf(stderr, "ERROR: course does not exist\n");
                return 1;
            }

            course.course_Hours = 0;

            seek = fseek(fp, course_num * sizeof(Course), SEEK_SET);

            if (seek != 0 || fwrite(&course, sizeof(Course), 1, fp) != 1)
            {
                fprintf(stderr, "ERROR: Write failed to delete\n");
                return 1;
            }
            printf("Course number %d was successfully deleted\n", course_num);
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (1);
    fclose(fp);
    return 0;
    // use fgets printf strcmp fseek fwrite
}