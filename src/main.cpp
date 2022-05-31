#include <sstream>
#include <iostream>
#include "GraphicKey.h"

using namespace std;

int main(int argc, char *argv[])
{
    
    std::stringstream convert(argv[2]);

	int codelength;
	char startPointName;
    if (!(convert >> codelength))
    {
        startPointName = 'A';
        codelength = 7;
    }
    else
        startPointName = *(argv[1]);
        
    GRAPHICKEY::GraphicKey graphicKey;
    
    graphicKey.SetFieldKeyCard(3 , 3);
    
    /*
    * 1.  2.  3.  4.  5.  6.  7.  8.
    * BA- -AB -A- -B- B-- --B --- ---
    * --- --- -B- -A- -A- -A- -A- -A-
    * --- --- --- --- --- --- B-- --B
    */
    graphicKey.AddNewPattern(-1,  0, GRAPHICKEY::LEFT);
    graphicKey.AddNewPattern( 1,  0, GRAPHICKEY::RIGHT);
    graphicKey.AddNewPattern( 0, -1, GRAPHICKEY::UP);
    graphicKey.AddNewPattern( 0,  1, GRAPHICKEY::DOWN);
    graphicKey.AddNewPattern(-1, -1, GRAPHICKEY::DIAGONAL_45_LEFT_UP);
    graphicKey.AddNewPattern( 1, -1, GRAPHICKEY::DIAGONAL_45_RIGHT_UP);
    graphicKey.AddNewPattern(-1,  1, GRAPHICKEY::DIAGONAL_45_LEFT_DOWN);
    graphicKey.AddNewPattern( 1,  1, GRAPHICKEY::DIAGONAL_45_RIGHT_DOWN);
    
    /*
    * 1.  2.  3.  4.  5.  6.  7.  8.
    * -B- --- --A A-- A-- --- --- -B-
    * --- B-- B-- --- --B --B --B ---
    * --A --A --- -B- --- A-- A-- A--
    */
    graphicKey.AddNewPattern(-1, -2, GRAPHICKEY::DIAGONAL_SHARP_MLEFT_M2UP);
    graphicKey.AddNewPattern(-2, -1, GRAPHICKEY::DIAGONAL_SHARP_M2LEFT_MUP);
    graphicKey.AddNewPattern(-2,  1, GRAPHICKEY::DIAGONAL_SHARP_M2LEFT_DOWN);
    graphicKey.AddNewPattern(-1,  2, GRAPHICKEY::DIAGONAL_SHARP_MLEFT_2DOWN);
    graphicKey.AddNewPattern( 1,  2, GRAPHICKEY::DIAGONAL_SHARP_RIGHT_2DOWN);
    graphicKey.AddNewPattern( 2,  1, GRAPHICKEY::DIAGONAL_SHARP_2RIGHT_DOWN);
    graphicKey.AddNewPattern( 2, -1, GRAPHICKEY::DIAGONAL_SHARP_2RIGHT_MDOWN);
    graphicKey.AddNewPattern( 1, -2, GRAPHICKEY::DIAGONAL_SHARP_RIGHT_M2DOWN);

    // + pattern of passing through the point if it is busy,
    // but there is a free point further down the direction

    
    //EXECUTE    
    uint32_t res =  graphicKey.countCodes(startPointName, codelength);

    std::cout<<"PossibleOptions = "<< res <<std::endl;
    return 0;
};

//todo list 
// 1. Testing? UNIT all
// 2. Template to main class
// 3. Exeptions
// 4. +Declatations
// 5. fix operators
// 6. Input params!!
// 7. add task img to git
