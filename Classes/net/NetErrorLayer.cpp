

#include "NetErrorLayer.h"
#include "Network.h"

NetErrorLayer::NetErrorLayer()
{

}

NetErrorLayer::~NetErrorLayer()
{

}

bool NetErrorLayer::init()
{
	Return_False_If(!Layer::init());

	Node* root = load_csd();
	addChild(root);

	return true;
}

Node* NetErrorLayer::load_csd()
{
	Node* root = CSLoader::createNode("NetError.csb");

	Button* btn = nullptr;

	btn = static_cast<Button*>( root->getChildByName("Retry") );
	btn->addClickEventListener( std::bind(&NetErrorLayer::onClickRetry, this, placeholders::_1) );

	btn = static_cast<Button*>( root->getChildByName("Exit") );
	btn->addClickEventListener( std::bind(&NetErrorLayer::onClickExit, this, placeholders::_1) );

    m_errorMsg = static_cast<Text*>( root->getChildByName("errorMsg") );


	return root;
}


void NetErrorLayer::onClickRetry(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);
//	CCLOG("%s", btn->getName().c_str());
    Request req(proto_check_network_up);
    Network::inst().addRequest(req);
}

void NetErrorLayer::onClickExit(Ref* sender)
{
//	Button* btn = static_cast<Button*>(sender);
//	CCLOG("%s", btn->getName().c_str());
    Director::getInstance()->end();
}

void NetErrorLayer::setErrorMessage(const string& msg)
{
    m_errorMsg->setString(msg);
}

void NetErrorLayer::onMessage(int notify_id, const net_data_t& root)
{
//    if (notify_id==notify_net_error) {
//        setErrorMessage(root["error_msg"].GetString());
//    }
}



