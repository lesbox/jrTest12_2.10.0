#include "BehaviourManager.h"

bool BehaviourManager::sendPveExploreCompleteRequest1() {
	currentRequestId = RequestId::PveExploreCompleteRequest1;

	PveExploreCompleteBehaviourParameter pveExploreCompleteBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<PveExploreCompleteBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/explore/getResult/") + QString::number(pveExploreCompleteBehaviourParameterTemp.pveExploreId) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveExploreCompleteData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}