#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "avl.h"

using namespace std;

list<vector<string>> readCSV(string filename)
{
    list<vector<string>> data; // List to store all vectors

    ifstream file(filename); // Open CSV file

    if (!file.is_open()) // Check if the file was opened successfully
    {
        cout << "Error opening file.\n";
        return data; // Return empty list
    }

    string line;
    while (getline(file, line)) // Read the CSV file line by line
    {
        size_t pos = 0;
        string token;

        vector<string> row; // Vector to store data for each row

        // Extract data from the NationalID column
        pos = line.find(",");
        token = line.substr(0, pos);
        row.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the GivenName column
        pos = line.find(",");
        token = line.substr(0, pos);
        row.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the Surname column
        pos = line.find(",");
        token = line.substr(0, pos);
        row.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the Birthday column
        pos = line.find(",");
        token = line.substr(0, pos);
        row.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the City column
        row.push_back(line);

        data.push_back(row); // Add the row vector to the list
    }

    file.close(); // Close the CSV file

    return data; // Return the list of vectors
}

int main()
{
    /*     AVLTree<int> tree;

        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(40);
        tree.insert(50);
        tree.insert(25);

        std::cout << "In-order traversal: ";
        tree.inOrderTraversal();
        std::cout << std::endl;

        std::cout << "Pre-order traversal: ";
        tree.preOrderTraversal();
        std::cout << std::endl; */

    vector<string> nationalIDs; // Vector to store data from the NationalID column
    vector<string> givenNames;  // Vector to store data from the GivenName column
    vector<string> surnames;    // Vector to store data from the Surname column
    vector<string> birthdays;   // Vector to store data from the Birthday column
    vector<string> cities;      // Vector to store data from the City column

    ifstream file("data.csv"); // Open CSV file

    if (!file.is_open()) // Check if the file was opened successfully
    {
        cout << "Error opening file.\n";
        return 0;
    }

    string line;
    while (getline(file, line)) // Read the CSV file line by line
    {
        size_t pos = 0;
        string token;

        // Extract data from the NationalID column
        pos = line.find(",");
        token = line.substr(0, pos);
        nationalIDs.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the GivenName column
        pos = line.find(",");
        token = line.substr(0, pos);
        givenNames.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the Surname column
        pos = line.find(",");
        token = line.substr(0, pos);
        surnames.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the Birthday column
        pos = line.find(",");
        token = line.substr(0, pos);
        birthdays.push_back(token);
        line.erase(0, pos + 1);

        // Extract data from the City column
        cities.push_back(line);
    }

    file.close(); // Close the CSV file

    // Print the data from each vector
    for (int i = 0; i < nationalIDs.size(); i++)
    {
        cout << nationalIDs[i] << " ";
        cout << givenNames[i] << " ";
        cout << surnames[i] << " ";
        cout << birthdays[i] << " ";
        cout << cities[i] << endl;
    }

    return 0;
}