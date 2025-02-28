/***************************************************
Name: Andrew Bracken 
Date: 2/13/22
Problem Number: Project 2
Hours spent solving the problem: 10
Instructor: Komogortsev, TSU
*****************************************************/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

void SplitInput(char input[], ofstream& outFile);
double FindAvgGrade(double sumGrade, double lowest);
char CalcLetterGrade(double avgGrade);
void PrintStudentIDInfo(char* firstName, char* lastName, char* studentID, ofstream& outFile);
void PrintStudentGradeInfo(double avgGrade, char letterGrade, ofstream& outFile);


int A_COUNT = 0;
int B_COUNT = 0;
int C_COUNT = 0;
int D_COUNT = 0;
int F_COUNT = 0;

int main()
{
    char input[100];

    ifstream inFile;
    ofstream outFile;

    inFile.open("student_input.dat");
    outFile.open("student_results.dat");

    //Format the header of the result file
    outFile << "Last_name";
    outFile.width(12);
    outFile << "First_name";
    outFile.width(5);
    outFile << "ID";
    outFile.width(21);
    outFile << "Average_Score";
    outFile.width(10);
    outFile << "GradeL\n";

    inFile.getline(input, 100); //Takes the entire first line as input

    while (!inFile.eof())
    {
        SplitInput(input, outFile); //Splits the first line into tokens for sorting

        inFile.getline(input, 100); //Takes the second line for sorting
    }

    outFile << "\n" << "Grade Totals:\n";
    
    if (A_COUNT > 0)
    {
        outFile << "A - " << A_COUNT << "\n";
    }
    if (B_COUNT > 0)
    {
        outFile << "B - " << B_COUNT << "\n";
    }
    if (C_COUNT > 0)
    {
        outFile << "C - " << C_COUNT << "\n";
    }
    if (D_COUNT > 0)
    {
        outFile << "D - " << D_COUNT << "\n";
    }
    if (F_COUNT > 0)
    {
        outFile << "F - " << F_COUNT << "\n";
    }

    inFile.close();
    outFile.close();
    return -1;
}

void SplitInput(char input[], ofstream& outFile)
{
    char* firstName = NULL;
    char* lastName = NULL;
    char* studentID = NULL;
    char* temp;
    char letterGrade;

    double numGrade;
    double sumGrades = 0.0f;
    double lowest = 100.0f;
    double avgGrade = 0.0f;
    int length;

    int entryCount = 0; //Used to check that 6 grades are present

    length = strlen(input);
    input[length] = '\0';

    temp = strtok(input, " ");

 
    while (temp != NULL)
    {

        if (entryCount == 0)
        {
            firstName = temp;
         
        }
        if (entryCount == 1)
        {
            lastName = temp;
        }

        if (entryCount == 2)
        {
            studentID = temp;
        }

        if (entryCount > 2)
        {
            numGrade = atof(temp);

            if (numGrade < 0)
            {
                outFile << "ERROR: Negative grade value found";
                exit(0);
            }

            if (numGrade < lowest) //Finds the lowest grade of the student
            {
                lowest = numGrade;
            }

            sumGrades += numGrade;
        }

        temp = strtok(NULL, " ");

        entryCount++;
    }

    if (entryCount < 9) //Checks for the proper amount of grades per student
    {

        outFile << "ERROR: Improper number of test grades found";
        exit(0);
    }

    avgGrade = FindAvgGrade(sumGrades, lowest); //Finds the average grade after dropping the lowest


    letterGrade = CalcLetterGrade(avgGrade);

    PrintStudentIDInfo(firstName, lastName, studentID, outFile);

    PrintStudentGradeInfo(avgGrade, letterGrade, outFile);
}

double FindAvgGrade(double sumGrades, double lowest)
{
    double avgGrade = 0.0;

    avgGrade = (sumGrades - lowest) / 5.0;

    return avgGrade;
}

char CalcLetterGrade(double avgGrade)
{
    char letterGrade;

    if (avgGrade >= 89.5)
    {
        letterGrade = 'A';
        A_COUNT++;
    }
    else if (avgGrade >= 79.5)
    {
        letterGrade = 'B';
        B_COUNT++;
    }
    else if (avgGrade >= 69.5)
    {
        letterGrade = 'C';
        C_COUNT++;
    }
    else if (avgGrade >= 59.5)
    {
        letterGrade = 'D';
        D_COUNT++;
    }
    else
    {
        letterGrade = 'F';
        F_COUNT++;
    }

    return letterGrade;
}

void PrintStudentIDInfo(char* firstName, char* lastName, char* studentID, ofstream& outFile)
{
    int lnLength;
    int fnLength;
    int fnWidth;
    int idWidth;

    //Calculates the length of each name to format output properly
    lnLength = strlen(lastName);
    fnLength = strlen(firstName);

    fnWidth = (11 - lnLength) + fnLength;

    idWidth = (13 - fnLength) + 6;

    outFile << lastName;

    outFile.width(fnWidth);
    outFile << firstName;

    outFile.width(idWidth);
    outFile<< studentID;
}

void PrintStudentGradeInfo(double avgGrade, char letterGrade, ofstream& outFile)
{
    int gradeLength = 4;
    int gradeWidth;
    int lgWidth;
    
    gradeWidth = 4 + gradeLength;
    lgWidth = 17 - gradeLength;
    
    outFile.width(gradeWidth);
    outFile << avgGrade;

    outFile.width(lgWidth);
    outFile << letterGrade << '\n';
}
