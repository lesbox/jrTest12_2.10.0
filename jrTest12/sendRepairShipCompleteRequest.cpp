#include "BehaviourManager.h"

bool BehaviourManager::sendRepairShipCompleteRequest1() {
	currentRequestId = RequestId::RepairShipCompleteRequest1;

	RepairShipCompleteBehaviourParameter repairShipCompleteBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<RepairShipCompleteBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/repairComplete/") + QString::number(repairShipCompleteBehaviourParameterTemp.repairDockId) + QString("/") + QString::number(repairShipCompleteBehaviourParameterTemp.shipId) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseRepairShipCompleteData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}