/*                                                                                                                                                                                                         
 * header.h
 * 4/30/2020                                                                                                                                                                                               
 * Sivam Patel                                                                                                                                                                                             
 * sxp180045@utdallas.edu                                                                                                                                                                                  
 * CS 3377.501 Spring 2020                                                                                                                                                                                 
 * 1.0                                                                                                                                                                                                     
 * 2020, All Rights Reserved                                                                                                                                                                               
 *                                                                                                                                                                                                         
 * Description                                                                                                                                                                                            
 *                                                                                                                                                                                                        
 *     Header file. Contains the BinaryFileHeader and BinaryFileRecord classes.
 */

#include <stdint.h>

class BinaryFileHeader
{
 public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength]; 
};


