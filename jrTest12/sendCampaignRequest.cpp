#include "BehaviourManager.h"

bool BehaviourManager::sendCampaignRequest1() {
	currentRequestId = RequestId::CampaignRequest1;

	CampaignBehaviourParameter campaignBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<CampaignBehaviourParameter>();

	dynamicParameters.currentCampaignInfo.campaignInfo = campaignBehaviourParameterTemp;

	for (int count = 0; count < dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet.size(); count++) {
		if (4 == getBrokenStatus(dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count])) {
			emit(outputLog(0, "fleet broken status error"));
			return false;
		}
	}

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/spy/") + QString::number(dynamicParameters.currentCampaignInfo.campaignInfo.campaignId) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCampaignData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendCampaignRequest2() {
	currentRequestId = RequestId::CampaignRequest2;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/challenge/") + QString::number(dynamicParameters.currentCampaignInfo.campaignInfo.campaignId) + QString("/") + QString::number(dynamicParameters.currentCampaignInfo.campaignNode.formation) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCampaignData2()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendCampaignRequest3() {
	currentRequestId = RequestId::CampaignRequest3;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/getWarResult/") + QString::number(dynamicParameters.currentCampaignInfo.campaignNode.isNightWar) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCampaignData3()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendCampaignRequest4() {
	currentRequestId = RequestId::CampaignRequest4;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/active/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCampaignData4()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendCampaignRequest5() {
	currentRequestId = RequestId::CampaignRequest5;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCampaignData5()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendCampaignRequest6() {
	currentRequestId = RequestId::CampaignRequest6;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseCampaignData6()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}