
#include "JigGrid.h"

JigGrid* JigGrid::create(Node* parent, JigGridDelegate* delegate)
{
    const Size size = parent->getContentSize();

    JigGrid *table = new (std::nothrow) JigGrid();
    table->initWithViewSize(size, nullptr);
    table->autorelease();
    table->setDelegate(delegate);
    table->setColor(Color3B{255,0,0});
    parent->addChild(table);

    return table;
}

void JigGrid::reset(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
    reloadData();
}

bool JigGrid::initWithViewSize(Size size, Node* container/* = nullptr*/)
{
    if (ScrollView::initWithViewSize(size,container))
    {
        CC_SAFE_DELETE(_indices);
        _indices        = new std::set<ssize_t>();
        this->setDirection(Direction::HORIZONTAL);

        ScrollView::setDelegate(this);
        return true;
    }
    return false;
}

JigGrid::JigGrid()
: _touchedCell(nullptr)
, _indices(nullptr)
, _JigGridDelegate(nullptr)
, _oldDirection(Direction::NONE)
, _isUsedCellsDirty(false)
, m_rows(0)
, m_cols(0)
{

}

JigGrid::~JigGrid()
{
    CC_SAFE_DELETE(_indices);
}

void JigGrid::reloadData()
{
    _oldDirection = Direction::NONE;
    m_emptyBorder.setSize(0, 0);

    for(const auto &cell : _cellsUsed) {
        cell->reset();
        if (cell->getParent() == this->getContainer()){
            this->getContainer()->removeChild(cell, true);
        }
    }

    _indices->clear();
    _cellsUsed.clear();

    this->_updateContentSize();
    if (_JigGridDelegate->numberOfCellsInJigGrid(this) > 0)
    {
        this->scrollViewDidScroll(this);
    }
}

JigGridCell *JigGrid::cellAtIndex(ssize_t idx)
{
    if (_indices->find(idx) != _indices->end())
    {
        for (const auto& cell : _cellsUsed)
        {
            if (cell->getIdx() == idx)
            {
                return cell;
            }
        }
    }

    return nullptr;
}

void JigGrid::updateCellAtIndex(ssize_t idx)
{
    if (idx == CC_INVALID_INDEX)
    {
        return;
    }
    long countOfItems = _JigGridDelegate->numberOfCellsInJigGrid(this);
    if (0 == countOfItems || idx > countOfItems-1)
    {
        return;
    }

    JigGridCell* cell = this->cellAtIndex(idx);
    if (!cell) {
        cell = _JigGridDelegate->tableCellAtIndex(this, idx);
    }

    if (m_emptyBorder.equals(Size::ZERO)){
        const Size cellRealSize = cell->getContentSize();
        if (!cellRealSize.equals(Size::ZERO)) {
            m_emptyBorder = (_getCellSize()-cellRealSize)/2;
        }
    }

    this->_setIndexForCell(idx, cell);
    this->_addCellIfNecessary(cell);
}

void JigGrid::_addCellIfNecessary(JigGridCell * cell)
{
    if (cell->getParent() != this->getContainer())
    {
        this->getContainer()->addChild(cell);
    }
    _cellsUsed.pushBack(cell);
    _indices->insert(cell->getIdx());
    _isUsedCellsDirty = true;
}

void JigGrid::_updateContentSize()
{
    const int page = this->totalPage();

    //set content size
    {
        Size size = Size::ZERO;
        switch (this->getDirection())
        {
            case Direction::HORIZONTAL:
                size = Size(page*_viewSize.width, _viewSize.height);
                break;
            default:
                size = Size(_viewSize.width, page*_viewSize.height);
                break;
        }
        this->setContentSize(size);
    }

    if (_oldDirection != _direction)
    {
        if (_direction == Direction::HORIZONTAL)
        {
            this->setContentOffset(Vec2(0,0));
        }
        else
        {
            this->setContentOffset(Vec2(0,this->minContainerOffset().y));
        }
        _oldDirection = _direction;
    }
}

