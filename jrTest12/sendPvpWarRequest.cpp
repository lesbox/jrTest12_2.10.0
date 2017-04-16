#include "BehaviourManager.h"

bool BehaviourManager::sendPvpWarRequest1() {
	currentRequestId = RequestId::PvpWarRequest1;

	PvpWarBehaviourParameter pvpWarBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<PvpWarBehaviourParameter>();
	
	dynamicParameters.currentPvpWarInfo.pvpWarInfo = pvpWarBehaviourParameterTemp;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pvp/spy/") + QString::number(dynamicParameters.currentPvpWarInfo.pvpWarInfo.fuid) + QString("/") + QString::number(dynamicParameters.currentPvpWarInfo.pvpWarInfo.fleetId) + QString("/0/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePvpWarData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPvpWarRequest2() {
	currentRequestId = RequestId::PvpWarRequest2;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pvp/challenge/") + QString::number(dynamicParameters.currentPvpWarInfo.pvpWarInfo.fuid) + QString("/") + QString::number(dynamicParameters.currentPvpWarInfo.pvpWarInfo.fleetId) + QString("/") + QString::number(dynamicParameters.currentPvpWarInfo.pvpWarNode.formation) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePvpWarData2()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPvpWarRequest3() {
	currentRequestId = RequestId::PvpWarRequest3;
	
	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pvp/getWarResult/") + QString::number(dynamicParameters.currentPvpWarInfo.pvpWarNode.isNightWar) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePvpWarData3()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPvpWarRequest4() {
	currentRequestId = RequestId::PvpWarRequest4;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pvp/getChallengeList/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePvpWarData4()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPvpWarRequest5() {
	currentRequestId = RequestId::PvpWarRequest5;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/active/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePvpWarData5()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPvpWarRequest6() {
	currentRequestId = RequestId::PvpWarRequest6;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePvpWarData6()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPvpWarRequest7() {
	currentRequestId = RequestId::PvpWarRequest7;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePvpWarData7()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}