#include "EmployeeDataParser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
//#include "c:/dev/c++/vcpkg/installed/x64-windows/include/pugixml.hpp"
//#include "c:/dev/c++/vcpkg/installed/x64-windows/include/nlohmann/json.hpp"

#include "pugixml.hpp"  // XML parsing library
#include "json.hpp"     // JSON parsing library (nlohmann/json)


using json = nlohmann::json;
using namespace std;


// Function to parse XML file
vector<Employee> parseXML(const string& filename) {
    vector<Employee> employees;
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str())) {
        cerr << "Error loading XML file: " << filename << endl;
        return employees;
    }

    for (pugi::xml_node emp = doc.child("employees").child("employee"); emp; emp = emp.next_sibling("employee")) {
        Employee e;
        e.name = emp.child("name").text().as_string();
        e.id = emp.child("id").text().as_int();
        e.department = emp.child("department").text().as_string();
        e.salary = emp.child("salary").text().as_double();
        employees.push_back(e);
    }
    return employees;
}

// Function to parse JSON file
vector<Employee> parseJSON(const string& filename) {
    vector<Employee> employees;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error loading JSON file: " << filename << endl;
        return employees;
    }

    json j;
    file >> j;

    for (auto& emp : j["employees"]) {
        Employee e;
        e.name = emp["name"];
        e.id = emp["id"];
        e.department = emp["department"];
        e.salary = emp["salary"];
        employees.push_back(e);
    }
    return employees;
}

// Function to calculate the average salary
double calculateAverageSalary(const vector<Employee>& employees) {
    if (employees.empty()) return 0;
    double total = 0;
    for (const auto& e : employees) total += e.salary;
    return total / employees.size();
}

// Function to find the highest-paid employee
Employee findHighestPaid(const vector<Employee>& employees) {
    return *max_element(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.salary < b.salary;
        });
}

// Function to sort employees by ID
void sortEmployeesByID(vector<Employee>& employees) {
    sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.id < b.id;
        });
}

// Function to display results
void displayResults(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees found." << endl;
        return;
    }

    double avgSalary = calculateAverageSalary(employees);
    Employee highestPaid = findHighestPaid(employees);
    vector<Employee> sortedEmployees = employees;
    sortEmployeesByID(sortedEmployees);

    cout << "Average Salary: " << avgSalary << endl;
    cout << "Highest Paid Employee: " << highestPaid.name << ", Salary: " << highestPaid.salary << endl;
    cout << "Sorted Employees by ID:" << endl;
    for (const auto& e : sortedEmployees) {
        cout << "ID: " << e.id << ", Name: " << e.name << ", Salary: " << e.salary << endl;
    }
}

#ifndef TEST_BUILD
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <XML file> <JSON file>" << endl;
        return 1;
    }

    string xmlFile = argv[1];
    string jsonFile = argv[2];

    vector<Employee> employees;
    vector<Employee> xmlEmployees = parseXML(xmlFile);
    vector<Employee> jsonEmployees = parseJSON(jsonFile);

    employees.insert(employees.end(), xmlEmployees.begin(), xmlEmployees.end());
    employees.insert(employees.end(), jsonEmployees.begin(), jsonEmployees.end());

    displayResults(employees);
    return 0;
}
#endif