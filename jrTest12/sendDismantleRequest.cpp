#include "BehaviourManager.h"

bool BehaviourManager::sendDismantleRequest1() {
	currentRequestId = RequestId::DismantleRequest1;

	DismantleBehaviourParameter DismantleBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<DismantleBehaviourParameter>();
	
	QString urlTemp = QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/dock/dismantleBoat/[");
	for (int count = 0; count < DismantleBehaviourParameterTemp.dismantleShipIdList.size(); count++) {
		if (count != DismantleBehaviourParameterTemp.dismantleShipIdList.size() - 1) {
			urlTemp += QString::number(DismantleBehaviourParameterTemp.dismantleShipIdList[count]) + QString(",");
		}
		else {
			urlTemp += QString::number(DismantleBehaviourParameterTemp.dismantleShipIdList[count]);
		}
	}
	if (DismantleBehaviourParameterTemp.isDismantleEquipment == false) {
		urlTemp += QString("]/0/");
	}
	else {
		urlTemp += QString("]/1/");
	}
	
	buildRequest(urlTemp);

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseDismantleData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}