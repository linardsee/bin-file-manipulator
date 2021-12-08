#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 	1000
#define LENGTH	     	64

/* GLOBALS */

typedef struct
{
	char name[LENGTH];
	int age;
	char favSubj[LENGTH];
} student_t;

student_t *students[MAX_STUDENTS]; 

int incr = 0;





/* PRIVATE FUNCTIONS */

void str_trim_lf (char* arr, int length)
{
  int i;
  for (i = 0; i < length; i++)
  { // trim \n
    if (arr[i] == '\n')
    {
      arr[i] = '\0';
      break;
    }
  }
}

void addToStruct(student_t* student)
{
	students[incr] = student;

	incr++;
}

void printAllStudents(student_t** studentsArr)
{
	// Table head
	
	printf("%-20s %-20c %-20s %-20c %-20s \n", "Name", '|', "Age", '|', "Favourite subject");
	for(int i = 0; i < incr; i++)
	{
		printf("%-20s %-20c %-20d %-20c %-20s \n", studentsArr[i]->name, '|', studentsArr[i]->age, '|', studentsArr[i]->favSubj);
	}
}

/* MAIN APPLICATION */

int main(void)
{
	char buff[LENGTH];
	int stAge;
	student_t structBuff;

	FILE *fptr;

	if((fptr = fopen("students.bin", "ab+")) == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	// Loop through file and save to application heap	
	while(!feof(fptr))
	{
		student_t *st = (student_t *)malloc(sizeof(student_t));		
		fread(st, sizeof(student_t), 1, fptr);
		if(st->age == 0) break;
		addToStruct(st);
	}

	printAllStudents(students);	
/*
	for(int i = 0; i < incr; i++)
	{
		printf("Student %d name: %s, age = %d \n", i, students[i]->name, students[i]->age);
	}
*/
	while(1)
	{
		printf("Enter students name (x to exit, p to print students): ");
		fgets(buff, LENGTH, stdin);
		str_trim_lf(buff, LENGTH);

		if(!strcmp(buff, "x"))
		{
			printf("Goodbye!\n");
			break;
		}	
	
		if(!strcmp(buff, "p"))
		{
			printAllStudents(students);
			continue;
		}	
			
		student_t *st = (student_t *)malloc(sizeof(student_t));		
		
		strcpy(st->name, buff);
		memset(buff, 0, sizeof(buff));
	
		printf("Enter students age: ");
		scanf("%d%*c", &stAge);
		st->age = stAge;
	
		printf("Enter student's favourite subject: ");
		fgets(buff, LENGTH, stdin);
		str_trim_lf(buff, LENGTH);
		strcpy(st->favSubj, buff);
		memset(buff, 0, sizeof(buff));

		addToStruct(st);

		fwrite(st, sizeof(student_t), 1, fptr);
	}

	fclose(fptr);
	return 0;
}


// commments 1