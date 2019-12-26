#ifndef MATRIXCALCULATORCLASS_H     // Protection against multiple inclusions
#define MATRIXCALCULATORCLASS_H

#include <iostream>                 // To be able to interact with user through cout, cin
#include <fstream>                  // To be able to work with files through ifstream, ofstream
#include <sstream>                  // To be able to manipulate strings through stringstream
#include <cmath>                    // To be able to use floor rounding operation

class MatrixCalculatorClass {       // Class for Matrix Calculator
private:                            // Private class members

    class Matrix {                                  // Subclass for matrix manipulation
    private:                                        // Private subclass members
        static unsigned int counter;                // Counter of how many matrices were created
        unsigned int order;                         // Order in which each matrix was created
        unsigned int rows;                          // Rows of matrix
        unsigned int columns;                       // Columns of matrix
    public:                                         // Public subclass members
        Matrix(void);                               // Subclass object constructor
        unsigned int getOrder(void);                // Get order in which matrix was created
        unsigned int getRows(void);                 // Get number of rows of matrix
        unsigned int getColumns(void);              // Get number of columns of matrix
        void setRows(unsigned int);                 // Set number of rows of matrix
        void setColumns(unsigned int);              // Set number of columns of matrix
        void saveMatrix(void);                      // Save elements of matrix into text file
        void readMatrix(void);                      // Read out elements of matrix from text file
        double getNthMatrixElement(unsigned int);   // Get specific element of matrix
    };

public:

    class Tools {                               // Subclass for interaction with user and input validation
    public:                                     // Public subclass members
        bool isIntNum(char);                    // Check whether character is valid positive number
        bool isIntValid(std::string);           // Check whether string number consists of valid positive numbers
        int requestIntInput(void);              // Request input from user, expecting positive nonzero number
        bool isDoubleNum(char);                 // Check whether character is valid number
        bool isDoubleValid(std::string);        // Check whether string number consists of valid numbers
        double requestDoubleInput(void);        // Request input from user, expecting any number
        void matrixManagement(std::string);     // Manipulate matrices based on user choice
        std::string menuPrompt(void);           // Ask user to choose desired operation
        void menu(void);                        // Select course of action based on user choice
    };

};

extern MatrixCalculatorClass::Tools MatrixCalculator;   // Declaration of Tools subclass object

#endif                      // MATRIXCALCULATORCLASS_H
