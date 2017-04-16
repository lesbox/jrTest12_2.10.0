#include "BehaviourManager.h"

bool BehaviourManager::sendPveExploreStartRequest1() {
	currentRequestId = RequestId::PveExploreStartRequest1;

	PveExploreStartBehaviourParameter pveExploreStartBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<PveExploreStartBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/explore/start/") + QString::number(pveExploreStartBehaviourParameterTemp.fleetId) + QString("/") + QString::number(pveExploreStartBehaviourParameterTemp.pveExploreId) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveExploreStartData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}