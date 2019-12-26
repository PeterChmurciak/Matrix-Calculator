#include "MatrixCalculatorClass.h"                                       // Include header file

unsigned int MatrixCalculatorClass::Matrix::counter = 0;                 // Initialize static counter as 0

MatrixCalculatorClass::Matrix::Matrix(void) {                            // Subclass object constructor
    rows = columns = 0;                                                  // Initialize matrix rows and columns as 0
    counter++;                                                           // Increment counter of created matrices
    order = counter;                                                     // Set order in which the matrix was created
}

unsigned int MatrixCalculatorClass::Matrix::getOrder(void) {             // Get order in which matrix was created
    return order;
}

unsigned int MatrixCalculatorClass::Matrix::getRows(void) {              // Get number of rows of matrix
    return rows;
}

unsigned int MatrixCalculatorClass::Matrix::getColumns(void) {           // Get number of columns of matrix
    return columns;
}

void MatrixCalculatorClass::Matrix::setRows(unsigned int inputRows) {    // Set number of rows of matrix
    rows = inputRows;
}

void MatrixCalculatorClass::Matrix::setColumns(unsigned int inputColumns) {     // Set number of columns of matrix
    columns = inputColumns;
}

void MatrixCalculatorClass::Matrix::saveMatrix(void) {                  // Save elements of matrix into text file
    std::ofstream Matrices("matrix.txt", std::ios::app);                // Create output stream class object Matrices connected to matrix.txt file in append mode

    for (unsigned int i = 0; i < getRows(); i++) {                      // Prompt user to input all rows of matrix one by one
        std::cout << "Enter row " << i + 1 << ": ";
        std::string line;                                               // Variable to store user string input of matrix row
        getline(std::cin, line);                                        // Get input from user and save it to line variable
        unsigned int counterOfSpaces = 0;                               // Counter of how many space characters there were in user row input
        unsigned int counterOfInvalidCharacters = 0;                    // Counter of how many invalid characters there were in user row input

        for (unsigned int j = 0; j < line.length(); j++) {              // Check each character of user input and increment counters if needed
            char element = line.at(j);
            if (element == ' ') {                                                                                   // If space character
                counterOfSpaces++;
            }
            if ( !((element >= '0' && element <= '9') || (element == '-' || element == ' ' || element == '.'))) {   // If not a valid character
                counterOfInvalidCharacters++;
            }
            if ( !(element >= '0' && element <= '9') && (line.length() == 1)) {                                     // If single character but not a number
                counterOfInvalidCharacters++;
            }
        }
        while (counterOfSpaces != getColumns() - 1 || counterOfInvalidCharacters != 0 || counterOfSpaces > line.length() - getColumns()) {
            std::cout << "Invalid input! Insert row " << i + 1 << " again: ";                                       // Repeat prompt until input is valid
            getline(std::cin, line);
            counterOfSpaces = counterOfInvalidCharacters = 0;
            for (unsigned int j = 0; j < line.length(); j++) {
                char element = line.at(j);
                if (element == ' ') {
                    counterOfSpaces++;
                }
                if ( !((element >= '0' && element <= '9') || (element == '-' || element == ' ' || element == '.'))) {
                    counterOfInvalidCharacters++;
                }
                if ( !(element >= '0' && element <= '9') && (line.length() == 1)) {
                    counterOfInvalidCharacters++;
                }
            }
        }
        std::stringstream stringStreamObject;                   // Create stringstream class object
        unsigned int lastPosition = 0;                          // Variable to store position of space character
        double ijElement = 0;                                   // Variable to store element in numeric form

        for (unsigned int i = 0; i < getColumns(); i++) {
            lastPosition = line.find(' ', 0);
            stringStreamObject.clear();
            stringStreamObject << line.substr(0, lastPosition); // Get string part separated by space character
            line = line.substr(lastPosition + 1, line.length());
            stringStreamObject >> ijElement;                    // Transform user string input into numeric form and save it to variable
            Matrices << ijElement << " ";                       // Save the element into text file, separate elements by space character
        }
    }
    Matrices << "\n";                                           // Separate matrices by new line character
    Matrices.close();                                           // Close output stream class object
}

