#include <iostream>

using namespace std;

#define LEFT_RIGHT 0
#define UP_DOWN    1

typedef enum
{
  START = 0,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  DIAGONAL_45_LEFT_UP,
  DIAGONAL_45_RIGHT_UP,
  DIAGONAL_45_LEFT_DOWN,
  DIAGONAL_45_RIGHT_DOWN
} eDirection;

struct sDraftTree{
  const struct sDraftTree* const parent;
  uint16_t pos;
  eDirection dirPatternNum;
  uint8_t numberToFinish;
};

uint8_t g_tableLenngth = 3;
uint8_t g_tableWidth = 3;
uint16_t g_tableSize = g_tableLenngth * g_tableWidth;

#define PATTERN_COUNT 9U

int8_t g_dirPatternCount = PATTERN_COUNT;
int8_t g_dirPattern[PATTERN_COUNT][2] =
{
    { 0,  0 },  //START
    {-1,  0 },  //LEFT
    { 1,  0 },  //RIGHT
    { 0, -1 },  //UP
    { 0,  1 },  //DOWN
    {-1, -1 },  //DIAGONAL_45_LEFT_UP
    { 1, -1 },  //DIAGONAL_45_RIGHT_UP
    {-1,  1 },  //DIAGONAL_45_LEFT_DOWN
    { 1,  1 },  //DIAGONAL_45_RIGHT_DOWN
};

int16_t lookPosition(uint8_t curPos, eDirection dirPatternNum)
{
    if(curPos > g_tableSize - 1)
        return -1;
    if(dirPatternNum < 1 || dirPatternNum > g_dirPatternCount - 1)
        return -1;

    int8_t *pPatternNum = &::g_dirPattern[dirPatternNum][0];

    int8_t numCurLine = (int8_t)curPos / (int8_t)g_tableWidth; // get current line
    numCurLine += pPatternNum[UP_DOWN];                             //get the desired line
    if(numCurLine < 0 || numCurLine > (int16_t)g_tableLenngth - 1)
        return -1;

    int8_t numCurColumn = (int8_t)(curPos % g_tableLenngth);   // get current column
    numCurColumn += pPatternNum[LEFT_RIGHT];                        //get the desired column
    if(numCurColumn < 0 || numCurColumn > (int8_t)g_tableWidth -1)
        return -1;

    return (uint16_t)(numCurLine * (int8_t)g_tableLenngth + numCurColumn);
}

int8_t turnDirAndCheck(const struct sDraftTree* const pDraft, eDirection dirPatternNum)
{
    int16_t newPos = -1;

    newPos = lookPosition(pDraft->pos, dirPatternNum);

    //position is out of the table
    if(newPos <= -1 || newPos >= (int8_t)g_tableSize)
        return -1;


    const struct sDraftTree* pDraftParent = pDraft->parent;

    while(pDraftParent != nullptr)
    {
        if(pDraftParent->pos == newPos)
        {
            // try to look beyond this point which is already occupied
            uint8_t length = pDraft->numberToFinish - 1U;
            struct sDraftTree newDraft = { pDraft, (uint16_t)newPos, dirPatternNum, length};
            newPos = turnDirAndCheck(&newDraft, dirPatternNum);
            break;
        }
        pDraftParent = pDraftParent->parent;
    }

    return newPos;
}

unsigned int counterOfSuccess(const struct sDraftTree* const pDraft)
{
    uint8_t countOfSuccess = 0;


    //limit the check. no START direction
    for(uint8_t dirPatternNum = 1; dirPatternNum < g_dirPatternCount; dirPatternNum ++)
    {
        int16_t unocPosition = turnDirAndCheck(pDraft, (eDirection)dirPatternNum);
        if(unocPosition == -1)
            continue;

        if(pDraft->numberToFinish > 1)
        {
            uint8_t length = pDraft->numberToFinish - 1U;
            struct sDraftTree newDraft = { pDraft, (uint16_t)unocPosition, (eDirection)dirPatternNum, length};
            countOfSuccess += counterOfSuccess(&newDraft);
        }
        else
            countOfSuccess ++;
    }

    return countOfSuccess;
}

unsigned int countCodes(uint8_t start, uint8_t length)
{
    if(start < 'A' && start > 'I')
        return 0;
    if(length == 0 || length > g_tableSize - 1)
        return 0;
    uint8_t pos = start - (uint8_t)'A';

    length -= 1U;
    struct sDraftTree draft = { nullptr, pos, START, length};

    return counterOfSuccess(&draft);
}

int main()
{
    std::cout<<"PossibleOptions = "<< countCodes('A', 7) <<std::endl;

    return 0;
};
