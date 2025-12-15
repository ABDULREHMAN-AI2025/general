#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

typedef struct
{
    char name[100];
    int ID;
} student;

typedef struct
{
    char courseName[100];
    char courseCode[10];
    int noOfStudents;
    int noOfAssesments;

    student *studentList;
    float **grid;
    char **assignmentName;

} course;

void print_results(course c)
{
    printf("\n=========================================================================\n");
    printf("COURSE GRADING SUMMARY: %s (%s)\n", c.courseName, c.courseCode);
    printf("=========================================================================\n");

    printf("ID\t| Student Name\t\t| ");
    for (int i = 0; i < c.noOfAssesments; i++)
    {
        printf("%-10s | ", c.assignmentName[i]);
    }
    printf("AVERAGE\n");
    printf("--------|------------------------|----------------------------------------\n");

    for (int j = 0; j < c.noOfStudents; j++)
    {
        float total = 0.0f;

        printf("%d\t| %-22s| ", c.studentList[j].ID, c.studentList[j].name);

        for (int i = 0; i < c.noOfAssesments; i++)
        {
            printf("%-10.2f | ", c.grid[i][j]);
            total += c.grid[i][j];
        }

        printf("%.2f\n", total / c.noOfAssesments);
    }

    printf("=========================================================================\n");
}

int main()
{
    course c;
    int i, j;

    printf("Enter number of students: ");
    scanf("%d", &c.noOfStudents);

    printf("Enter number of assessments: ");
    scanf("%d", &c.noOfAssesments);
    clear_input_buffer();

    c.studentList = malloc(c.noOfStudents * sizeof(student));
    if (!c.studentList) return 1;

    c.grid = malloc(c.noOfAssesments * sizeof(float *));
    if (!c.grid) return 1;

    for (i = 0; i < c.noOfAssesments; i++)
    {
        c.grid[i] = malloc(c.noOfStudents * sizeof(float));
        if (!c.grid[i]) return 1;
    }

    c.assignmentName = malloc(c.noOfAssesments * sizeof(char *));
    if (!c.assignmentName) return 1;

    for (i = 0; i < c.noOfAssesments; i++)
    {
        c.assignmentName[i] = malloc(50);
        if (!c.assignmentName[i]) return 1;
    }

    printf("\nEnter course name: ");
    fgets(c.courseName, sizeof(c.courseName), stdin);
    c.courseName[strcspn(c.courseName, "\n")] = '\0';

    printf("Enter course code: ");
    scanf("%9s", c.courseCode);
    clear_input_buffer();

    for (i = 0; i < c.noOfAssesments; i++)
    {
        printf("Enter name of assignment %d: ", i + 1);
        fgets(c.assignmentName[i], 50, stdin);
        c.assignmentName[i][strcspn(c.assignmentName[i], "\n")] = '\0';
    }

    for (i = 0; i < c.noOfStudents; i++)
    {
        printf("\nStudent %d ID: ", i + 1);
        scanf("%d", &c.studentList[i].ID);
        clear_input_buffer();

        printf("Student %d Name: ", i + 1);
        fgets(c.studentList[i].name, sizeof(c.studentList[i].name), stdin);
        c.studentList[i].name[strcspn(c.studentList[i].name, "\n")] = '\0';
    }

    for (i = 0; i < c.noOfAssesments; i++)
    {
        printf("\nEntering marks for %s\n", c.assignmentName[i]);

        for (j = 0; j < c.noOfStudents; j++)
        {
            printf("Student %d: ", c.studentList[j].ID);
            scanf("%f", &c.grid[i][j]);
        }
        clear_input_buffer();
    }

    print_results(c);

    for (i = 0; i < c.noOfAssesments; i++)
    {
        free(c.assignmentName[i]);
        free(c.grid[i]);
    }

    free(c.assignmentName);
    free(c.grid);
    free(c.studentList);

    return 0;
}
