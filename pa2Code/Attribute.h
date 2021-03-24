/* -----------------------------------------------------------------------------
FILE NAME:         
DESCRIPTION:        
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     **-**-2020         1.0  Original version
----------------------------------------------------------------------------- */
#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>

#include <stdio.h>
#include <unistd.h>




class Attribute {
     private: 
          std::string attributeName, attributeType;
          int numOfValues;
          std::vector<std::string> values;

     public:
          Attribute() {};
          ~Attribute() {};
          Attribute(std::string name, std::string type) {
               attributeName = name;
               attributeType = type;
          }

          void createAttribute(std::string name, std::string type) {
               attributeName = name;
               attributeType = type;
          }

          void displayAttribute() {
               std::cout << attributeName << " " << attributeType;
          }

          std::string getName() {
               return attributeName;
          }

          int getNumOfValues() {
               return numOfValues = values.size();
          }

          void addValue(std::string val) {
               values.push_back(val);
          }

          void displayValue(int i){

               std::cout << values[i] << " | ";
                   
          }

          bool valuesExist(std::string val) {

               bool valExists = false; 

               for (int i = 0; i < values.size(); i++) {

                    if (val == values[i]) {
                         valExists = true;
                    }
               }

               return valExists;

          }

          void getValueIndexes(std::string val, std::vector<int> &valueIndexes) {

               for (int i = 0; i < values.size(); i++) {

                    if (val == values[i]) {
                         
                         valueIndexes.push_back(i);
                         
                    }
               }

          }

          int getNumOfDuplicates(std::string value) {

               int count = 0;

               // figures out how many of the same value are in this attribute
               for (int i = 0; i < values.size(); i++) {

                    if (values[i] == value) {
                         count++;
                    }
                    
               }

               return count;

          }

          bool updateValue(std::string oldValue, std::string newValue) {

               bool success = false;

               for (int i = 0; i < values.size(); i++) {

                    if (oldValue == values[i]) {
                         
                         values[i] = newValue;
                         success = true;
                    }
               }

               return success;

          }

          bool updateMultipleValues(std::string newValue, std::string oldValue, std::vector<int> &valueIndexes) {

               bool success = false;

               for (int i = 0; i < valueIndexes.size(); i++) {

                    if (values[valueIndexes[i]] == oldValue) {
                         values[valueIndexes[i]] = newValue;
                         success = true;
                    }
                    

                    
               }

               return success;

          }
          
          

};




#endif