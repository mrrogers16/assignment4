#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_BUFF_SIZE 100
#define MAX_BUFF_SIZE 4096
#define MAX_COURSE_NAME_LENGTH 83
#define MAX_COURSES 1024
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
            printf("Course number: ");
            fgets(course_number_buff, STD_BUFF_SIZE, stdin);
            course_num = (int)strtol(course_number_buff, NULL, 10);

            printf("Course Name: ");
            fgets(course_name_buff, STD_BUFF_SIZE, stdin);
            course.course_Name[strlen(course.course_Name) - 1] = '\0';

            printf("Course Schedule: ");
            fgets(course_schedule_buff, STD_BUFF_SIZE, stdin);
            course.course_Sched[strlen(course.course_Sched) - 1] = '\0';

            printf("Course Hours: ");
            fgets(course_hours_buff, STD_BUFF_SIZE, stdin);
            course.course_Hours = (int)strtol(course_hours, NULL, 10);

            printf("Course Enrollment: ");
            fgets(course_size_buff, STD_BUFF_SIZE, stdin);
            course.course_Size = (int)strtol(course_size_buff, NULL, 10);

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
            }
            printf("Success\n");

            break;
        case 'R':
        case 'r':
            printf("Course number: ");
            fgets(course_number_buff, STD_BUFF_SIZE, stdin);
            course_num = (int)strtol(course_number_buff, NULL, 10);

            if (fseek(fp, course_num * sizeof(Course), SEEK_SET) != 0)
            {
                printf("Error seeking file");
                return 1;
            }
            if (fread(&temp, sizeof(Course), 1L, fp) == 0)
            {
                printf("ERROR: File not read");
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
        case 'U':
        case 'u':
            printf("Course number: ");
            fgets(course_number_buff, STD_BUFF_SIZE, stdin);
            course_num = (int)strtol(course_number_buff, NULL, 10);

            printf("Course Name: ");
            fgets(course_name_buff, STD_BUFF_SIZE, stdin);
            course.course_Name[strlen(course.course_Name) - 1] = '\0';

            printf("Course Schedule: ");
            fgets(course_schedule_buff, STD_BUFF_SIZE, stdin);
            course.course_Sched[strlen(course.course_Sched) - 1] = '\0';

            printf("Course Hours: ");
            fgets(course_hours_buff, STD_BUFF_SIZE, stdin);
            course.course_Hours = (int)strtol(course_hours, NULL, 10);

            printf("Course Enrollment: ");
            fgets(course_size_buff, STD_BUFF_SIZE, stdin);
            course.course_Size = (int)strtol(course_size_buff, NULL, 10);
            

            if (fseek(fp, course_num * sizeof(Course), SEEK_SET) != 0)
            {
                printf("Error seeking file\n");
                return 1;
            }
            fread(&temp, sizeof(Course), 1L, fp);
            if (temp.course_Hours == 0)
            {
                printf("ERROR: Course not found\n");
            }
            if (course_name_buff == '\0')
            {
                strcpy(course.course_Name, temp.course_Name);
            }
            if (course_schedule_buff == '\0')
            {
                strcpy(course.course_Sched, temp.course_Sched);
            }
            if (course_hours == '\0')
            {
                course.course_Hours = temp.course_Hours;
            }
            if (course_size == '\0')
            {
                course.course_Size = temp.course_Size;
            }

            if (fread(&temp, sizeof(Course), 1L, fp) == 1L)
            {
                printf("ERROR: File not read");
                return 1;
            }
            break;

        case 'D':
        case 'd':
            printf("Enter a course number: ");
            fgets(input, STD_BUFF_SIZE, stdin);
            sscanf(input, "%d", &course_num);
            if (fseek(fp, course_num * sizeof(Course), SEEK_SET) != 0)
            {
                printf("Error seeking file\n");
                return 1;
            }
            course_read = fread(&temp, sizeof(Course), 1L, fp);

            if (temp.course_Hours == 0)
            {
                printf("ERROR: Course not found\n");
            }
            memset(&temp, 0, sizeof(Course));
            fseek(fp, course_num * sizeof(Course), SEEK_SET);
            fwrite(&temp, sizeof(Course), 1L, fp);
            printf("%d, was successfully deleted\n", course_num);
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