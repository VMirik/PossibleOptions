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


    GraphicKey graphicKey;
    graphicKey.SetFieldKeyCard(3 , 3);

    graphicKey.AddNewPattern(-1,  0, LEFT);
    graphicKey.AddNewPattern( 1,  0, RIGHT);
    graphicKey.AddNewPattern( 0, -1, UP);
    graphicKey.AddNewPattern( 0,  1, DOWN);
    graphicKey.AddNewPattern(-1, -1, DIAGONAL_45_LEFT_UP);
    graphicKey.AddNewPattern( 1, -1, DIAGONAL_45_RIGHT_UP);
    graphicKey.AddNewPattern(-1,  1, DIAGONAL_45_LEFT_DOWN);
    graphicKey.AddNewPattern( 1,  1, DIAGONAL_45_RIGHT_DOWN);

    uint16_t res =  graphicKey.countCodes(startPointName, codelength);

    std::cout<<"PossibleOptions = "<< res <<std::endl;
    return 0;
};
