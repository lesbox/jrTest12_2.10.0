#include "BehaviourManager.h"

bool BehaviourManager::sendInstantRepairMultiShipRequest1() {
	currentRequestId = RequestId::InstantRepairMultiShipRequest1;

	InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<InstantRepairMultiShipBehaviourParameter>();

	QString urlTemp = QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/instantRepairShips/[");
	for (int count = 0; count < instantRepairMultiShipBehaviourParameterTemp.shipIdList.size(); count++) {
		if (count != instantRepairMultiShipBehaviourParameterTemp.shipIdList.size() - 1) {
			urlTemp += QString::number(instantRepairMultiShipBehaviourParameterTemp.shipIdList[count]) + QString(",");
		}
		else {
			urlTemp += QString::number(instantRepairMultiShipBehaviourParameterTemp.shipIdList[count]);
		}
	}
	urlTemp += QString("]/");

	buildRequest(urlTemp);

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseInstantRepairMultiShipData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}