#include "BehaviourManager.h"

bool BehaviourManager::sendGetTaskAwardRequest1() {
	currentRequestId = RequestId::GetInitializationDataRequest1;

	GetTaskAwardBehaviourParameter getTaskAwardBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<GetTaskAwardBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/task/getAward/") + QString::number(getTaskAwardBehaviourParameterTemp.taskId) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseGetTaskAwardData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}