#include <iomanip>
#include <iostream>

using namespace std;

void ReverseIt(char* o, char* r);

int main()
{
    char original[] = "Conan The Barbarian\0";
    char reversed[100];

    ReverseIt(original, reversed);

    cout << original << " reversed is " << reversed << endl;
}

void ReverseIt(char* o, char* r)
{
    int space1 = 0;
    int space2 = 0;
    int index = 0;
    char* temp = o;
    char* temp2 = r;

    //index the spaces
    while (*temp != '\0') 
    {
        if (*temp == ' ' && space1 == 0)
        {
            space1 = index;
        }
        else if (*temp == ' ')
        {
            space2 = index;
        }

        temp++;
        index++;
    }

    //set temp to last part of name
    temp = &o[space2 + 1];

    //copy last part of o to r
    for (int i = 1; i < index - space2; i++)
    {
        *temp2 = *temp;
        temp++;
        temp2++;
    }

    //format output
    *temp2 = ',';
    temp2++;
    *temp2 = ' ';
    temp2++;

    //reset iterator
    temp = o;

    //copy the rest of o to r
    for (int i = 1; i <= space2; i++)
    {
        *temp2 = *temp;
        temp++;
        temp2++;
    }

    //place null terminator
    *temp2 = '\0';
}