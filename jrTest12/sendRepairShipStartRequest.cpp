#include "BehaviourManager.h"

bool BehaviourManager::sendRepairShipStartRequest1() {
	currentRequestId = RequestId::RepairShipStartRequest1;

	RepairShipStartBehaviourParameter repairShipStartBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<RepairShipStartBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/repair/") + QString::number(repairShipStartBehaviourParameterTemp.shipId) + QString("/") + QString::number(repairShipStartBehaviourParameterTemp.repairDockId) + QString("/"));
	
	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseRepairShipStartData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}