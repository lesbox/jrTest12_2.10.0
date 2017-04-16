#include "BehaviourManager.h"

bool BehaviourManager::sendGetLoginAwardRequest1() {
	currentRequestId = RequestId::GetLoginAwardRequest1;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/active/getLoginAward/c3ecc6250c89e88d83832e3395efb973/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseGetLoginAwardData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}