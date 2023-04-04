#include <stdio.h>
#include <stdlib.h>

#define MAX_COURSE_NAME_LENGTH 83
#define COURSE_FILENAME "courses.dat"

typedef struct
{
    unsigned course_Number;
    char course_Name[MAX_COURSE_NAME_LENGTH + 1];
    char course_Sched[4];
    unsigned course_Size;
    unsigned course_Hours;
} COURSE;

void create_course_record(COURSE *courses, int *num_courses)
{
    FILE *fp = fopen(COURSE_FILENAME, "ab"); // open in binary append mode
    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }

    // Get user input
    int course_number;
    char course_name[MAX_COURSE_NAME_LENGTH + 1]; //+1 for NULL terminator
    char course_sched[4];
    unsigned course_hours, course_enrollment;

    printf("Enter course number: ");
    scanf("%d", &course_number);
    printf("Enter course name: ");
    getchar(); // handle last newline character
    fgets(course_name, MAX_COURSE_NAME_LENGTH + 1, stdin);
    printf("Enter course schedule (MWF or TR): ");
    scanf("%s", course_sched);
    printf("Enter course credit hours: ");
    scanf("%u", &course_hours);
    printf("Enter course enrollment: ");
    scanf("%u", &course_enrollment);

    // Check if course already exists
    int i;
    for (i = 0; i < *num_courses; i++)
    {
        if (courses[i].course_Number == course_number)
        {
            printf("ERROR: course already exists\n");
            fclose(fp);
            return;
        }
    }
    // Create new course record and write to file
    COURSE new_course = {0};
    new_course.course_Number = course_number;
    strncpy(new_course.course_Name, course_name, MAX_COURSE_NAME_LENGTH);
    strncpy(new_course.course_Sched, course_sched, 4);
    new_course.course_Hours = course_hours;
    new_course.course_Size = course_enrollment;
    fwrite(&new_course, sizeof(COURSE), 1, fp);

    // Update courses array and num_courses
    courses[*num_courses] = new_course;
    (*num_courses)++;

    fclose(fp);
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
