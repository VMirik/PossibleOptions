#ifndef GRAPHICKEY_H_
#define GRAPHICKEY_H_
#include <iostream>
#include <cstring>

namespace GRAPHICKEY
{

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
    DIAGONAL_45_RIGHT_DOWN,
    DIAGONAL_SHARP_MLEFT_M2UP,
    DIAGONAL_SHARP_M2LEFT_MUP,
    DIAGONAL_SHARP_M2LEFT_DOWN,
    DIAGONAL_SHARP_MLEFT_2DOWN,
    DIAGONAL_SHARP_RIGHT_2DOWN,
    DIAGONAL_SHARP_2RIGHT_DOWN,
    DIAGONAL_SHARP_2RIGHT_MDOWN,
    DIAGONAL_SHARP_RIGHT_M2DOWN
} eDirection;


struct __attribute__ ((__packed__))sPatternForPossibleCombinations
{
    struct sPatternForPossibleCombinations* parent;
    int16_t leftRigth;
    int16_t upDown;
    eDirection dirPatternNum;

    sPatternForPossibleCombinations
    (
        struct sPatternForPossibleCombinations* aParent = nullptr,
        int16_t aLeftRigth = 0,
        int16_t aUpDown = 0,
        eDirection aDirPatternNum = START
    ):
        parent(aParent),
        leftRigth(aLeftRigth),
        upDown(aUpDown),
        dirPatternNum(aDirPatternNum)
    {}
    ~sPatternForPossibleCombinations(){if(this->parent != nullptr) delete this->parent;}
};


//==================================================================================================
//    PatternForPossibleCombinations class function Declaration
//==================================================================================================

class PatternForPossibleCombinations
{
private:
   struct sPatternForPossibleCombinations* m_pLastPattern;

   PatternForPossibleCombinations(const PatternForPossibleCombinations&); 
   PatternForPossibleCombinations& operator=(const PatternForPossibleCombinations&);

protected: 
  uint8_t m_PatternCount; 

public:
    PatternForPossibleCombinations();
    ~PatternForPossibleCombinations();

    /**
    * Add a new pattern for a unique search 
    *
    * @param  leftRigth     Indicates direction: -x left, x right.
    * @param  upDown        Indicates direction: : -x up, x down.
    * @param  dirPatternNum Direction indicator
    * @return               execution success.
    */
    bool AddNewPattern(int16_t leftRigth, int16_t upDown, eDirection dirPatternNum);
    
    /**
    * Get number of patterns.
    *
    * @return count.
    */
    uint8_t GetPatternCount();
    
    /**
    * Get pattern structure.
    *
    * @param pos Enum named after patern.
    * @return    structure with settings.
    */
    struct sPatternForPossibleCombinations* GetPattern(eDirection pos);
};

//==================================================================================================
//    GraphicKeyCard class function Declaration
//==================================================================================================

class GraphicKeyCard: public PatternForPossibleCombinations
{
protected:
    int16_t m_keyCardLength;
    int16_t m_keyCardWidth;
    int16_t m_keyCardSize;
    
    bool *m_pAreaBuff;

public:
    GraphicKeyCard(int16_t keyCardLength = 3, int16_t keyCardWidth = 3);
    ~GraphicKeyCard();

    /**
    * Create workspace.
    *
    * @param keyCardLength table Length. To define the working area.
    * @param keyCardWidth  table width. To define the working area.
    * @return    execution success.
    */
    bool SetFieldKeyCard(int16_t keyCardLength, int16_t keyCardWidth);
    
    
    int16_t getKeyCardLength();
    int16_t getKeyCardWidth();
    int16_t getKeyCardSize();

    /**
    * Finding a position on the field using a pattern.
    *
    * @param curPos         current position.
    * @param dirPatternNum  pattern name (look in enum).
    * @return               Found new position. if failure then -1.
    */
    uint16_t lookPosition(int16_t curPos, eDirection dirPatternNum);
};

//==================================================================================================
//    GraphicKey class function Declaration
//==================================================================================================

class GraphicKey: public GraphicKeyCard
{
private:

    int16_t turnDirAndCheck(int16_t pos, eDirection pattern);
    uint32_t counterOfSuccess(int16_t pos, int16_t length);

public:
    GraphicKey();
    ~GraphicKey();

   /**
    * Starting function for searching for possible variants 
    * of a graphic key using patterns and a given length
    *
    * @param start          sign value A-Z.c
    *                       orresponds to the position on the table
    * @param length         pattern password length.
    * @return               Found result. The number of possible 
    *                       combinations in the specified 
    *                       area and length
    */
    uint32_t countCodes(char start = 'A', int16_t length = 7);

};
}
#endif /* GRAPHICKEY_H_ */