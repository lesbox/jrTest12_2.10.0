#include "BehaviourManager.h"

bool BehaviourManager::sendPveWarRequest1() {
	currentRequestId = RequestId::PveWarRequest1;

	PveWarBehaviourParameter pveWarBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<PveWarBehaviourParameter>();
	
	if (1 != checkFleetBrokenStatus(pveWarBehaviourParameterTemp.fleetId)) {
		emit(outputLog(0, "fleet broken status error"));
		return false;
	}

	dynamicParameters.currentPveWarInfo.pveWarInfo = pveWarBehaviourParameterTemp;
	dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter = dynamicParameters.currentPveWarInfo.pveWarInfo.routeInfo.begin();
	dynamicParameters.collectShip_205SkipFailedCount = 0;

	QByteArray Content = (QString("pve_level=") + QString::number(pveWarBehaviourParameterTemp.pveChapter) + QString("&pid=") + QString::number(generatePid())).toUtf8();
	
	QMap<QByteArray, QByteArray> extraRawHeader;
	extraRawHeader.insert("Content-Type", "application/x-www-form-urlencoded");
	extraRawHeader.insert("Content-Length", QString::number(Content.length()).toUtf8());

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/cha11enge/") + QString::number(pveWarBehaviourParameterTemp.pveId) + QString("/") + QString::number(pveWarBehaviourParameterTemp.fleetId) + QString("/0/"), true, true, extraRawHeader);

	networkReply = networkManager->post(*request, Content);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest2() {
	currentRequestId = RequestId::PveWarRequest2;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/newNext/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData2()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest3(){
	currentRequestId = RequestId::PveWarRequest3;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/spy/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData3()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest4() {
	currentRequestId = RequestId::PveWarRequest4;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/deal/") + QString::number(dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId) + QString("/") + QString::number(dynamicParameters.currentPveWarInfo.pveWarInfo.fleetId) + QString("/") + QString::number(dynamicParameters.currentPveWarInfo.pveWarNodeList.last().formation) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData4()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest5() {
	currentRequestId = RequestId::PveWarRequest5;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/getWarResult/") + QString::number(dynamicParameters.currentPveWarInfo.pveWarNodeList.last().isNightWar) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData5()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest6() {
	currentRequestId = RequestId::PveWarRequest6;

	PveWarBehaviourParameter pveWarBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<PveWarBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/active/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData6()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest7() {
	currentRequestId = RequestId::PveWarRequest7;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData7()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest8() {
	currentRequestId = RequestId::PveWarRequest8;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData8()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendPveWarRequest9() {
	currentRequestId = RequestId::PveWarRequest9;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/SkipWar/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parsePveWarData9()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}