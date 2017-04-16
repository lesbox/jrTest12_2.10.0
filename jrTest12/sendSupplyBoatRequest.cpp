#include "BehaviourManager.h"

bool BehaviourManager::sendSupplyBoatRequest1() {
	currentRequestId = RequestId::SupplyBoatRequest1;

	SupplyBoatBehaviourParameter supplyBoatBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<SupplyBoatBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/supply/") + QString::number(supplyBoatBehaviourParameterTemp.shipId) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseSupplyBoatData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}