#include <iostream>
#include <fstream>

using namespace std;

class Roster 
{
public:
    void TransformData(string rawData)
    {
        // Having 5 records, we create an array of 5 to save in order the data
        string columns[5] = {"", "", "", "", ""};
        string::size_type p = 0;
        for (int i = 0; i < 5; i++) {
            string column = "";
            // removing the spaces in the data
            while(rawData[p] == ' ')
            {
                p++;
            }
            while(p < rawData.length() && rawData[p] != ' ')
            {
                column += rawData[p];
                p++;
            }
            
            columns[i] = column;
        }
        LName = columns[0];
        FName = columns[1];
        age = stoi(columns[2]);
        gender = columns[3][0];
        opinion = columns[4][0];
    }

    string LName;
    string FName;
    int age;
    char gender;  // M=Male, F=Female, N=Non Specified
    char opinion; // Y=Yes, N=No

};

int CountRecords(ifstream& records)
{
    int count = 0;
    string line = " ";

    // Going through every line to count the number of records

    while (getline(records, line)) {
        count++;
    }

    return count;
}

// returns true if the first string should be first
bool AscendingString(string firstString, string secondString)
{
    string shortString = firstString;

    if (firstString.length() > secondString.length())
    {
        shortString = secondString;
    }
    for (string::size_type i = 0; i < shortString.length(); i++) 
    {
        if (secondString[i] != firstString[i])
        {
            return firstString[i] > secondString[i];
        }
    }
    return secondString.length() > firstString.length();
}

void SortingArrayByLName(Roster array[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        for (int p = 0; p < i; p++) 
        {
            if (AscendingString(array[p].LName, array[i].LName)) 
            {
                Roster prevArray = array[i];
                array[i] = array[p];
                array[p] = prevArray;
            }
        }        
    }
}

void PrintRecords(Roster array[], int size) 
{
    cout << "   The Great Titanic Controversy Survey" << endl;
    cout << "Last Name\tFirst Name\tAge\t\tGender\t\tYes/No" << endl;
    cout << "---------\t---------\t---------\t---------\t---------" << endl;

    for (int i = 0; i < size; i++)
    {
        while (array[i].LName.length() < 10) {
            array[i].LName += " ";
        }
        while (array[i].FName.length() < 10) {
            array[i].FName += " ";
        }

        cout << array[i].LName << "\t" << array[i].FName << "\t" << array[i].age << "\t\t";
        
        if (array[i].gender == 'F')
        {
            cout << "Female" << "\t\t";
        }
        else 
        {
            cout << "Male" << "\t\t";
        }

        if (array[i].opinion == 'Y')
        {
            cout << "Yes" << endl;
        }
        else 
        {
            cout << "No" << endl;
        }
    }
}

void PrintSummary(Roster array[], int size)
{
    int peopleQty = size;
    float totalAge = 0;

    int males = 0;
    int females = 0;
    int nonSpecified = 0;

    int peopleYes = 0;
    int peopleNo = 0;

    for (int i = 0; i < size; i++)
    {
        totalAge += array[i].age;

        if (array[i].opinion == 'Y')
        {
            peopleYes++;
        }
        else
        {
            peopleNo++;
        }

        if (array[i].gender == 'M') 
        {
            males++;
        }
        else if (array[i].gender == 'F')
        {
            females++;
        }
        else
        {
            nonSpecified++;
        }
    }

    float averageAge = totalAge / peopleQty;

    cout << endl << "Number that took the survey: " << peopleQty << endl;
    cout << "Number of males: " << males << endl;
    cout << "Number of females: " << females << endl;
    cout << "Number of non-specific: " << nonSpecified << endl;
    cout << "Average Age: " << averageAge << endl;
    cout << "Total that said yes: " << peopleYes << endl;
    cout << "Total that said no: " << peopleNo << endl;

}


int main() 
{

    bool validFile = false;
    int totalRecords = 0;

    // Repeating the cycle until we have a valid input

    while(!validFile)
    {
        string fileName = " ";

        cout << "Enter filename to open: ";
        cin >> fileName;

        ifstream Data(fileName);
        if (Data.is_open())
        {
            validFile = true;
            totalRecords = CountRecords(Data);
            Data.clear();
            Data.seekg(0, Data.beg);

            string line = " ";
            int count = 0;

            Roster records[totalRecords];
            while (getline(Data, line)) {
                Roster singleRecord;
                singleRecord.TransformData(line);
                records[count] = singleRecord;
                count++;
            }

            SortingArrayByLName(records, totalRecords);
            PrintRecords(records, totalRecords);
            PrintSummary(records, totalRecords);

        }
        else
        {
            cout << "Invalid file!" << endl;
        }
    }

    return 0;
}
