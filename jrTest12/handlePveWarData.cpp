#include "BehaviourManager.h"

bool BehaviourManager::handlePveWarData1() {
	emit(outputLog(0, "start pve war"));
	sendPveWarRequest2();
	return true;
}

bool BehaviourManager::handlePveWarData2() {
	qsrand(QDateTime::currentDateTimeUtc().toTime_t());
	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	timerTemp.start(1300);
	eventloop.exec();

	emit(outputLog(0, "next node : " + QString::number(dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId)));
	if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId == 70214) {
		int stop = 1;
	}

	if (!dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().childNodes.contains(dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId)) {
		//test
		if ((*getParentBehaviour()).behaviourType == BehaviourType::StealOilBehaviour) {
			for (int count = 1; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count++) {
				if (4 == getBrokenStatus(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count])) {
					dynamicParameters.stealOilBrokenCount++;
				}
			}
		}
		//
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	else {
		dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter = dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().childNodes.find(dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId);

		if (dynamicParameters.drop500 == 0) {
			if (jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] == 1 || jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] == 2) {
				if (2 <= checkFleetBrokenStatus(staticParameters.activeFleetId) || 3 <= checkFleetSupplyStatus(staticParameters.activeFleetId)) {
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
					emit(behaviourComplete());
					return true;
				}
				else {
					sendPveWarRequest3();
				}
			}
			else {
				dynamicParameters.currentPveWarInfo.pveWarNodeList.last().formation = 1;
				sendPveWarRequest4();
			}
		}
		else {
			if (jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] != 3 && jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] != 4) {
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else {
				dynamicParameters.currentPveWarInfo.pveWarNodeList.last().formation = 1;
				sendPveWarRequest4();
			}
		}
	}

	return true;
}

bool BehaviourManager::handlePveWarData3() {
	if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.canSkip != 0 && dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().canSkip != 0) {
		sendPveWarRequest9();
	}
	else {
		dynamicParameters.currentPveWarInfo.pveWarNodeList.last().formation = dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().defaultFormation;
		if ((*getParentBehaviour()).behaviourType == BehaviourType::StealPantsBehaviour) {
			bool quitFlag = true;
			for (int count = 0; count < dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips.size(); count++) {
				if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips[count].shipCid == 20100003) {
					quitFlag = false;
					break;
				}
			}
			if (quitFlag == true) {
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
				emit(behaviourComplete());
				return true;
			}
		}
		else if ((*getParentBehaviour()).behaviourType == BehaviourType::CompleteTaskBehaviour) {
			if (dynamicParameters.completeTaskShipType != 0) {
				bool quitFlag = true;
				for (int count = 0; count < dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips.size(); count++) {
					if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips[count].type == dynamicParameters.completeTaskShipType) {
						quitFlag = false;
						break;
					}
				}
				if (quitFlag == true) {
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
					emit(behaviourComplete());
					return true;
				}
			}
		}
		else if ((*getParentBehaviour()).behaviourType == BehaviourType::CollectShipBehaviour) {
			int submarineCountTemp = 0;
			for (int count = 0; count < dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips.size(); count++) {
				if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips[count].type == 14) {
					submarineCountTemp++;
					break;
				}
			}
			if (submarineCountTemp > 0) {
				dynamicParameters.currentPveWarInfo.pveWarNodeList.last().formation = 5;
			}
		}
		else if ((*getParentBehaviour()).behaviourType == BehaviourType::TrainShipBehaviour) {
			bool quitFlag = false;
			for (int count = 0; count < dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips.size(); count++) {
				if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.enemyShips[count].type != 14) {
					quitFlag = true;
					break;
				}
			}
			if (quitFlag == true) {
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
				emit(behaviourComplete());
				return true;
			}
		}
		sendPveWarRequest4();
	}
	return true;
}

bool BehaviourManager::handlePveWarData4() {
	emit(outputLog(0, "start day war"));

	qsrand(QDateTime::currentDateTimeUtc().toTime_t());
	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	if (jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] == 1 || jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] == 2) {
		timerTemp.start(13000 + (qrand() % 6000));
	}
	else {
		timerTemp.start(1700 + (qrand() % 400));
	}
	eventloop.exec();

	if (jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] == 1 || jrData.userInfo.pveNodeInfo.nodeInfo[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId] == 2) {
		if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warReport.canDoNightWar != 0 && dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().canDoNightWar != 0) {
			dynamicParameters.currentPveWarInfo.pveWarNodeList.last().isNightWar = 1;
		}
		else {
			dynamicParameters.currentPveWarInfo.pveWarNodeList.last().isNightWar = 0;
		}
		sendPveWarRequest5();
	}
	else {
		//test
		if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId == 20204) {
			emit(outputLog(9, ""));
		}
		else if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId == 30104) {
			emit(outputLog(10, ""));
		}
		else if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId == 40305) {
			emit(outputLog(11, ""));
		}
		//

		if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().pveLevelEnd == 0) {
			if (dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().childNodes.size() != 0) {
				sendPveWarRequest2();
			}
			else {
				//test
				if ((*getParentBehaviour()).behaviourType == BehaviourType::StealAmmoBehaviour) {
					for (int count = 1; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count++) {
						if (4 == getBrokenStatus(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count])) {
							dynamicParameters.stealAmmoBrokenCount++;
						}
					}
				}
				//
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
				emit(behaviourComplete());
				return true;
			}
		}
		else {
			sendPveWarRequest6();
		}
	}

	return true;
}

