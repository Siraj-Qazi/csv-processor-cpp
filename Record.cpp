// Implementation file

#include "Record.h"

Record::Record(string n, unsigned int a, string d) {
    name = n;
    amount = a;
    date = d;
}

string Record::get_name(void) {
    return name;
}

unsigned int Record::get_amount(void) {
    return amount;
}

string Record::get_date(void) {
    return date;
}

// Function for comparing two Record objects, to be used in list::sort()
bool custom_comparison(Record r1, Record r2) {
    vector<unsigned int> date1 = integerize_date(r1.get_date(), "-");
    vector<unsigned int> date2 = integerize_date(r2.get_date(), "-");

    if (date1[1] < date2[1])
        return true;
    else if (date1[1] == date2[1])
    {
        if (r1.get_amount() > r2.get_amount())
            return true;
        else if (r1.get_amount() == r2.get_amount())
        {
            if (r1.get_name() < r2.get_name())
                return true;
        }
    }
    return false;
}

// Function to convert a date in string format into a vector of the form [month,day,year]
vector<unsigned int> integerize_date(string date, const string &delim) {
    size_t i = 0;
    string temp;
    vector<unsigned int> result;
    while ((i = date.find(delim)) != string::npos) {
        temp = date.substr(0, i);
        result.push_back(stoi(temp));
        date.erase(0, i + delim.length());
    }
    result.push_back(stoi(date));

    return result;
}