void MatrixCalculatorClass::Matrix::readMatrix(void) {                  // Read out elements of matrix from text file
    std::ifstream Matrices("matrix.txt");                               // Create input stream class object Matrices connected to matrix.txt file
    unsigned int lineNumber = 0;                                        // Variable to keep track what line from text file was just read
    std::string line;                                                   // Variable to store line from text file

    while (lineNumber != getOrder()) {
        getline(Matrices, line);                                        // Get line from file corresponding to the matrix order of creation
        lineNumber++;                                                   // (Each line in text file represents one matrix)
    }
    unsigned int lastPosition = 0;                                      // Variable to store position of space character

    for (unsigned int i = 0; i < getRows(); i++) {                      // Write out all elements separated by space characters in form of matrix
        for (unsigned int j = 0; j < getColumns(); j++) {
            lastPosition = line.find(' ', 0);
            std::cout << line.substr(0, lastPosition) << "\t";
            line = line.substr(lastPosition + 1, line.length());
        }
        std::cout << "\n";
    }
    Matrices.close();                                                   // Close input stream class object
}

double MatrixCalculatorClass::Matrix::getNthMatrixElement(unsigned int N) {     // Get specific element of matrix
    std::ifstream Matrices("matrix.txt");                                       // Create input stream class object Matrices connected to matrix.txt file
    unsigned int lineNumber = 0;                                                // Variable to keep track what line from text file was just read
    std::string line;                                                           // Variable to store line from text file

    while (lineNumber != getOrder()) {
        getline(Matrices, line);                                                // Get line from file corresponding to the matrix order of creation
        lineNumber++;                                                           // (Each line in text file represents one matrix)
    }
    unsigned int lastPosition = 0;                                              // Variable to store position of space character

    for (unsigned int i = 0; i < getRows()*getColumns(); i++) {                 // Search through elements of matrix
        lastPosition = line.find(' ', 0);
        if (i == N) {                                                           // If at Nth element
            line = (line.substr(0, lastPosition));
            std::stringstream stringStreamObject(line);
            double searchedValue;
            stringStreamObject >> searchedValue;                                // Transform string to number
            return searchedValue;                                               // Return searched value of Nth element
        }
        line = line.substr(lastPosition + 1, line.length());
    }
    Matrices.close();                                                           // Close input stream class object
}

bool MatrixCalculatorClass::Tools::isIntNum(char testedChar) {          // Check whether character is valid positive number
    if (testedChar >= '0' && testedChar <= '9') {
        return true;
    } else {
        return false;
    }
}

bool MatrixCalculatorClass::Tools::isIntValid(std::string str) {        // Check whether string number consists of valid positive numbers
    unsigned int check = 0;
    if (str.length() <= 0) {
        return false;
    }
    for (int i = 0; i < str.length(); i++) {                            // Check each character of string
        if (isIntNum(str[i]) == false) {
            check++;                                                    // Increment if not valid
        }
    }
    if (check == 0) {                                                   // If all characters valid
        return true;
    } else {                                                            // If found invalid character
        return false;
    }
}

int MatrixCalculatorClass::Tools::requestIntInput() {                       // Request input from user, expecting positive nonzero number
    int requestedInput;                                                     // Variable for storing numeric input
    std::string input;                                                      // Variable for storing user string number input
    getline(std::cin, input);                                               // Get user input

    while (!isIntValid(input) || (input.length() == 1 && input == "0")) {   // Check whether input meets the conditions
        std::cout << "Invalid input! Insert correct value: ";               // If not repeat prompt
        getline(std::cin, input);
    }
    std::stringstream stringStreamObject(input);
    stringStreamObject >> requestedInput;                                   // Transform string to number
    return requestedInput;                                                  // Return number
}

bool MatrixCalculatorClass::Tools::isDoubleNum(char testedChar) {           // Check whether character is valid number
    if ((testedChar >= '0' && testedChar <= '9' && testedChar != ' ') || testedChar == '.' || testedChar == '-') {
        return true;
    } else {
        return false;
    }
}

bool MatrixCalculatorClass::Tools::isDoubleValid(std::string str) {         // Check whether string number consists of valid numbers
    unsigned int check = 0;
    if (str.length() <= 0) {
        return false;
    }
    for (int i = 0; i < str.length(); i++) {                                // Check each character of string
        if (isDoubleNum(str[i]) == false) {
            check++;                                                        // Increment if not valid
        }
    }
    if (check == 0) {                                                       // If all characters valid
        return true;
    } else {                                                                // If found invalid character
        return false;
    }
}

