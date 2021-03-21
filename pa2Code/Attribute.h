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
          
          

};




#endif