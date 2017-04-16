#include "BehaviourManager.h"

bool BehaviourManager::sendCheckSpoilsShopRequest1() {
	currentRequestId = RequestId::CheckSpoilsShopRequest1;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/shop/getSpoilsShopList"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCheckSpoilsShopData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}