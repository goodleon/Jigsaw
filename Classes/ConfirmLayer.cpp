

#include "ConfirmLayer.h"
#include "LanguageMgr.h"

ConfirmLayer* ConfirmLayer::create(const string& lan_id, ConfirmListener ok, ConfirmListener cancel)
{
    ConfirmLayer* ret = new ConfirmLayer();
    ret->init();
    ret->m_ok = ok;
    ret->m_cancel = cancel;
    
    ret->setText(  LanguageMgr::inst().getText(lan_id) );
    
    return ret;
}

ConfirmLayer::ConfirmLayer()
{

}

ConfirmLayer::~ConfirmLayer()
{

}

bool ConfirmLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

Node* ConfirmLayer::load_csd()
{
	Node* root = CSLoader::createNode("confirm.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Cancel") );
	btn->addClickEventListener( std::bind(&ConfirmLayer::onClickCancel, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Ok") );
	btn->addClickEventListener( std::bind(&ConfirmLayer::onClickOk, this, placeholders::_1) );


	m_text = static_cast<Text*>(root->getChildByName("text"));


	return root;
}


void ConfirmLayer::onClickCancel(Ref* sender)
{
    if (m_cancel)
    {
        m_cancel();
    }
    
    JigScene* scene = static_cast<JigScene*>( getParent() );
    scene->dismiss(this);
}
			
void ConfirmLayer::onClickOk(Ref* sender)
{
    if (m_ok)
    {
        m_ok();
    }
    
    JigScene* scene = static_cast<JigScene*>( getParent() );
    scene->dismiss(this);
}

void ConfirmLayer::setText(const string& text)
{
    m_text->setString( text );
}

