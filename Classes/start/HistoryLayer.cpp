

#include "HistoryLayer.h"
#include "GameSceneMgr.h"
#include "JigToast.h"
#include "CacheGif.h"
#include "InstantGif.h"
#include "PlayInitMsg.h"
#include "PlayManager.h"
#include "PaymentMgr.h"

class GifWidget : public Button
{
public:
    static GifWidget* create(int level, int sub_level)
    {
        GifWidget* self = new GifWidget();
        self->init();
        self->autorelease();
        self->ignoreContentAdaptWithSize(false);

        Sprite* sp = Sprite::create("res/back3.png");
        sp->setScale(106.0f/96, 106.0f/64);
        sp->setPosition(Point(50,50));
        self->addChild(sp);

        string file = sstr("jigsaw%d/pic%02d.gif", level, sub_level);
        GifBase* gif = CacheGif::create( FileUtils::getInstance()->fullPathForFilename(file).c_str() );
        gif->setAnchorPoint(Point::ZERO);
        const Size content = gif->getContentSize();
        gif->setScale( 100/content.width );

        self->addChild(gif);
        self->setContentSize( Size(100,100) );
        self->setAnchorPoint(Point::ZERO);



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
    m_pview.at(0) = static_cast<PageView*>(root->getChildByName("pv0"));
    m_pview.at(1) = static_cast<PageView*>(root->getChildByName("pv1"));

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
    m_pview.at(level)->addEventListener( std::bind(&HistoryLayer::onPageCallback, this, placeholders::_1, placeholders::_2));

    CallFunc* load = CallFunc::create([=](){
        lazyInitLevel(level);
    });

//    Sequence* tmp = Sequence::create(load, DelayTime::create(0.5), NULL);

    Repeat* rep = Repeat::create(load, m_record.at(level).sub_level+1+1);

    CallFunc* end = CallFunc::create([=](){
        onPageCallback( m_pview.at(level), PageView::EventType::TURNING );
    });

    Sequence* seq = Sequence::create( rep, end, NULL );

    this->runAction(seq);
}

void HistoryLayer::lazyInitLevel(int level)
{
    PageView* pv = m_pview.at(level);
    int has_loaded = getPageItemCount(pv);
    CCASSERT(has_loaded<=m_level.at(level).Count, "");
    if (has_loaded<=m_record.at(level).sub_level)
    {
        GifWidget* gif = GifWidget::create( level, has_loaded );

        const int page_count = 6;
        const int page = has_loaded/page_count;
        const int r = (has_loaded%6)/3;
        const int c = (has_loaded%6)%3;

        gif->setPosition( Point(c*130+20, (1-r)*140+30) );

        gif->addClickEventListener( std::bind(&HistoryLayer::onClickPageItem, this, placeholders::_1) );

        pv->addWidgetToPage(gif, page, true);
    }
}

int HistoryLayer::getPageItemCount(PageView* pview)
{
    int ret = 0;
    const Vector<Layout*>& pages = pview->getPages();
    for (auto it = pages.begin(); it != pages.end(); ++it)
    {
        ret += (*it)->getChildrenCount();
    }
    return ret;
}

void HistoryLayer::onPageCallback(Ref* page, PageView::EventType evt)
{
    PageView* pv = static_cast<PageView*>(page);
    const int index = pv->getTag();
    m_page.at( index )->setString( sstr("%d/%d", pv->getCurPageIndex()+1, (int)pv->getPages().size()) );
}

void HistoryLayer::initPayment()
{
//    onClickPay(nullptr);
    m_btn_pay->setVisible( false );
    m_pview.at(1)->setVisible( true );

//    m_btn_pay->setVisible( m_record.at(1).sub_level<0 );
//    m_pview.at(1)->setVisible( !m_btn_pay->isVisible() );
}


