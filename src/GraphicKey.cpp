#include "GraphicKey.h"

//namespace GRAPHICKEY
//{
//==================================================================================================
//    PatternForPossibleCombinations class function implementation
//==================================================================================================

    PatternForPossibleCombinations::PatternForPossibleCombinations():
        m_pLastPattern(new sPatternForPossibleCombinations()),
        m_PatternCount(1U)
    {
        ///
    }
    
    PatternForPossibleCombinations::~PatternForPossibleCombinations()
    {
        delete m_pLastPattern;
    }

    bool PatternForPossibleCombinations::AddNewPattern(int16_t leftRigth, int16_t upDown, eDirection dirPatternNum)
    {
        m_pLastPattern  = new struct sPatternForPossibleCombinations
        (
            m_pLastPattern,
            leftRigth,
            upDown,
            dirPatternNum
        );
        if(m_pLastPattern != nullptr)
        {
            m_PatternCount ++;
            return true;
        }
        return false;
    }
    
    uint8_t PatternForPossibleCombinations::GetPatternCount()
    {
        return m_PatternCount;
    }

    struct sPatternForPossibleCombinations* PatternForPossibleCombinations::GetPattern(eDirection dirPatternNum)
    {
        if((uint16_t)dirPatternNum > m_PatternCount - 1)
            return nullptr;


        struct sPatternForPossibleCombinations* pLastPattern = m_pLastPattern;
        while(pLastPattern != nullptr && pLastPattern->dirPatternNum != dirPatternNum)
        {
            pLastPattern = pLastPattern->parent;
        }

        return pLastPattern;
    }

//==================================================================================================
//    GraphicKeyCard class function implementation
//==================================================================================================

    GraphicKeyCard::GraphicKeyCard(int16_t keyCardLength, int16_t keyCardWidth):
        PatternForPossibleCombinations(),
        m_keyCardLength(keyCardLength),
        m_keyCardWidth(keyCardWidth),
        m_keyCardSize(keyCardLength*keyCardWidth)
    {
         ///
    }
    
    GraphicKeyCard::~GraphicKeyCard()
    {
        ///
    }

    int16_t GraphicKeyCard::getKeyCardLength()
    {
        return m_keyCardLength;
    }

    int16_t GraphicKeyCard::getKeyCardWidth()
    {
        return m_keyCardWidth;
    }

    int16_t GraphicKeyCard::getKeyCardSize()
    {
        return m_keyCardSize;
    }

    bool GraphicKeyCard::SetFieldKeyCard(int16_t keyCardLength, int16_t keyCardWidth)
    {
        m_keyCardLength = keyCardLength;
        m_keyCardWidth = keyCardWidth;
        m_keyCardSize = m_keyCardLength * m_keyCardWidth;
        return true;
    }

    uint16_t GraphicKeyCard::lookPosition(int16_t curPos, eDirection dirPatternNum)
    {
        if(curPos > m_keyCardSize - 1)
            return -1;
        if(dirPatternNum < 1 || (uint16_t)dirPatternNum > m_PatternCount - 1)
            return -1;

        struct sPatternForPossibleCombinations* pLastPattern = GetPattern(dirPatternNum);

        if(pLastPattern == nullptr)
            return -1;

        int16_t numCurLine = curPos / m_keyCardWidth;              // get current line
        numCurLine += pLastPattern->upDown;                        //get the desired line
        if(numCurLine < 0 || numCurLine > m_keyCardWidth - 1)
            return -1;

        int16_t numCurColumn = curPos % m_keyCardLength;           // get current column
        numCurColumn += pLastPattern->leftRigth;                   //get the desired column
        if(numCurColumn < 0 || numCurColumn > m_keyCardLength -1)
            return -1;

        uint16_t res = numCurLine * m_keyCardLength + numCurColumn;

        return res;
    }

//==================================================================================================
//    GraphicKey class function implementation
//==================================================================================================

    GraphicKey::GraphicKey()
    {
        ///
    }

    GraphicKey::~GraphicKey()
    {
        ///
    }

    uint16_t GraphicKey::countCodes(char start, int16_t length)
    {
        if((start < 'A' && start > 'I')) //(start < 'a' && start > 'i')
            return 0;

        if(length == 0 || length > m_keyCardSize)
            return 0;

        int16_t pos = (start - (char)'A');

        if(pos >= m_keyCardSize)
            return 0;

        length -= 1U;

        struct sDraftTree draftTree = { nullptr, pos, START, length};

        uint16_t res = counterOfSuccess(&draftTree);

        return res;
    }

    uint16_t GraphicKey::counterOfSuccess(struct sDraftTree* pDraftTree)
    {
        uint16_t countOfSuccess = 0;


        //limit the check. no START direction
        for(int16_t pattern = 1; pattern < m_PatternCount; pattern ++)
        {
            int16_t unocPosition = turnDirAndCheck(pDraftTree, (eDirection)pattern);
            if(unocPosition == -1)
                continue;

            if(pDraftTree->numberToFinish > 1)
            {
                int16_t length = pDraftTree->numberToFinish - 1U;
                struct sDraftTree newDraft = { pDraftTree, unocPosition, (eDirection)pattern, length};
                countOfSuccess += counterOfSuccess(&newDraft);
            }
            else
                countOfSuccess ++;
        }

        return countOfSuccess;
    }

    int16_t GraphicKey::turnDirAndCheck(struct sDraftTree* pDraftTree, eDirection pattern)
    {
        int16_t newPos = -1;

        newPos = lookPosition(pDraftTree->pos, pattern);

        //position is out of the table
        if(newPos <= -1 || newPos >= m_keyCardSize)
            return -1;


        struct sDraftTree* pDraftTreeParent = pDraftTree->parent;

        while(pDraftTreeParent != nullptr)
        {
            if(pDraftTreeParent->pos == newPos) //position exist and selected
            {
                // try to look beyond this point which is already occupied
                // WARNING : THIS METHOD SHOULD STOP WHEN IT BREAKS INTO LIMITS
                // OR FINDS AN EMPTY POSITION. It doesn't break the rules :)
                int16_t length = pDraftTree->numberToFinish - 1U;
                struct sDraftTree testDraft = { pDraftTree, newPos, pattern, length};
                
                newPos = turnDirAndCheck(&testDraft, pattern);
                break;
            }
            pDraftTreeParent = pDraftTreeParent->parent;
        }

        return newPos;
    }    
//}
