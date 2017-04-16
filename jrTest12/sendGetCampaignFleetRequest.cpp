#include "BehaviourManager.h"

bool BehaviourManager::sendGetCampaignFleetRequest1() {
	currentRequestId = RequestId::GetCampaignFleetRequest1;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/getFleet/") + QString::number(dynamicParameters.currentCampaignInfo.campaignInfo.campaignId) + QString("/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseGetCampaignFleetData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}