double MatrixCalculatorClass::Tools::requestDoubleInput() {                 // Request input from user, expecting any number
    double requestedInput;                                                  // Variable for storing numeric input
    std::string input;                                                      // Variable for storing user string number input
    getline(std::cin, input);                                               // Get user input

    while (!isDoubleValid(input) || (input.length() == 1 && (input == "-" || input == "."))) {  // Check whether input meets the conditions
        std::cout << "Invalid input! Insert correct value: ";               // If not repeat prompt
        getline(std::cin, input);
    }
    std::stringstream stringStreamObject(input);
    stringStreamObject >> requestedInput;                                   // Transform string to number
    return requestedInput;                                                  // Return number
}

void MatrixCalculatorClass::Tools::matrixManagement(std::string option) {           // Manipulate matrices based on user choice
    if (option == "1" || option == "2") {                                           // Addition or subtraction

        if (option == "1") {
            std::cout << "Addition of two matrices A+B=C\n" << std::endl;
        } else {
            std::cout << "Subtraction of two matrices A-B=C\n" << std::endl;
        }
        Matrix A;                                                                   // First matrix
        std::cout << "Enter dimensions of matrix A...\nNumber of rows: ";
        A.setRows(requestIntInput());
        std::cout << "Number of columns: ";
        A.setColumns(requestIntInput());
        std::cout << "\nEnter element(s) of matrix A..." << std::endl;
        A.saveMatrix();

        Matrix B;                                                                   // Second matrix
        B.setRows(A.getRows());
        B.setColumns(A.getColumns());
        std::cout << "\nMatrix B has to have " << B.getRows() << " row(s) and " << B.getColumns() << " column(s).\n" << std::endl;
        std::cout << "Enter element(s) of matrix B..." << std::endl;
        B.saveMatrix();

        Matrix C;                                                                   // Third, output matrix
        C.setRows(B.getRows());
        C.setColumns(B.getColumns());
        std::cout << "\nOutput matrix C will have " << C.getRows() << " row(s) and " << C.getColumns() <<" column(s).\n" << std::endl;
        std::cout << "Element(s) of output matrix C: " << std::endl;
        std::ofstream Matrices("matrix.txt", std::ios::app);                        // Create output stream class object Matrices connected to matrix.txt file in append mode

        for (int i = 0; i < C.getRows()*C.getColumns(); i++) {
            double ijElement;
            if (option == "1") {
                ijElement = A.getNthMatrixElement(i) + B.getNthMatrixElement(i);    // In addition mode add elements
            } else if (option == "2") {
                ijElement = A.getNthMatrixElement(i) - B.getNthMatrixElement(i);    // In subtraction mode subtract elements
            }
            Matrices << ijElement << " ";                                           // Write resulting matrix to file with elements separated by space character
        }
        Matrices << "\n";                                                           // Separate matrices by newline character
        Matrices.close();                                                           // Close output stream class object
        C.readMatrix();                                                             // Write out elements of resulting matrix C

    } else if (option == "3") {
        std::cout << "Scalar multiplication of a matrix a*B=C\n" << std::endl;      // Scalar multiplication mode
        double scalar;
        std::cout << "Enter value of scalar a..." << std::endl;
        scalar = requestDoubleInput();                                              // Get scalar number from user

        Matrix D;                                                                   // Multiplied matrix
        std::cout << "\nEnter dimensions of multiplied matrix B...\nNumber of rows: ";
        D.setRows(requestIntInput());
        std::cout << "Number of columns: ";
        D.setColumns(requestIntInput());
        std::cout << "\nEnter elements of multiplied matrix B..." << std::endl;
        D.saveMatrix();

        Matrix E;                                                                   // Output matrix
        E.setRows(D.getRows());
        E.setColumns(D.getColumns());
        std::cout << "\nOutput matrix C will have " << E.getRows() << " row(s) and " << E.getColumns() <<" column(s).\n" << std::endl;
        std::cout << "Element(s) of output matrix C: " << std::endl;
        std::ofstream Matrices("matrix.txt", std::ios::app);                        // Create output stream class object Matrices connected to matrix.txt file in append mode

        for (int i = 0; i < E.getRows()*E.getColumns(); i++) {                      // Go through all matrix elements
            double ijElement;
            ijElement = (scalar) * (D.getNthMatrixElement(i));                      // Multiply each  element by scalar
            Matrices << ijElement << " ";                                           // Write resulting matrix to file with elements separated by space character
        }
        Matrices << "\n";                                                           // Separate matrices by newline character
        Matrices.close();                                                           // Close output stream class object
        E.readMatrix();                                                             // Write out elements of resulting matrix C

    } else if (option == "4") {
        std::cout << "Multiplication of two matrices A*B=C" << std::endl;           // Matrix multiplication mode
        Matrix F;                                                                   // First matrix
        std::cout << "\nEnter dimensions of matrix A...\nNumber of rows: ";
        F.setRows(requestIntInput());
        std::cout << "Number of columns: ";
        F.setColumns(requestIntInput());
        std::cout << "\nEnter elements of matrix A..." << std::endl;
        F.saveMatrix();

        Matrix G;
        G.setRows(F.getColumns());                                                  // Second matrix
        std::cout << "\nNumber of rows of matrix B has to be " << G.getRows() << "." << std::endl;
        std::cout << "Number of columns: ";
        G.setColumns(requestIntInput());
        std::cout << "\nEnter elements of matrix B... " << std::endl;
        G.saveMatrix();

        Matrix H;                                                                   // Third, output matrix
        H.setRows(F.getRows());
        H.setColumns(G.getColumns());
        std::cout << "\nOutput matrix C will have " << H.getRows() << " row(s) and " << H.getColumns() <<" column(s).\n" << std::endl;
        std::cout << "Element(s) of output matrix C: " << std::endl;
        std::ofstream Matrices("matrix.txt", std::ios::app);                        // Create output stream class object Matrices connected to matrix.txt file in append mode

        for (int i = 0; i < H.getRows()*H.getColumns(); i++) {                      // Go through all matrix elements
            double ijElement = 0;
            for (int j = 0; j < F.getColumns(); j++) {                              // Get each element as result of matrix multiplication
                ijElement += F.getNthMatrixElement(j + floor(i / H.getColumns()) * F.getColumns()) * G.getNthMatrixElement(i % G.getColumns() + j * G.getColumns());
            }
            Matrices << ijElement << " ";                                           // Write resulting matrix to file with elements separated by space character
        }
        Matrices << "\n";                                                           // Separate matrices by newline character
        Matrices.close();                                                           // Close output stream class object
        H.readMatrix();                                                             // Write out elements of resulting matrix C
    }
}

