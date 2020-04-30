/*                                                                                                                                                                                                         
 * main.cpp                                                                                                                                                                                                
 * 4/30/2020                                                                                                                                                                                               
 * Sivam Patel                                                                                                                                                                                             
 * sxp180045@utdallas.edu                                                                                                                                                                                  
 * CS 3377.501 Spring 2020                                                                                                                                                                                 
 * 1.0                                                                                                                                                                                                     
 * 2020, All Rights Reserved                                                                                                                                                                               
 *                                                                                                                                                                                                         
 * Description                                                                                                                                                                                             
 *                                                                                                                                                                                                         
 *     Main file for assignment6. It will create the CDK matrix and parse the binary
 *     file to get the header information, put it into the CDK matrix, and display it.
 */

#include <iostream>
#include "cdk.h"
#include "header.h"
#include <fstream>
#include <sstream>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH maxRecordStringLength
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"", "a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  ifstream binaryFile;
  // open binary file

  binaryFile.open("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  // check if file opened properly
  if(!binaryFile.is_open())
    {
      std::cout << "Failed to open file. Exiting." << std::endl;
      exit(EXIT_FAILURE);
    }
  // create header class to store header data
  BinaryFileHeader *head = new BinaryFileHeader();
  // read binary file data to headeer
  binaryFile.read((char*)head ,sizeof(BinaryFileHeader));

  std::stringstream st;

  // add magic number to matix
  st << "Magic: 0x" << hex << uppercase << head->magicNumber;  
  setCDKMatrixCell(myMatrix, 1, 1, st.str().c_str());
  st.str(std::string());

  stringstream ss;  // stringstream for everything else besides Magic Number

  // add version number to matrix
  ss << "Version: " << (int)head->versionNumber;
  setCDKMatrixCell(myMatrix, 1, 2, ss.str().c_str());
  ss.str(std::string());
  
  // add number of records to matrix
  ss << "NumRecords: " << head->numRecords;
  setCDKMatrixCell(myMatrix, 1, 3, ss.str().c_str());
  
  // get max number of records (check if more than 4)
  int maxRecords = (int)head->numRecords;
  if(maxRecords > 4)
    maxRecords = 4;

  for(int x = 2; x < maxRecords + 2; x++)
    {
      // reset stringstream
      ss.str(std::string());
      // get next record
      BinaryFileRecord *record = new BinaryFileRecord();
      // read data into record
      binaryFile.read((char *) record, sizeof(BinaryFileRecord));
      // convert string length to string
      ss << (int)record->strLength;
      // insert data into matrix
      setCDKMatrixCell(myMatrix, x, 1, ss.str().c_str());
      setCDKMatrixCell(myMatrix, x, 2, record->stringBuffer);
      // delete record
      delete record;
    }
  
  // create completed matrix
  drawCDKMatrix(myMatrix, true);

  // sleep to view matrix
  sleep (10);


  // Cleanup screen
  endCDK();
}
