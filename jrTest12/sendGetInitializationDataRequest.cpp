#include "BehaviourManager.h"

bool BehaviourManager::sendGetInitializationDataRequest1() {
	currentRequestId = RequestId::GetInitializationDataRequest1;

	buildRequest(QString("http://version.jr.moefantasy.com/index/getInitConfigs/&market=2&channel=0&version=2.10.0"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseGetInitializationDataData7()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}