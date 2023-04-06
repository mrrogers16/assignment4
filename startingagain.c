#include <stdio.h>
#include <stdlib.h>
#define MAX_BUFF_SIZE 4096
#define MAX_COURSE_NAME_LENGTH 83
#define MAX_COURSES 1024
#define COURSE_FILENAME "courses.dat"

typedef struct COURSE
{
    unsigned course_Number;
    char course_Name[MAX_COURSE_NAME_LENGTH + 1];
    char course_Sched[4];
    unsigned course_Size;
    unsigned course_Hours;
} Course;

Course *read_courses(FILE *fp, int *num_courses)
{
    // Allocate memory for the Course array
    Course *courses = malloc(sizeof(Course) * (*num_courses));
    if (courses == NULL)
    {
        printf("Failed to allocate memory for courses\n");
        return NULL;
    }

    // Read the course data from the file and populate the Course array
    int i = 0;
    char buff[MAX_BUFF_SIZE];
    while (fgets(buff, sizeof(buff), fp))
    {
        if (sscanf(buff, "%u %83s %3s %u %u", &courses[i].course_Number, courses[i].course_Name, courses[i].course_Sched, &courses[i].course_Size, &courses[i].course_Hours) == 5)
        {
            i++;
        }
        else
        {
            printf("Error reading course data for course %d\n", i + 1);
        }
        if (i == num_courses)
        {
            break;
        }
    }

    // Set the number of courses if num_courses is not NULL
    if (num_courses != NULL)
    {
        num_courses = i;
    }

    fclose(fp);
    return courses;
}

int main()
{

    Course *courses;
    int num_courses = 0;
    char menu_option;
    int i = 0;
    int course_num;
    char course_name[MAX_COURSE_NAME_LENGTH + 1];
    char course_sched[4];
    unsigned course_hours, course_enrollment;
    char buff[MAX_BUFF_SIZE];

    FILE *fp;
    fp = fopen(COURSE_FILENAME, "rb");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Calculate the number of courses in the file

    while (fgets(buff, sizeof(buff), fp))
    {
        int course_num;
        char course_name[MAX_COURSE_NAME_LENGTH + 1];
        char course_sched[4];
        unsigned course_hours, course_enrollment;
        if (sscanf(buff, "%u %83s %3s %u %u", &course_num, course_name, course_sched, &course_enrollment, &course_hours) == 5)
        {
            num_courses++;
        }
        else
        {
            printf("Error reading course data for line %d\n", num_courses + 1);
        }
    }
    courses = read_courses(fp, num_courses);

    for (i = 0; i < num_courses; i++)
    {
        printf("Course Number: %u\n", courses[i].course_Number);
        printf("Course Name: %s\n", courses[i].course_Name);
        printf("Course Schedule: %s\n", courses[i].course_Sched);
        printf("Course Enrollment: %u\n", courses[i].course_Size);
        printf("Course Hours: %u\n", courses[i].course_Hours);
        printf("\n");
    }
    return 0;
}
//     // Allocate memory for the courses array
//     courses = malloc(num_courses * sizeof(Course));
//     if (courses == NULL)
//     {
//         printf("Failed to allocate memory\n");
//         return 1;
//     }

//     // Reset the standard input stream so that we can read from it again
//     rewind(stdin);

//     // Read in the course data from standard input and store it in the courses array
//     for (i = 0; i < num_courses; i++)
//     {
//         fgets(buff, sizeof(buff), stdin);
//         if (sscanf(buff, "%u %83s %3s %u %u", &course_num, course_name, course_sched, &course_enrollment, &course_hours) == 5)
//         {
//             courses[i].course_Number = course_num;
//             courses[i].course_Size = course_enrollment;
//             courses[i].course_Hours = course_hours;
//             strncpy(courses[i].course_Name, course_name, MAX_COURSE_NAME_LENGTH);
//             strncpy(courses[i].course_Sched, course_sched, 4);
//         }
//         else
//         {
//             printf("2Error reading course data for course %d\n", i + 1);
//             break;
//         }
//     }

//     // Print out all the courses
//     for (i = 0; i < num_courses; i++)
//     {
//         printf("Course Number: %u\n", courses[i].course_Number);
//         printf("Course Name: %s\n", courses[i].course_Name);
//         printf("Course Schedule: %s\n", courses[i].course_Sched);
//         printf("Course Enrollment: %u\n", courses[i].course_Size);
//         printf("Course Hours: %u\n", courses[i].course_Hours);
//         printf("\n");
//     }

//     // Free the memory allocated for the courses array

//     free(courses);

//     return 0;
// }
