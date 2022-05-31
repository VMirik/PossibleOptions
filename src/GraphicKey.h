#ifndef GRAPHICKEY_H_
#define GRAPHICKEY_H_
#include <iostream>


//namespace GRAPHICKEY
//{

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


struct sPatternForPossibleCombinations
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


class Uncopyable {
protected:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
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
    * Sum numbers in a vector.
    *
    * @param values Container whose values are summed.
    * @return sum of `values`, or 0.0 if `values` is empty.
    */
    uint8_t GetPatternCount();
    
    /**
    * Sum numbers in a vector.
    *
    * @param values Container whose values are summed.
    * @return sum of `values`, or 0.0 if `values` is empty.
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

public:
    GraphicKeyCard(int16_t keyCardLength = 3, int16_t keyCardWidth = 3);
    ~GraphicKeyCard();

    bool SetFieldKeyCard(int16_t keyCardLength, int16_t keyCardWidth);
    int16_t getKeyCardLength();
    int16_t getKeyCardWidth();
    int16_t getKeyCardSize();

    uint16_t lookPosition(int16_t curPos, eDirection dirPatternNum);
};

struct sDraftTree
{
    struct sDraftTree* parent;
    int16_t pos;
    eDirection dirPatternNum;
    int16_t numberToFinish;
};

//==================================================================================================
//    GraphicKey class function Declaration
//==================================================================================================

class GraphicKey: public GraphicKeyCard
{
private:

    int16_t turnDirAndCheck(struct sDraftTree* pDraftTree, eDirection pattern);
    uint16_t counterOfSuccess(struct sDraftTree* pDraftTree);
public:
    GraphicKey();
    ~GraphicKey();
    
    uint16_t countCodes(char start = 'A', int16_t length = 7);

};
//}
#endif /* GRAPHICKEY_H_ */