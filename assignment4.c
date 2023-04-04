#include <stdio.h>
#include <stdlib.h>

#define MAX_COURSE_NAME_LENGTH 83
#define COURSE_FILENAME "courses.dat"

typedef struct
{
    char course_Name[MAX_COURSE_NAME_LENGTH + 1];
    char course_Sched[4];
    unsigned course_Size;
    unsigned course_Hours;
} COURSE;

void create_course_record(COURSE *courses, int *num_courses)
{
    FILE *fp = fopen(COURSE_FILENAME, "ab"); //open in binary append mode
    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }
}

void update_course_record(COURSE *courses, int num_courses)
{
    // Handle update course record option
}

void read_course_record(COURSE *courses, int num_courses)
{
    // Handle read course record option
}

void delete_course_record(COURSE *courses, int *num_courses)
{
    // Handle delete course record option
}

int main()
{

    COURSE *courses;
    int num_courses;
    char menu_option;

    courses = read_course_file();
    num_courses = sizeof(*courses) / sizeof(COURSE);

    printf("Enter one of the following actions or press CTRL-D to exit.\n");
    printf("C - create a new course record\n");
    printf("U - update an existing course record\n");
    printf("R - read an existing course record\n");
    printf("D - delete an existing course record\n");

    while (scanf(" %c", &menu_option) == 1)
    {
        switch (menu_option)
        {
        case 'C':
        case 'c':
            create_course_record(courses, &num_courses);
            break;
        case 'U':
        case 'u':
            update_course_record(courses, num_courses);
            break;
        case 'R':
        case 'r':
            read_course_record(courses, num_courses);
            break;
        case 'D':
        case 'd':
            delete_course_record(courses, &num_courses);
            break;
        default:
            printf("Invalid option selected.\n");
            break;
        }

        printf("Enter one of the following actions or press CTRL-D to exit.\n");
        printf("C - create a new course record\n");
        printf("U - update an existing course record\n");
        printf("R - read an existing course record\n");
        printf("D - delete an existing course record\n");
    }

    return 0;
}
