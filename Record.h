
#ifndef FILEIO_RECORD_H
#define FILEIO_RECORD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Record {
public:
    Record(string="", unsigned int=0, string="");  //Constructor
    /* Getter functions*/
    string get_name(void);
    unsigned int get_amount(void);
    string get_date(void);

private:
    string name;
    unsigned int amount;
    string date;

};

// Utility functions
bool custom_comparison(Record, Record);
vector<unsigned int> integerize_date(string, const string&);

#endif //FILEIO_RECORD_H
