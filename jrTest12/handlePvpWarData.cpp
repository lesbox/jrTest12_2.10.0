#include "BehaviourManager.h"

bool BehaviourManager::handlePvpWarData1() {
	emit(outputLog(0, "start pvp war"));

	dynamicParameters.currentPvpWarInfo.pvpWarNode.formation = 1;
	sendPvpWarRequest2();
	return true;
}

bool BehaviourManager::handlePvpWarData2() {
	emit(outputLog(0, "start day war"));

	qsrand(QDateTime::currentDateTimeUtc().toTime_t());
	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	timerTemp.start(13000 + (qrand() % 6000));
	eventloop.exec();

	dynamicParameters.currentPvpWarInfo.pvpWarNode.isNightWar = dynamicParameters.currentPvpWarInfo.pvpWarNode.warReport.canDoNightWar;
	sendPvpWarRequest3();
	return true;
}

bool BehaviourManager::handlePvpWarData3() {
	if (dynamicParameters.currentPvpWarInfo.pvpWarNode.isNightWar != 0) {
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

	sendPvpWarRequest4();
	return true;
}

bool BehaviourManager::handlePvpWarData4() {
	sendPvpWarRequest5();
	return true;
}

bool BehaviourManager::handlePvpWarData5() {
	sendPvpWarRequest6();
	return true;
}

bool BehaviourManager::handlePvpWarData6() {
	sendPvpWarRequest7();
	return true;
}

bool BehaviourManager::handlePvpWarData7() {
	return true;
}