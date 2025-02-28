#include <stdio.h>

#define MAX_STUDENTS 100

typedef struct
{
    char name[50];
    float gpa;
} Student;



int main() {
    Student students[100];

    int count = 0;


    while (scanf("%s", students[count].name) != EOF) //prompt user, end on EOF
    {
        scanf("%f", &students[count].gpa);
       
        count++;
    }



    for (int i = 0; i < count; i++) //Print students with 3.0 gpa
    {
        if (students[i].gpa > 3.0)
        {
            printf("%s\n", students[i].name);
        }
    }

    return 0;

}