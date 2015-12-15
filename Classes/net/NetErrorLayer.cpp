

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

    if (server_addr=="localhost") {
        m_server_addr->setString("192.168.0.");
    }
    else{
        m_server_addr->setString(server_addr);
    }

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

    m_server_addr = static_cast<TextField*>( root->getChildByName("server_addr") );

	return root;
}


void NetErrorLayer::onClickRetry(Ref* sender)
{
    server_addr = m_server_addr->getString();

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



