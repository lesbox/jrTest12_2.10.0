#include "BehaviourManager.h"

bool BehaviourManager::sendSupplyMultiBoatRequest1() {
	currentRequestId = RequestId::SupplyMultiBoatRequest1;

	SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<SupplyMultiBoatBehaviourParameter>();
	
	QString urlTemp = QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/supplyBoats/[");
	
	for (int count = 0; count < supplyMultiBoatBehaviourParameterTemp.shipIdList.size(); count++) {
		if (count != supplyMultiBoatBehaviourParameterTemp.shipIdList.size() - 1) {
			urlTemp += QString::number(supplyMultiBoatBehaviourParameterTemp.shipIdList[count]) + QString(",");
		}
		else {
			urlTemp += QString::number(supplyMultiBoatBehaviourParameterTemp.shipIdList[count]);
		}
	}
	urlTemp += QString("]/0/0/");
	buildRequest(urlTemp);

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseSupplyMultiBoatData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}