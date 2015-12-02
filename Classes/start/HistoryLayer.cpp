

#include "HistoryLayer.h"
#include "GameSceneMgr.h"
#include "JigToast.h"
#include "CacheGif.h"
#include "InstantGif.h"
#include "PlayInitMsg.h"
#include "PlayManager.h"
#include "PaymentMgr.h"
#include "lib4cc3x.h"

class GifWidget : public JigGridCell
{
public:
    static GifWidget* create(int level, int sub_level)
    {
        GifWidget* self = new GifWidget();
        self->init();
        self->autorelease();
        
        const Size selfSize(110, 110);

        Sprite* sp = Sprite::create("res/back3.png");
        sp->setScale(selfSize.width/96, selfSize.height/64);
        sp->setPosition(selfSize/2);
        self->addChild(sp);

        string file = sstr("jigsaw%d/pic%02d.gif", level, sub_level);
        GifBase* gif = CacheGif::create( FileUtils::getInstance()->fullPathForFilename(file).c_str() );
        const Size content = gif->getContentSize();
        gif->setScale( 100/content.width );
        gif->setPosition(selfSize/2);
        self->addChild(gif);

        self->setContentSize( selfSize );

        self->Level = level;
        self->SubLevel = sub_level;

        return self;
    }

    int Level;
    int SubLevel;
};

struct PayResult
{
    HistoryLayer* layer;
    void onPayCallback(bool succeed)
    {
        if (!succeed) {
            JigToast::show("pay_fail");
        }
        else{
            JigToast::show("pay_succeed");
            DBRecord record = DBRecord::readby_level(1);
            if (record.sub_level<0) {
                record.sub_level = 0;
                record.write();
                if(layer){
                    layer->m_record.at(1) = record;
                    layer->initLevel(1);
                    layer->initPayment();
                }
            }
        }

        if(layer){
            layer->m_payResult = nullptr;
        }
        delete this;
    }
};

HistoryLayer::HistoryLayer()
:m_payResult(nullptr)
{

}

HistoryLayer::~HistoryLayer()
{

}

bool HistoryLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

    for (int i=0; i<2; ++i)
    {
        m_level.push_back( DBMainLevel::readby_level(i) );
        m_record.push_back( DBRecord::readby_level(i) );
    }

    for (int i=0; i<2; ++i)
    {
        m_title.at(i)->setString( m_level.at(i).Description );
        initLevel( i );
    }

    initPayment();

	return true;
}

Node* HistoryLayer::load_csd()
{
	Node* root = CSLoader::createNode("History.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Return") );
	btn->addClickEventListener( std::bind(&HistoryLayer::onClickReturn, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Button_2") );
	btn->addClickEventListener( std::bind(&HistoryLayer::onClickButton_2, this, placeholders::_1) );

    btn = static_cast<Button*>( root->getChildByName("Pay") );
    btn->addClickEventListener( std::bind(&HistoryLayer::onClickPay, this, placeholders::_1) );
    m_btn_pay = btn;

    m_pview.resize(2);
    m_pview.at(0) = JigGrid::create(root->getChildByName("pv0"), this);
//    static_cast<PageView*>(root->getChildByName("pv0"))->addChild(m_pview.at(0));
    m_pview.at(1) = JigGrid::create(root->getChildByName("pv1"), this);
//    static_cast<PageView*>(root->getChildByName("pv1"))->addChild(m_pview.at(1));

    m_title.resize(2);
	m_title.at(0) = static_cast<Text*>(root->getChildByName("title0"));
	m_title.at(1) = static_cast<Text*>(root->getChildByName("title1"));

    m_page.resize(2);
    m_page.at(0) = static_cast<Text*>(root->getChildByName("page0"));
    m_page.at(1) = static_cast<Text*>(root->getChildByName("page1"));

	return root;
}


void HistoryLayer::onClickReturn(Ref* sender)
{
    GameSceneMgr::inst().replace(kStartScene);
}

void HistoryLayer::onClickPay(Ref* sender)
{
    if(m_payResult)
    {
        JigToast::show("has_paid");
        return;
    }

    m_payResult = new PayResult();
    m_payResult->layer = this;

    PaymentMgr::inst().setPayCallback( std::bind(&PayResult::onPayCallback, m_payResult, placeholders::_1) );
    PaymentMgr::inst().pay(100);
}

void HistoryLayer::onClickButton_2(Ref* sender)
{
    JigToast::show("iamsplit");
}

void HistoryLayer::onClickPageItem(Ref* sender)
{
    GifWidget* wid = static_cast<GifWidget*>(sender);

    DBMainLevel level = DBMainLevel::readby_level( wid->Level );
    PlayInitMsg msg;
    msg.set_main_level( wid->Level );
    msg.set_start_level( wid->SubLevel );
    msg.set_level_count( level.Count );
    msg.set_rotable( level.Rotable );
    PlayManager::inst().enterGame(msg);
}

void HistoryLayer::initLevel(int level)
{
    m_pview.at(level)->setTag( level );

    m_pview.at(level)->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
    m_pview.at(level)->reset(2, 3);
}

void HistoryLayer::initPayment()
{
//    onClickPay(nullptr);
    m_btn_pay->setVisible( false );
    m_pview.at(1)->setVisible( true );

//    m_btn_pay->setVisible( m_record.at(1).sub_level<0 );
//    m_pview.at(1)->setVisible( !m_btn_pay->isVisible() );
}

JigGridCell* HistoryLayer::tableCellAtIndex(JigGrid *table, ssize_t idx)
{
    const int level = table->getTag();

    GifWidget* gif = GifWidget::create( level, idx );

    return gif;
}

ssize_t HistoryLayer::numberOfCellsInJigGrid(JigGrid *table)
{
    const int index = table->getTag();
    if (index!=0 && index!=1)
        return 0;

    return m_record.at(index).sub_level+1;
}

void HistoryLayer::tableCellTouched(JigGrid* table, JigGridCell* cell)
{
    GifWidget* wid = dynamic_cast<GifWidget*>(cell);

    DBMainLevel level = DBMainLevel::readby_level( wid->Level );
    PlayInitMsg msg;
    msg.set_main_level( wid->Level );
    msg.set_start_level( wid->SubLevel );
    msg.set_level_count( level.Count );
    msg.set_rotable( level.Rotable );
    PlayManager::inst().enterGame(msg);
}