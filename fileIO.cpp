//Required header files

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
#include "Record.h"

using namespace std;

vector<unsigned int> integerize_date(string, const string &);

bool custom_comparison(Record, Record);

int main() {
    std::ifstream inFile("donations-raw.csv");

    list<Record> myrecords;     // STL List
    if (!inFile.is_open()) {
        cout << "\n Error! Couldn't open file donations-raw.csv ";
        exit(1);
    } else
        cout << "\n Processing donations-raw.csv ...\n";
    string str;
    getline(inFile, str); // to skip the first line
    while (getline(inFile, str)) {
        string name, date, tempAmount;
        unsigned int amount;
        istringstream currentLine(str);  // using stringstream to separately parse each line
        getline(currentLine, name, ','); //read line delimited by ,
        getline(currentLine, tempAmount, ',');
        amount = stoi(tempAmount);                  //convert string to integer
        getline(currentLine, date, '\r');
        myrecords.push_back(*new Record(name, amount, date)); // add a new record to list myrecords
    }

    inFile.close();
    myrecords.sort(custom_comparison);

    ofstream outFile("donations-processed.csv", ios::out);  // open file for writing
    if (!outFile.is_open()) {
        cout << "\n Error creating file donations-processed.csv\n";
        exit(1);
    }
    unsigned int weekly_sum = 0;
    for (auto it = begin(myrecords); it != end(myrecords); ++it) {
        outFile << (*it).get_date() << "," << (*it).get_amount()<<","<<(*it).get_name()<<"\r\n"; /* Since the given input
 *                                                                                                  file has been generated on
 *                                                                                                  windows, it has \r\n endings.
 *                                                                                                  Thus the output file has also
 *                                                                                                  been generated for windows.
 *                                                                                                  UNIX uses \n, which can be changed here accordingly.
 *                                                                                                  */
        /*Output to console */
        cout << (*it).get_date() << "," << (*it).get_amount()<<","<<(*it).get_name()<<"\n";
        weekly_sum += (*it).get_amount();   // Retrieve each record's amount by dereferencing current iterator
        int day_of_month = integerize_date((*it).get_date(),"-")[1];
        if (day_of_month == 20 || day_of_month == 26) {
            outFile << "week " << (day_of_month == 20 ? 1 : 2) << " total: " << weekly_sum <<"\r\n";

            /* Output to console */
            cout << "week " << (day_of_month == 20 ? 1 : 2) << " total: " << weekly_sum <<"\n";
            weekly_sum = 0;
        }
    }
    outFile.close();   // close file
    cout << "\n Output successfully written to donations-processed.csv\n";
}


