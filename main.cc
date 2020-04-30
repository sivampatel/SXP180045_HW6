/*
 * File:   main.cc
 * Author: Sivam Patel
 * Email:  sxp180045@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include "header.h"
#include <fstream>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "My Matrix"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "R1", "R2", "R3"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "C1", "C2"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
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

  // char * placeholder = new char[maxRecordStringLength];
  ifstream binaryFile("/scratch/perkins/cs3377.bin", ios::in | ios::binary);
  BinaryFileHeader *head = new BinaryFileHeader();
  binaryFile.read((char*)head ,sizeof(BinaryFileHeader));
  std::cout << head->magicNumber << " " << head->versionNumber << " " << head->numRecords<< std::endl;
  sleep(100);
  
  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  setCDKMatrixCell(myMatrix, 2, 1, "New Test Message");

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
