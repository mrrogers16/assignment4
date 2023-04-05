#include <stdio.h>
#include <stdlib.h>

#define MAX_COURSE_NAME_LENGTH 83
#define COURSE_FILENAME "courses.dat"

typedef struct COURSE
{
    unsigned course_Number;
    char course_Name[MAX_COURSE_NAME_LENGTH + 1];
    char course_Sched[4];
    unsigned course_Size;
    unsigned course_Hours;
} Course;

void create_course_record(FILE *fp, Course *courses, int *num_courses)
{
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
            return;
        }
    }
    // Create new course record and write to file
    Course new_course;
    new_course.course_Number = course_number;
    strncpy(new_course.course_Name, course_name, MAX_COURSE_NAME_LENGTH);
    strncpy(new_course.course_Sched, course_sched, 4);
    new_course.course_Hours = course_hours;
    new_course.course_Size = course_enrollment;
    fwrite(&new_course, sizeof(Course), 1, fp);

    // Update courses array and num_courses
    courses[*num_courses] = new_course;
    (*num_courses)++;

    printf("New course record created and added to file.\n");
}

void update_course_record(Course *courses, int num_courses, FILE *fp)
{
    int course_num, i;
    char course_name[MAX_COURSE_NAME_LENGTH + 1];
    char course_sched[4];
    unsigned course_hours = 0, course_enrollment = 0;

    printf("Enter course number to update: ");
    scanf("%d", &course_num);

    for (i = 0; i < num_courses; i++)
    {
        if (courses[i].course_Number == course_num)
        {
            printf("Enter course name (press enter to keep current value '%s'): ", courses[i].course_Name);
            getchar();
            fgets(course_name, MAX_COURSE_NAME_LENGTH + 1, stdin);
            if (course_name[0] != '\n') // if the user entered a non-empty string
            {
                strncpy(courses[i].course_Name, course_name, MAX_COURSE_NAME_LENGTH);
                courses[i].course_Name[strlen(course_name) - 1] = '\0'; // remove trailing newline character
            }

            printf("Enter course schedule (MWF or TR, press enter to keep current value '%s'): ", courses[i].course_Sched);
            scanf("%s", course_sched);
            if (course_sched[0] != '\0') // if the user entered a non-empty string
            {
                strncpy(courses[i].course_Sched, course_sched, 4);
            }

            printf("Enter course credit hours (press enter to keep current value %u): ", courses[i].course_Hours);
            char ch = getchar();
            if (ch != '\n') // if the user entered a non-empty string
            {
                scanf("%u", &course_hours);
                courses[i].course_Hours = course_hours;
            }

            printf("Enter course enrollment (press enter to keep current value %u): ", courses[i].course_Size);
            ch = getchar();
            if (ch != '\n') // if the user entered a non-empty string
            {
                scanf("%u", &course_enrollment);
                courses[i].course_Size = course_enrollment;
            }

            // Write updated course record to file
            fseek(fp, i * sizeof(Course), SEEK_SET); // move to the beginning of the course record
            fwrite(&courses[i], sizeof(Course), 1, fp);
            printf("Course record updated.\n");
            return;
        }
    }

    printf("ERROR: course not found\n");
}

void read_course_record(FILE *fp, Course *courses, int num_courses)
{
    int course_number;
    int i;
    printf("Enter a CS course number: ");
    scanf("%d", &course_number);
    while (fp != NULL)
    {
        fseek(fp, 0, SEEK_SET); // move to the beginning of the file
        Course buff;

        while (fread(&buff, sizeof(Course), 1, fp) == 1)
        {
            if (buff.course_Number == course_number)
            {
                printf("Course number: %d\n", i);
                printf("Course name: %s\n", buff.course_Name);
                printf("Scheduled days: %s\n", buff.course_Sched);
                printf("Credit hours: %u\n", buff.course_Hours);
                printf("Enrolled students: %u\n", buff.course_Size);
                return;
            }
            i++;
        }

        printf("ERROR: course not found\n");
    }
}

Course *read_course_file(FILE *fp, int *num_courses)
{
    if (!fp)
    {
        printf("Error opening file.\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_SET); // move to the beginning of the file
    int count = 0;
    Course buff = {0};
    while (fread(&buff, sizeof(Course), 1, fp) == 1)
    {
        count++;
    }

    *num_courses = count;
    Course *courses = malloc(*num_courses * sizeof(Course));
    fseek(fp, 0, SEEK_SET); // move to the beginning of the file again
    fread(courses, sizeof(Course), *num_courses, fp);

    return courses;
}

void delete_course_record(Course *courses, int *num_courses)
{
    int course_num, i;

    printf("Enter course number to delete: ");
    scanf("%d", &course_num);

    for (i = 0; i < *num_courses; i++)
    {
        if (courses[i].course_Number == course_num)
        {
            // Move the last course to the index being deleted
            courses[i] = courses[*num_courses - 1];
            (*num_courses)--; // Reduce the number of courses

            // Update the courses.dat file
            FILE *fp = fopen(COURSE_FILENAME, "wb"); // Open in binary write mode
            if (!fp)
            {
                printf("Error opening file.\n");
                return;
            }
            fwrite(courses, sizeof(Course), *num_courses, fp);
            fclose(fp);

            printf("Course record deleted.\n");
            return;
        }
    }

    printf("ERROR: course not found\n");
}

int main(int argc, char *argv[])
{

    Course *courses;
    int num_courses;
    char menu_option;
    num_courses = 0;

    FILE *fp = fopen(argv[1], "rb");
    if (argc < 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    // num_courses = sizeof(*courses) / sizeof(Course);
    courses = read_course_file(&num_courses);

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