Vec2 JigGrid::_offsetFromIndex(ssize_t index)
{
    const Size cellSize = this->_getCellSize();
    Point ret;
    if (getDirection()==Direction::HORIZONTAL)
    {
        const int page = index/(m_rows*m_cols);
        const int idxInPage = index%(m_rows*m_cols);
        ret.set(idxInPage%m_cols*cellSize.width, _viewSize.height-cellSize.height-idxInPage/m_cols*cellSize.height);
        ret.x += page*_viewSize.width;
    }
    else if (getDirection()==Direction::VERTICAL)
    {
        ret.set(index%m_cols*cellSize.width, index/m_cols*cellSize.height);
        ret.y += (getContentSize().height-_viewSize.height);
    }
    else
    {
        CCASSERT(false, "");
    }

    ret += m_emptyBorder;

    return ret;
}

long JigGrid::_indexFromOffset(Vec2 offset)
{
    const Size cellSize = this->_getCellSize();

    int ret = -1;

    if (getDirection()==Direction::HORIZONTAL)
    {
        offset.x *= -1;
        const int rowInPage = int((_viewSize.height-offset.y)/cellSize.height)%m_rows;
        const int colInPage = int(offset.x/cellSize.width)%m_cols;
        const int curPage = offset.x/_viewSize.width;
        ret = rowInPage*m_cols + colInPage + curPage*m_rows*m_cols;
    }
    else if (getDirection()==Direction::VERTICAL)
    {
        CCASSERT(false, "这段代码是错的");
        offset.y *= -1;
        const int idxInPage = (this->getContentSize().height-offset.y)/cellSize.height;
        const int curPage = (this->getContentSize().height-offset.y)/_viewSize.height;
        ret = idxInPage*m_cols+curPage*m_rows*m_cols;
    }

    const long maxIdx = _JigGridDelegate->numberOfCellsInJigGrid(this) - 1;
    ret = MAX(0, ret);
    return ret>maxIdx ? CC_INVALID_INDEX : ret;
}

void JigGrid::_moveCellOutOfSight(JigGridCell *cell)
{
    _cellsUsed.eraseObject(cell);
    _isUsedCellsDirty = true;

    _indices->erase(cell->getIdx());
    cell->reset();

    if (cell->getParent() == this->getContainer())
    {
        this->getContainer()->removeChild(cell, true);;
    }
}

void JigGrid::_setIndexForCell(ssize_t index, JigGridCell *cell)
{
    cell->setAnchorPoint(Vec2(0, 0));
    cell->setPosition(this->_offsetFromIndex(index));
    cell->setIdx(index);
}

void JigGrid::scrollViewDidScroll(ScrollView* view)
{
    long countOfItems = _JigGridDelegate->numberOfCellsInJigGrid(this);
    if (0 == countOfItems)
    {
        return;
    }

    if (_isUsedCellsDirty)
    {
        _isUsedCellsDirty = false;
        std::sort(_cellsUsed.begin(), _cellsUsed.end(), [](JigGridCell *a, JigGridCell *b) -> bool{
            return a->getIdx() < b->getIdx();
        });
    }

    if(_JigGridDelegate != nullptr) {
        _JigGridDelegate->scrollViewDidScroll(this);
    }

    const ssize_t maxIdx = MAX(countOfItems-1, 0);

    const Point startOffset = this->getContentOffset();
    int startIdx = this->_indexFromOffset(startOffset);
    if (startIdx == CC_INVALID_INDEX)
    {
        startIdx = countOfItems - 1;
    }

    const Point endOffset = getDirection()==Direction::HORIZONTAL ? startOffset-Point(_viewSize.width,0) : startOffset-Point(0,_viewSize.height);
    int endIdx = this->_indexFromOffset(endOffset);
    if (endIdx == CC_INVALID_INDEX)
    {
        endIdx = countOfItems - 1;
    }

    CCASSERT(startIdx>=0 && startIdx<=maxIdx, "");
    CCASSERT(endIdx>=0 && endIdx<=maxIdx, "");
//    int idx = 0;

//    if (!_cellsUsed.empty()) //移除startIdx前面的cell
//    {
//        auto cell = _cellsUsed.at(0);
//        idx = cell->getIdx();
//
//        while(idx < startIdx)
//        {
//            this->_moveCellOutOfSight(cell);
//            if (!_cellsUsed.empty())
//            {
//                cell = _cellsUsed.at(0);
//                idx = cell->getIdx();
//            }
//            else
//            {
//                break;
//            }
//        }
//    }
//    if (!_cellsUsed.empty()) //移除endIdx后面的cell
//    {
//        auto cell = _cellsUsed.back();
//        idx = cell->getIdx();
//
//        while(idx <= maxIdx && idx > endIdx)
//        {
//            this->_moveCellOutOfSight(cell);
//            if (!_cellsUsed.empty())
//            {
//                cell = _cellsUsed.back();
//                idx = cell->getIdx();
//            }
//            else
//            {
//                break;
//            }
//        }
//    }

    for (long i = startIdx; i <= endIdx; i++)
    {
        if (_indices->find(i) != _indices->end())
        {
            continue;
        }
        this->updateCellAtIndex(i);
    }
}

