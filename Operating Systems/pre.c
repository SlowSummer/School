#include <stdio.h>

typedef struct
{
    char name[50];
    float gpa;
} Student;



int main() {
    Student students[100];

    int count = 0;
    //float gpa;

    printf("Enter student names and GPAs, Ctrl-D to stop: \n");

    while (scanf("%s, %f", students[count].name, students[count].gpa) != EOF)
    {
        count++;
    }

    printf("\nStudents with GPAs > 3.0: \n");

    for (int i = 0; i < count; i++)
    {
        if (students[i].gpa > 3.0)
        {
            printf("%s\n", students[i].name);
        }
    }

    return 0;

}