std::string MatrixCalculatorClass::Tools::menuPrompt() {        // Ask user to choose desired operation
    std::cout << "MENU\n";
    std::cout << "1. Addition of two matrices"<< std::endl;
    std::cout << "2. Subtraction of two matrices"<< std::endl;
    std::cout << "3. Scalar multiplication of a matrix"<< std::endl;
    std::cout << "4. Multiplication of two matrices"<< std::endl;
    std::cout << "5. Exit\n"<< std::endl;
    std::string option;                                         // Variable for storing user string number input
    std::cout << "Option: ";
    getline(std::cin, option);                                  // Get user input

    while ((option != "1" && option != "2" && option != "3" && option != "4" && option != "5") || option.length() > 1) { // Validate user input
        if (std::cin.fail()) {
            std::cin.clear();
        }
        std::cout << "Invalid option!\n"<< std::endl;           // If invalid, prompt again
        std::cout << "Option: ";
        getline(std::cin, option);
    }
    return option;                                              // Return string number option chosen by user
}

void MatrixCalculatorClass::Tools::menu() {                     // Select course of action based on user choice
    std::cout << "Calculator for basic matrix operations. Created by Peter Chmurciak.\n"<< std::endl;
    std::cout << "Enter values of each row separated by SPACE and confirm by pressing ENTER."<< std::endl;
    std::cout << "If needed, use point (dot) as a decimal delimiter.\n"<< std::endl;
    remove("matrix.txt");

    while (1) {
        std::string MenuChoice = menuPrompt();                  // Get user choice

        if (MenuChoice == "5") {                                // If user chose Exit, exit application
            std::cout << "Terminating application..." << std::endl;
            remove("matrix.txt");
            break;
        }
        matrixManagement(MenuChoice);                           // Decide based on user choice
        std::cout << std::endl;
    }
}

MatrixCalculatorClass::Tools MatrixCalculator;                  // Create calculator object to use in main function
