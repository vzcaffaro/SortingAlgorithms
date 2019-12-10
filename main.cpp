#include "fileReader.h"
#include <iostream>
#include <fstream>//allows file I/O
#include <cstdlib>//includes rand()

using namespace std;



int main(int argc, char** argv)
{
    int lines;//stores number of lines for processing
    float lower, upper; //lower and upper bounds
    char input;
    string file_arg;


    cout<<"Would you like to read from a file or randomly generate numbers for sorting? Enter 'r' for reading a file in or 'g' to generate a file."<<endl;
    cin>>input;
    input = toupper(input);
    while(input != 'R' && input != 'G')
    {
        cout<<"That is not a valid entry. Please enter 'r' to read in a file in or 'g' to generate a file."<<endl;
        cin>>input;
        input = toupper(input);
    }

    if(input == 'R')
    {
        cout<<"Please enter the name of the file you would like to read. "<<endl;
        cin>>file_arg;
    }
    else
    {
        cout<<"How many items would you like the program to sort?"<<endl;
        cin>>lines;
        cout<<"Enter the lower bound for number generation. "<<endl;
        cin>>lower;
        cout<<"Enter the upper bound for number generation. "<<endl;
        cin>>upper;

        ofstream outf;
        outf.open("Unordered.txt");

        srand(time(NULL));
        outf<<lines<<endl;
        for(int i = 0; i<lines; i++)
        {
            float random = ((float)rand()) / (float) RAND_MAX; //generates a random float from 0 to 1
            float num = random * (upper-lower) + lower; //multiplies random number by range and adds lower bound
            outf<<num<<endl;
        }

        outf.close();

        file_arg = "Unordered.txt";
    }



    fileReader fr(lines,file_arg);//handles most of the code in the constructor of fileReader

}