bool BehaviourManager::handlePveWarData5() {
	if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().isNightWar != 0) {
		if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warResult.resultLevel < 1 || dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warResult.resultLevel > 6) {
			emit(outputLog(0, "start night war, resultLevel error"));
		}
		else {
			emit(outputLog(0, "start night war, resultLevel: " + staticParameters.resultLevelDescriptorList[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warResult.resultLevel - 1]));
		}
	}
	else {
		if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warResult.resultLevel < 1 || dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warResult.resultLevel > 6) {
			emit(outputLog(0, "skip night war, resultLevel error"));
		}
		else {
			emit(outputLog(0, "skip night war, resultLevel: " + staticParameters.resultLevelDescriptorList[dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warResult.resultLevel - 1]));
		}
	}

	qsrand(QDateTime::currentDateTimeUtc().toTime_t());
	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().isNightWar != 0) {
		timerTemp.start(10000 + (qrand() % 4000));
	}
	else {
		timerTemp.start(2000 + (qrand() % 4000));
	}
	eventloop.exec();

	auto test = dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value();

	if (dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().childNodes.size() != 0) {
		int flagTemp = checkFleetBrokenStatus(staticParameters.activeFleetId);
		if (3 <= flagTemp) {
			sendPveWarRequest6();
		}
		else {
			if (dynamicParameters.drop500 == 0) {
				if (2 <= flagTemp || 3 <= checkFleetSupplyStatus(staticParameters.activeFleetId)) {
					bool quitFlag = true;
					for each(int nodeIdTemp in dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().childNodes.keys()) {
						if (jrData.userInfo.pveNodeInfo.nodeInfo[nodeIdTemp] != 1 && jrData.userInfo.pveNodeInfo.nodeInfo[nodeIdTemp] != 2) {
							quitFlag = false;
							break;
						}
					}
					if (quitFlag == false) {
						sendPveWarRequest2();
					}
					else {
						sendPveWarRequest6();
					}
				}
				else {
					sendPveWarRequest2();
				}
			}
			else {
				bool quitFlag = true;
				for each(int nodeIdTemp in dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().childNodes.keys()) {
					if (jrData.userInfo.pveNodeInfo.nodeInfo[nodeIdTemp] == 3 || jrData.userInfo.pveNodeInfo.nodeInfo[nodeIdTemp] == 4) {
						quitFlag = false;
						break;
					}
				}
				if (quitFlag == false) {
					sendPveWarRequest2();
				}
				else {
					sendPveWarRequest6();
				}
			}
		}
	}
	else {
		sendPveWarRequest6();
	}

	return true;
}

bool BehaviourManager::handlePveWarData6() {
	sendPveWarRequest7();
	return true;
}

bool BehaviourManager::handlePveWarData7() {
	sendPveWarRequest8();
	return true;
}

bool BehaviourManager::handlePveWarData8() {
	for (int count = 0; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count ++) {
		if (jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].isLocked == 0) {
			dispatchShip(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]);
		}
	}
	//test
	if ((*getParentBehaviour()).behaviourType == BehaviourType::StealOilBehaviour) {
		for (int count = 1; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count++) {
			if (4 == getBrokenStatus(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count])) {
				dynamicParameters.stealOilBrokenCount++;
			}
		}
	}
	if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId == 50510) {
		emit(outputLog(8, ""));
	}
	//
	return true;
}

bool BehaviourManager::handlePveWarData9() {
	if (dynamicParameters.currentPveWarInfo.pveWarNodeList.last().isSkipSuccess == 1) {
		emit(outputLog(0, "succeed in skipping war"));
		sendPveWarRequest2();
		return true;
	}
	else {
		emit(outputLog(0, "fail in skipping war"));
		if ((*getParentBehaviour()).behaviourType == BehaviourType::CollectShipBehaviour) {
			dynamicParameters.collectShip_205SkipFailedCount++;
			if (dynamicParameters.collectShip_205SkipFailedCount >= 2) {
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
				emit(behaviourComplete());
				return true;
			}
		}

		if (dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().mustSkip == true) {
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RouteError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			dynamicParameters.currentPveWarInfo.pveWarNodeList.last().formation = dynamicParameters.currentPveWarInfo.pveWarInfo.pveNodeIter.value().defaultFormation;
			sendPveWarRequest4();
		}
	}

	return true;
}