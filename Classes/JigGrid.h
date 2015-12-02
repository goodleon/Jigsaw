
#ifndef __JigGrid_H__
#define __JigGrid_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <set>
#include <vector>

using namespace std;
using namespace cocos2d;
using namespace extension;


class JigGrid;
class JigGridCell;

class JigGridDelegate : public ScrollViewDelegate
{
public:
    virtual JigGridCell* tableCellAtIndex(JigGrid *table, ssize_t idx) = 0;
    virtual ssize_t numberOfCellsInJigGrid(JigGrid *table) = 0;

    virtual void tableCellTouched(JigGrid* table, JigGridCell* cell){};
    virtual void tableCellHighlight(JigGrid* table, JigGridCell* cell){};
    virtual void tableCellUnhighlight(JigGrid* table, JigGridCell* cell){};
};

class JigGridCell: public Node
{
public:
    CREATE_FUNC(JigGridCell);

    JigGridCell() {}

    ssize_t getIdx() const
    {
        return _idx;
    }
    void setIdx(ssize_t uIdx)
    {
        _idx = uIdx;
    }

    void reset()
    {
        _idx = CC_INVALID_INDEX;
    }

private:
    ssize_t _idx;
};


class JigGrid : public cocos2d::extension::ScrollView, public ScrollViewDelegate
{
public:

//    enum class VerticalFillOrder
//    {
//        TOP_DOWN,
//        BOTTOM_UP
//    };

//    static JigGrid* create();
//    static JigGrid* create(JigGridDelegate* dataSource, Size size);
//    static JigGrid* create(JigGridDelegate* dataSource, Size size, Node *container);

    static JigGrid* create(Node* parent, JigGridDelegate* delegate);

    JigGrid();
    virtual ~JigGrid();

    void reset(int rows, int cols);
    void reloadData();
    JigGridCell *cellAtIndex(ssize_t idx);

    JigGridDelegate* getDelegate() { return _JigGridDelegate; }
    void setDelegate(JigGridDelegate* pDelegate) { _JigGridDelegate = pDelegate; }

    void updateCellAtIndex(ssize_t idx);

    int totalPage();
    int curPage();

    // Overrides
    virtual void scrollViewDidScroll(ScrollView* view) override;
    virtual void scrollViewDidZoom(ScrollView* view)  override {}
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;

protected:
    bool initWithViewSize(Size size, Node* container = NULL);

    void _updateContentSize();

//    long __indexFromOffset(Vec2 offset);
    long _indexFromOffset(Vec2 offset);
//    Vec2 __offsetFromIndex(ssize_t index);
    Vec2 _offsetFromIndex(ssize_t index);

    void _moveCellOutOfSight(JigGridCell *cell);
    void _setIndexForCell(ssize_t index, JigGridCell *cell);
    void _addCellIfNecessary(JigGridCell * cell);

    Size _getCellSize();

    JigGridCell *_touchedCell;

    std::set<ssize_t>* _indices;

    Vector<JigGridCell*> _cellsUsed;

    JigGridDelegate* _JigGridDelegate;

    Direction _oldDirection;

    bool _isUsedCellsDirty;

    int m_rows;
    int m_cols;
    Size m_emptyBorder;
};

#endif /* __JigGrid_H__ */
