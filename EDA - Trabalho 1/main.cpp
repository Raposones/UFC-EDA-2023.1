#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "avl.h"
#include "person.h"

void menu()
{
    cout << "\n*******************************" << endl;
    cout << "[1] Search for a national ID (CPF)" << endl;
    cout << "[2] Search for a name - by prefix" << endl;
    cout << "[3] Search for a name - by substring" << endl;
    cout << "[4] Search for a birthday range" << endl;
    cout << "[5] - Exit" << endl;
    cout << "*******************************"
         << endl;
}

int main()
{
    AVL<string> natID_tree;
    AVL<string> name_tree;
    AVL<string> birthday_tree(true);

    ifstream file("data.csv");

    if (!file.is_open())
    {
        cout << "Cannot open file.\n";
        return 0;
    }

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string natID, fname, surname, city, fullname, bday_str;
        Date bday;
        getline(ss, natID, ',');
        getline(ss, fname, ',');
        getline(ss, surname, ',');
        getline(ss, bday_str, ',');
        getline(ss, city, ',');
        fullname = fname + " " + surname;

        bday = str_to_date(bday_str);

        Person *p = new Person(natID, fullname, bday, city);
        name_tree.insert(fullname, p);
        natID_tree.insert(natID, p);
        birthday_tree.insert(bday_str, p);
    }

    file.close();

    // natID_tree.in_order();
    // name_tree.in_order();
    // name_tree.prefix_search("Mar");
    // name_tree.substring_search("mil");
    // birthday_tree.date_range_search("01/01/1972", "01/01/1973");

    int key;
    string search;
    string date1, date2;

    do
    {
        menu();
        cout << "==> ";
        cin >> key;
        switch (key)
        {
        case 1:
            cout << "\n*******************************" << endl;
            cout << "You are now searching in NAT. ID TREE. Keys in this tree uses XXX.XXX.XXX-XX format!\n"
                 << endl;
            cout << "Enter a national ID." << endl;
            cout << "*******************************" << endl;
            cout << "==> ";
            cin >> search;
            natID_tree.natID_search(search);
            break;

        case 2:
            cout << "\n*******************************" << endl;
            cout << "You are now searching in NAME TREE. Keys in this tree are case sensitive!.\n"
                 << endl;
            cout << "Which prefix are you searching for?" << endl;
            cout << "*******************************" << endl;
            cout << "==> ";
            cin >> search;
            name_tree.prefix_search(search);
            break;

        case 3:
            cout << "\n*******************************" << endl;
            cout << "You are now searching in NAME TREE. Keys in this tree are case sensitive!.\n"
                 << endl;
            cout << "Which substring are you searching for?" << endl;
            cout << "*******************************" << endl;
            cout << "==> ";
            cin >> search;
            name_tree.substring_search(search);
            break;

        case 4:
            cout << "\n*******************************" << endl;
            cout << "You are now searching in BIRTHDAY TREE. Keys in this tree are strings and uses DD/MM/YYYY format!\n"
                 << endl;
            cout << "Enter the starting date." << endl;
            cout << "*******************************" << endl;
            cout << "==> ";
            cin >> date1;
            cout << "\n*******************************" << endl;
            cout << "Enter the limit date." << endl;
            cout << "*******************************" << endl;
            cout << "==> ";
            cin >> date2;
            birthday_tree.date_range_search(date1, date2);
            break;

        case 5:
            cout << "Goodbye!";
            break;

        default:
            cout
                << "Invalid choice. Please, choose one of the options available!"
                << endl;
            break;
        }
    } while (key != 5);
}