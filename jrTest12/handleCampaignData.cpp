#include "BehaviourManager.h"

bool BehaviourManager::handleCampaignData1() {
	emit(outputLog(0, "start campaign"));

	dynamicParameters.currentCampaignInfo.campaignNode.formation = 2;
	sendCampaignRequest2();
	return true;
}

bool BehaviourManager::handleCampaignData2() {
	emit(outputLog(0, "start day war"));

	qsrand(QDateTime::currentDateTimeUtc().toTime_t());
	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	timerTemp.start(13000 + (qrand() % 6000));
	eventloop.exec();

	dynamicParameters.currentCampaignInfo.campaignNode.isNightWar = dynamicParameters.currentCampaignInfo.campaignNode.warReport.canDoNightWar;
	sendCampaignRequest3();
	return true;
}

bool BehaviourManager::handleCampaignData3() {
	if (dynamicParameters.currentCampaignInfo.campaignNode.isNightWar != 0) {
		emit(outputLog(0, "start night war"));
	}
	else {
		emit(outputLog(0, "skip night war"));
	}

	qsrand(QDateTime::currentDateTimeUtc().toTime_t());
	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	if (dynamicParameters.currentPvpWarInfo.pvpWarNode.isNightWar != 0) {
		timerTemp.start(10000 + (qrand() % 4000));
	}
	else {
		timerTemp.start(2000 + (qrand() % 4000));
	}
	eventloop.exec();

	sendCampaignRequest4();
	return true;
}

bool BehaviourManager::handleCampaignData4() {
	sendCampaignRequest5();
	return true;
}

bool BehaviourManager::handleCampaignData5() {
	sendCampaignRequest6();
	return true;
}

bool BehaviourManager::handleCampaignData6() {
	return true;
}