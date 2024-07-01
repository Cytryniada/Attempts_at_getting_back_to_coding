
#include <iostream>
#include <array>
#include <string>

#pragma warning(push)
#pragma warning(disable:4244)

float grade_to_float(std::string gr) // converts grade in form of letter to float value
{
    float val = 0;
    if (gr.size() > 1)
    {
        if (gr[1] == '+') val = 0.3;
        else if (gr[1] == '-') val = -0.3;
    }
    switch(toupper(gr[0]))
    {
        case 'A':
            return 4.00 + val;
            break;
        case 'B':
            return 3.00 + val;
            break;
        case 'C':
            return 2.00 + val;
            break;
        case 'D':
            return 1.00 + val;
            break;
        case 'F':
            return 0 + val;
            break;
        default:
            return 0; // bad data
            break;
    }
}
int main(int argc, char* argv[])
{
    // full grade points, GPA and CGPA display

    // names of subjects cannot contain spaces
    // calculator displays weighted GPA and CGPA
    // A+ is maximum grade with the value of 4.3 and F the minimum grade with value of 0
    // input sensitive - no try-catching wrong input
    // value of - sign in grade is -0.3 and value of + sign in grade is 0.3

    int n = 0; // Number of semesters
    std::cout << "Insert number of semesters: ";
    std::cin >> n;
    while (n <= 0)
    {
        std::cout << "\nNumber cannot be lower than 1: ";
        std::cin >> n;
    } // validate number of semesters

    std::string** sem = new std::string *[n]; // stores info for each subject to display in the Summary
    int* val = new int[n]; // stores amount of subjects in each semester

    float GPA = 0, CGPA = 0; //GPA - temporary variable storing and displaying GPA for each semester, CGPA - variable which sums up every GPA and displays CGPA

    bool msg = true; // message about required format of input data

    for (int i = 0; i < n; i++) // data insert
    {
        int m = 0;
        std::cout << "\n\nInsert number of subjects in semester number " << i + 1 << ": ";
        std::cin >> m;
        while (m <= 0)
        {
            std::cout << "\nNumber cannot be lower than 1: ";
            std::cin >> m;
        } //validate number of subjects
        sem[i] = new std::string[m*3+1];

        if (msg) {
            std::cout << "\nSubject info must be inserted in following format: subject_info letter_grade(+-) credits. Each subject must be submitted by making new line.\n";
            msg = false;
        }
        val[i] = m;
        for (int j = 0; j < m; j++)
        {
            std::cin >> sem[i][j*3+1] >> sem[i][j*3 + 2] >> sem[i][j*3 + 3];
        }
    }

    
    std::cout << std::endl;
    std::cout.precision(2);
    for (int i = 0; i < n; i++) //data display - SUMMARY
    {
        std::cout << "\n\nSemester " << i + 1 << ": ";
        std::cout << "\n| Subject name | Grade | Credits | Grade points |";
        int credits = 0;
        GPA = 0;
        for (int j = 0; j < val[i]; j++)
        {
            std::cout << "\n" << sem[i][j * 3 + 1] << " " << sem[i][j * 3 + 2] << " " << sem[i][j * 3 + 3] << " ";

            credits += std::stoi(sem[i][j * 3 + 3]);
            float total_c = (grade_to_float(sem[i][j * 3 + 2]) * std::stoi(sem[i][j * 3 + 3])); //stoi needed
            GPA += total_c;
            std::cout << total_c;
        }
        GPA /= credits;
        std::cout << "\n______________________\n" << "Your GPA for " << i+1 << " semester is " << GPA << " and total credit is " << credits << "\n";
        CGPA += GPA;
    }
    CGPA /= n;
    std::cout << "\n______________________\n" << "Your overall CGPA is " << CGPA;
    for (int i = 0; i < n; i++) // removal of pointers to avoid memory leak
    {
        delete []sem[i];
    }
    delete []sem;
    delete []val;
    return 0;
}
