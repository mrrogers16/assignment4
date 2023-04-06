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
    

    // ensure cursor is at beginning of file
    //fseek(fp, 0, SEEK_SET);
    Course buff = {0};
//while (fgets buff, 1024, stdin)
//     while (fread(&buff, sizeof(Course), 1, fp) == 1) // Determine number of courses
//     {
//         num_courses++;
//     }
//     courses = malloc(num_courses * sizeof(Course));
//     fseek(fp, 0, SEEK_SET); // move cursor to beginning of file again
//     fread(courses, sizeof(Course), num_courses, fp);



//     printf("Enter one of the following actions or press CTRL-D to exit.\n");
//     printf("C - create a new course record\n");
//     printf("U - update an existing course record\n");
//     printf("R - read an existing course record\n");
//     printf("D - delete an existing course record\n");

//     while (scanf(" %c", &menu_option) == 1)
//     {
//         switch (menu_option)
//         {
//         case 'C':
//         case 'c':
//         {
//             printf("Enter course number: ");
//             scanf("%d", &course_num);
//             printf("Enter course name: ");
//             getchar(); // handle last newline character
//             fgets(course_name, MAX_COURSE_NAME_LENGTH + 1, stdin);
//             printf("Enter course schedule (MWF or TR): ");
//             scanf("%s", course_sched);
//             printf("Enter course credit hours: ");
//             scanf("%u", &course_hours);
//             printf("Enter course enrollment: ");
//             scanf("%u", &course_enrollment);

//             // Check if course already exists
//             int i;
//             for (i = 0; i < num_courses; i++)
//             {
//                 if (courses[i].course_Number == course_num)
//                 {
//                     printf("ERROR: course already exists\n");
//                     break;
//                 }
//             }
//             // Create new course record and write to file
//             Course new_course;
//             new_course.course_Number = course_num;
//             strncpy(new_course.course_Name, course_name, MAX_COURSE_NAME_LENGTH);
//             strncpy(new_course.course_Sched, course_sched, 4);
//             new_course.course_Hours = course_hours;
//             new_course.course_Size = course_enrollment;
//             fwrite(&new_course, sizeof(Course), 1, fp);

//             // Update courses array and num_courses
//             courses[num_courses] = new_course;
//             (num_courses)++;

//             printf("New course record created and added to file.\n");
//         }
//         break;

//         case 'R':
//         case 'r':
//         {
//             int course_number;
//             int i = 0;
//             printf("Enter a CS course number: ");
//             scanf("%d", &course_number); // User input

//             fseek(fp, 0, SEEK_SET); // move cursor to beginning of file
//             while (!feof(fp))
//             {
//                 Course buff;

//                 if (fread(&buff, sizeof(Course), 1, fp) == 1)
//                 {
//                     if (buff.course_Number == course_number)
//                     {
//                         printf("Course number: %d\n", i);
//                         printf("Course name: %s\n", buff.course_Name);
//                         printf("Scheduled days: %s\n", buff.course_Sched);
//                         printf("Credit hours: %u\n", buff.course_Hours);
//                         printf("Enrolled students: %u\n", buff.course_Size);
//                     }
//                     i++;
//                 }
//             }
//             printf("ERROR: course not found\n");
//         }
//         break;
//         case 'U':
//         case 'u':
//         {
//             printf("Enter course number to update: ");
//             scanf("%d", &course_num);

//             for (i = 0; i < num_courses; i++)
//             {
//                 if (courses[i].course_Number == course_num)
//                 {
//                     printf("Enter course name (press enter to keep current value '%s'): ", courses[i].course_Name);
//                     getchar();
//                     fgets(course_name, MAX_COURSE_NAME_LENGTH + 1, stdin);
//                     if (course_name[0] != '\n') // if the user entered a non-empty string
//                     {
//                         strncpy(courses[i].course_Name, course_name, MAX_COURSE_NAME_LENGTH);
//                         courses[i].course_Name[strlen(course_name) - 1] = '\0'; // remove trailing newline character
//                     }

//                     printf("Enter course schedule (MWF or TR, press enter to keep current value '%s'): ", courses[i].course_Sched);
//                     scanf("%s", course_sched);
//                     if (course_sched[0] != '\0') // if the user entered a non-empty string
//                     {
//                         strncpy(courses[i].course_Sched, course_sched, 4);
//                     }

//                     printf("Enter course credit hours (press enter to keep current value %u): ", courses[i].course_Hours);
//                     char ch = getchar();
//                     if (ch != '\n') // if the user entered a non-empty string
//                     {
//                         scanf("%u", &course_hours);
//                         courses[i].course_Hours = course_hours;
//                     }

//                     printf("Enter course enrollment (press enter to keep current value %u): ", courses[i].course_Size);
//                     ch = getchar();
//                     if (ch != '\n') // if the user entered a non-empty string
//                     {
//                         scanf("%u", &course_enrollment);
//                         courses[i].course_Size = course_enrollment;
//                     }

//                     // Write updated course record to file
//                     fseek(fp, i * sizeof(Course), SEEK_SET); // move to the beginning of the course record
//                     fwrite(&courses[i], sizeof(Course), 1, fp);
//                     printf("Course record updated.\n");
//                 }
//             }

//             printf("ERROR: course not found\n");
//         }
//         break;
//         case 'D':
//         case 'd':
//         {
//             // delete_course_record(courses, &num_courses);
//             int course_num;

//             printf("Enter course number to delete: ");
//             scanf("%d", &course_num);

//             for (i = 0; i < num_courses; i++)
//             {
//                 if (courses[i].course_Number == course_num)
//                 {
//                     // Move the last course to the index being deleted
//                     courses[i] = courses[num_courses - 1];
//                     (num_courses)--; // Reduce the number of courses

//                     // Update the courses.dat file
//                     fseek(fp, 0, SEEK_SET); // Move the file pointer to the beginning of the file
//                     fwrite(courses, sizeof(Course), num_courses, fp);
//                     printf("Course record deleted.\n");
//                 }
//             }

//             printf("ERROR: course not found\n");
//             // Ensure file is up to date even if course not found
//             fseek(fp, 0, SEEK_SET);
//             fwrite(courses, sizeof(Course), num_courses, fp);
//         }
//         break;

//         default:
//             printf("Invalid option selected.\n");
//             break;
//         }

//         printf("Enter one of the following actions or press CTRL-D to exit.\n");
//         printf("C - create a new course record\n");
//         printf("U - update an existing course record\n");
//         printf("R - read an existing course record\n");
//         printf("D - delete an existing course record\n");
//     }
    
     return 0;
// }