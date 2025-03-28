#ifndef EMPLOYEE_DATA_PARSER_H
#define EMPLOYEE_DATA_PARSER_H

#include <vector>
#include <string>

struct Employee {
    std::string name;
    int id;
    std::string department;
    double salary;
};

// Funciones de parsing
std::vector<Employee> parseXML(const std::string& filename);
std::vector<Employee> parseJSON(const std::string& filename);

// Funciones de cálculo
double calculateAverageSalary(const std::vector<Employee>& employees);
Employee findHighestPaid(const std::vector<Employee>& employees);
void sortEmployeesByID(std::vector<Employee>& employees);

// Función de salida
void displayResults(const std::vector<Employee>& employees);

#endif // EMPLOYEE_DATA_PARSER_H
#pragma once
