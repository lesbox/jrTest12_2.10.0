#include "BehaviourManager.h"

bool BehaviourManager::sendCreateFleetRequest1() {
	currentRequestId = RequestId::CreateFleetRequest1;

	CreateFleetBehaviourParameter createFleetBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<CreateFleetBehaviourParameter>();

	QString urlTemp = QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/instantFleet/") + QString::number(createFleetBehaviourParameterTemp.fleetId) + QString("/[");
	for (int count = 0; count < createFleetBehaviourParameterTemp.shipIdList.size(); count++) {
		if (count != createFleetBehaviourParameterTemp.shipIdList.size() - 1) {
			urlTemp += QString::number(createFleetBehaviourParameterTemp.shipIdList[count]) + QString(",");
		}
		else {
			urlTemp += QString::number(createFleetBehaviourParameterTemp.shipIdList[count]);
		}
	}
	urlTemp += QString("]/");

	buildRequest(urlTemp);

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCreateFleetData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);
	return true;
}