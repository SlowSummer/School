#include <stdio.h>
#include <string.h>

int main() {

	char students[100][50];
	int count = 0;



	while (scanf("%s", students[count]) != EOF) //prompt user, end on EOF
	{
		count++;
	}

	for (int i = 0; i < count - 1; i++) //bubble sort alphabetically
	{
		for (int j = i + 1; j < count; j++)
		{
			if (strcmp(students[i], students[j]) > 0)
			{
				char temp[50];
				strcpy(temp, students[i]);
				strcpy(students[i], students[j]);
				strcpy(students[j], temp);
			}
		}
	}

	printf("\nSorted names:\n");

	for (int i = 0; i < count; i++)
	{
		printf("%s\n", students[i]);
	}


	return 0;
}