void JigGrid::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (!this->isVisible()) {
        return;
    }

    if (_touchedCell){
        Rect bb = this->getBoundingBox();
        bb.origin = _parent->convertToWorldSpace(bb.origin);

        if (bb.containsPoint(pTouch->getLocation()) && _JigGridDelegate != nullptr)
        {
            _JigGridDelegate->tableCellUnhighlight(this, _touchedCell);
            _JigGridDelegate->tableCellTouched(this, _touchedCell);
        }

        _touchedCell = nullptr;
    }

    ScrollView::onTouchEnded(pTouch, pEvent);
}

bool JigGrid::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    for (Node *c = this; c != nullptr; c = c->getParent())
    {
        if (!c->isVisible())
        {
            return false;
        }
    }

    bool touchResult = ScrollView::onTouchBegan(pTouch, pEvent);

    if(_touches.size() == 1)
    {
        long index;
        Vec2 point;

        point = this->getContainer()->convertTouchToNodeSpace(pTouch);
        point.x *= -1;

        index = this->_indexFromOffset(point);
        if (index == CC_INVALID_INDEX)
        {
            _touchedCell = nullptr;
        }
        else
        {
            _touchedCell  = this->cellAtIndex(index);
        }

        if (_touchedCell && _JigGridDelegate != nullptr)
        {
            _JigGridDelegate->tableCellHighlight(this, _touchedCell);
        }
    }
    else if (_touchedCell)
    {
        if(_JigGridDelegate != nullptr)
        {
            _JigGridDelegate->tableCellUnhighlight(this, _touchedCell);
        }

        _touchedCell = nullptr;
    }

    return touchResult;
}

void JigGrid::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    ScrollView::onTouchMoved(pTouch, pEvent);

    if (_touchedCell && isTouchMoved())
    {
        if(_JigGridDelegate != nullptr)
        {
            _JigGridDelegate->tableCellUnhighlight(this, _touchedCell);
        }
        
        _touchedCell = nullptr;
    }
}

void JigGrid::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    ScrollView::onTouchCancelled(pTouch, pEvent);
    
    if (_touchedCell)
    {
        if(_JigGridDelegate != nullptr)
        {
            _JigGridDelegate->tableCellUnhighlight(this, _touchedCell);
        }
        
        _touchedCell = nullptr;
    }
}

Size JigGrid::_getCellSize()
{
    return Size(_viewSize.width/m_cols, _viewSize.height/m_rows);
}

int JigGrid::totalPage()
{
    const int cellCount = _JigGridDelegate->numberOfCellsInJigGrid(this);
    return cellCount==m_rows*m_cols ? cellCount/(m_rows*m_cols) : cellCount/(m_rows*m_cols)+1;
}

int JigGrid::curPage()
{
    const Point offset = getContentOffset();
    if (getDirection()==Direction::HORIZONTAL)
    {
        return offset.x*-1/_viewSize.width;
    }
    else if (getDirection()==Direction::VERTICAL)
    {
        const float pageOff = getContentSize().height+getContentOffset().y;
        return pageOff/_viewSize.height;
    }
    return 0;
}

