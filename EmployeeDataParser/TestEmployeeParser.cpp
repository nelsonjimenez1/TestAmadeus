#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "EmployeeDataParser.h"

using namespace std;

// Test para parseXML usando el archivo real
TEST(ParserTest, ParseXMLFile) {
    vector<Employee> employees = parseXML("../data/employees_1.xml");
    ASSERT_EQ(employees.size(), 2);

    EXPECT_EQ(employees[0].name, "John Doe");
    EXPECT_EQ(employees[0].id, 1);
    EXPECT_EQ(employees[0].salary, 50000);

    EXPECT_EQ(employees[1].name, "Jane Smith");
    EXPECT_EQ(employees[1].id, 2);
    EXPECT_EQ(employees[1].salary, 70000);
}

// Test para parseJSON usando el archivo real
TEST(ParserTest, ParseJSONFile) {
    vector<Employee> employees = parseJSON("../data/employees_1.json");
    ASSERT_EQ(employees.size(), 2);

    EXPECT_EQ(employees[0].name, "Alice Brown");
    EXPECT_EQ(employees[0].id, 3);
    EXPECT_EQ(employees[0].salary, 60000);

    EXPECT_EQ(employees[1].name, "Bob White");
    EXPECT_EQ(employees[1].id, 4);
    EXPECT_EQ(employees[1].salary, 80000);
}

// Test para verificar displayResults con datos reales
TEST(DisplayTest, DisplayResultsOutput) {
    vector<Employee> employees = parseXML("../data/employees_1.xml");
    vector<Employee> employeesJson = parseJSON("../data/employees_1.json");

    employees.insert(employees.end(), employeesJson.begin(), employeesJson.end());

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());  // Redirigir cout al stringstream

    displayResults(employees);

    cout.rdbuf(old);  // Restaurar cout original
    string output = buffer.str();

    // Comprobaciones en el output
    EXPECT_NE(output.find("Average Salary"), string::npos);
    EXPECT_NE(output.find("Highest Paid Employee: Bob White, Salary: 80000"), string::npos);
    EXPECT_NE(output.find("ID: 1, Name: John Doe"), string::npos);
    EXPECT_NE(output.find("ID: 2, Name: Jane Smith"), string::npos);
    EXPECT_NE(output.find("ID: 3, Name: Alice Brown"), string::npos);
    EXPECT_NE(output.find("ID: 4, Name: Bob White"), string::npos);
}

// Ejecutar todos los tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
