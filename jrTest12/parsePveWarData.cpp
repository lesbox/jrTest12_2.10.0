#include "BehaviourManager.h"

bool BehaviourManager::parsePveWarData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData1 = jsonContent.object();

	if (true == getErrorInfo(pveWarData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	dynamicParameters.currentPveWarInfo.pveWarNodeList.clear();
	dynamicParameters.currentPveWarInfo.pveWarNodeList.append(MiniPveWarNodeInformation());

	dynamicParameters.currentPveWarInfo.pveWarNodeList.last().pveLevelEnd = (int)getDoubleFromQJsonObject(pveWarData1, "pveLevelEnd", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("pveLevelEnd");
		errorManager.pushErrorInfo("pveWarData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	handlePveWarData1();
	return true;
}

bool BehaviourManager::parsePveWarData2() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData2");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData2");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData2 = jsonContent.object();

	if (true == getErrorInfo(pveWarData2)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	dynamicParameters.currentPveWarInfo.pveWarNodeList.append(MiniPveWarNodeInformation());

	dynamicParameters.currentPveWarInfo.pveWarNodeList.last().nodeId = (int)getDoubleFromQJsonObject(pveWarData2, "node", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("node");
		errorManager.pushErrorInfo("parsePveWarData2");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	handlePveWarData2();
	return true;
}

bool BehaviourManager::parsePveWarData3() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData3");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData3 = jsonContent.object();

	if (true == getErrorInfo(pveWarData3)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!pveWarData3.contains("enemyVO") || !pveWarData3["enemyVO"].isObject()) {
		errorManager.pushErrorInfo("enemyVO");
		errorManager.pushErrorInfo("pveWarData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject enemyVo = pveWarData3["enemyVO"].toObject();

		if (false == dynamicParameters.currentPveWarInfo.pveWarNodeList.last().enemyVo.fromQJsonObject(enemyVo, errorManager)) {
			errorManager.pushErrorInfo("enemyVO");
			errorManager.pushErrorInfo("pveWarData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	handlePveWarData3();
	return true;
}

bool BehaviourManager::parsePveWarData4() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData4");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData4 = jsonContent.object();

	if (true == getErrorInfo(pveWarData4)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	//battle ship status
	//
	if ((*getParentBehaviour()).behaviourType == BehaviourType::TrainShipBehaviour) {
		int trainingOilTemp = 0;
		int trainingAmmoTemp = 0;
		for (int count = 0; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count++) {
			trainingOilTemp += jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].battlePropsMax.oil;
			trainingAmmoTemp += jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].battlePropsMax.ammo;
		}

		dynamicParameters.trainingOil -= trainingOilTemp / 5;
		dynamicParameters.trainingAmmo -= trainingAmmoTemp / 5;
	}

	if (pveWarData4.contains("userResVo")) {
		if (!pveWarData4["userResVo"].isObject()) {
			errorManager.pushErrorInfo("userResVo");
			errorManager.pushErrorInfo("pveWarData4");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject userResVo = pveWarData4["userResVo"].toObject();

			if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userResVo, errorManager)) {
				errorManager.pushErrorInfo("userResVo");
				errorManager.pushErrorInfo("pveWarData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	dynamicParameters.currentPveWarInfo.pveWarNodeList.last().pveLevelEnd = (int)getDoubleFromQJsonObject(pveWarData4, "pveLevelEnd", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("pveLevelEnd");
		errorManager.pushErrorInfo("pveWarData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	if (pveWarData4.contains("warReport")) {
		if (!pveWarData4["warReport"].isObject()) {
			errorManager.pushErrorInfo("warReport");
			errorManager.pushErrorInfo("pveWarData4");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject warReport = pveWarData4["warReport"].toObject();

			if (false == dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warReport.fromQJsonObject(warReport, errorManager)) {
				errorManager.pushErrorInfo("warReport");
				errorManager.pushErrorInfo("pveWarData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	handlePveWarData4();
	return true;
}

bool BehaviourManager::parsePveWarData5() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData5");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData5 = jsonContent.object();

	if (true == getErrorInfo(pveWarData5)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	bool spoilFlagTemp = false;
	dynamicParameters.currentPveWarInfo.pveWarNodeList.last().spoils = (int)getDoubleFromQJsonObject(pveWarData5, "spoils", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("spoils");
		errorManager.pushErrorInfo("pveWarData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else if (flagTemp == 0) {
		spoilFlagTemp = true;
		dynamicParameters.spoilNum = dynamicParameters.currentPveWarInfo.pveWarNodeList.last().spoils;
	}
	else {
		dynamicParameters.currentPveWarInfo.pveWarNodeList.last().dropSpoils = (int)getDoubleFromQJsonObject(pveWarData5, "dropSpoils", flagTemp);
		if (flagTemp == 1) {
			errorManager.pushErrorInfo("dropSpoils");
			errorManager.pushErrorInfo("pveWarData5");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else if (flagTemp == 0) {
			spoilFlagTemp = true;
			dynamicParameters.spoilNum += dynamicParameters.currentPveWarInfo.pveWarNodeList.last().dropSpoils;
		}
		else {

		}
	}

	if (spoilFlagTemp == true) {
		emit(outputLog(12, QString::number(dynamicParameters.spoilNum) + " / " + QString::number(dynamicParameters.maxSpoilNum)));
		emit(outputLog(0, QString("spoil number : ") + QString::number(dynamicParameters.spoilNum)));
	}

	dynamicParameters.currentPveWarInfo.pveWarNodeList.last().drop500 = (int)getDoubleFromQJsonObject(pveWarData5, "drop500", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("drop500");
		errorManager.pushErrorInfo("pveWarData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else if(flagTemp == 0){
		dynamicParameters.drop500 = dynamicParameters.currentPveWarInfo.pveWarNodeList.last().drop500;
		emit(outputLog(0, "drop500"));
	}

	if (pveWarData5.contains("updateTaskVo")) {
		if (!pveWarData5["updateTaskVo"].isArray()) {
			errorManager.pushErrorInfo("updateTaskVo");
			errorManager.pushErrorInfo("pveWarData5");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = pveWarData5["updateTaskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("pveWarData5");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("pveWarData5");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.taskVo.insert(taskTemp.taskCid, taskTemp);
			}

			updateTaskAwardStatus();
		}
	}

	if (pveWarData5.contains("newShipVO")) {
		if (!pveWarData5["newShipVO"].isArray()) {
			errorManager.pushErrorInfo("newShipVO");
			errorManager.pushErrorInfo("pveWarData5");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray shipVoList = pveWarData5["newShipVO"].toArray();
			MiniNormalShipInformation shipTemp;

			for (int count = 0; count < shipVoList.size(); count++) {
				if (!shipVoList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("newShipVO");
					errorManager.pushErrorInfo("pveWarData5");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == shipTemp.fromQJsonObject(shipVoList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("newShipVO");
					errorManager.pushErrorInfo("pveWarData5");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
				dispatchShip(shipTemp.id);

				if ((*getParentBehaviour()).behaviourType == BehaviourType::CollectShipBehaviour && staticParameters.collectShipShipCidList.contains(shipTemp.shipCid)) {
					dynamicParameters.collectShipSuccessFlag = true;
					emit(outputLog(0, "collect succeed : ") + QString::number(shipTemp.shipCid));
				}

				if (jrData.initInfo.shipCard[shipTemp.shipCid].type == 12) {
					dynamicParameters.trainingOil += jrData.initInfo.shipCard[shipTemp.shipCid].dismantle[2] * 3;
					dynamicParameters.trainingAmmo += jrData.initInfo.shipCard[shipTemp.shipCid].dismantle[3] * 3;
				}
			}
		}
	}

	if (!pveWarData5.contains("warResult") || !pveWarData5["warResult"].isObject()) {
		errorManager.pushErrorInfo("warResult");
		errorManager.pushErrorInfo("pveWarData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject warResult = pveWarData5["warResult"].toObject();

		if (false == dynamicParameters.currentPveWarInfo.pveWarNodeList.last().warResult.fromQJsonObject(warResult, errorManager)) {
			errorManager.pushErrorInfo("warResult");
			errorManager.pushErrorInfo("pveWarData5");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!pveWarData5.contains("shipVO")) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("pveWarData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userShipList;
		MiniNormalShipInformation shipTemp;

		if (pveWarData5["shipVO"].isObject()) {
			userShipList.append(pveWarData5["shipVO"].toObject());
		}
		else if (pveWarData5["shipVO"].isArray()) {
			userShipList = pveWarData5["shipVO"].toArray();
		}
		else {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("pveWarData5");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		for (int count = 0; count < userShipList.size(); count++) {
			if (!userShipList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("pveWarData5");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == shipTemp.fromQJsonObject(userShipList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("pveWarData5");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
		}
	}

	handlePveWarData5();
	return true;
}

bool BehaviourManager::parsePveWarData6() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData6");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData6");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData6 = jsonContent.object();

	if (true == getErrorInfo(pveWarData6)) {
		return false;
	}

	if (!pveWarData6.contains("marketingData") || !pveWarData6["marketingData"].isObject()) {
		errorManager.pushErrorInfo("marketingData");
		errorManager.pushErrorInfo("pveWarData6");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject marketingData = pveWarData6["marketingData"].toObject();

		if (false == jrData.userInfo.marketingData.fromQJsonObject(marketingData, errorManager)) {
			errorManager.pushErrorInfo("marketingData");
			errorManager.pushErrorInfo("pveWarData6");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		updateLoginAwardStatus();
	}

	handlePveWarData6();
	return true;
}

bool BehaviourManager::parsePveWarData7() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData7");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData7");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData7 = jsonContent.object();

	if (true == getErrorInfo(pveWarData7)) {
		return false;
	}

	handlePveWarData7();
	return true;
}

bool BehaviourManager::parsePveWarData8() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData8");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData8");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData8 = jsonContent.object();

	if (true == getErrorInfo(pveWarData8)) {
		return false;
	}

	if (!pveWarData8.contains("passInfo") || !pveWarData8["passInfo"].isObject()) {
		errorManager.pushErrorInfo("passInfo");
		errorManager.pushErrorInfo("pveWarData8");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject passInfo = pveWarData8["passInfo"].toObject();

		if (false == jrData.userInfo.passInfo.fromQJsonObject(passInfo, errorManager)) {
			errorManager.pushErrorInfo("passInfo");
			errorManager.pushErrorInfo("pveWarData8");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		dynamicParameters.canCampaign = false;
		if (jrData.userInfo.passInfo.remainNum > 0) {
			dynamicParameters.canCampaign = true;
		}
	}

	handlePveWarData8();
	emit(behaviourComplete());
	return true;
}

bool BehaviourManager::parsePveWarData9() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveWarData9");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveWarData9");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveWarData9 = jsonContent.object();

	if (true == getErrorInfo(pveWarData9)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	dynamicParameters.currentPveWarInfo.pveWarNodeList.last().isSkipSuccess = (int)getDoubleFromQJsonObject(pveWarData9, "isSuccess", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("isSuccess");
		errorManager.pushErrorInfo("pveWarData9");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	if (pveWarData9.contains("userResVo")) {
		if (!pveWarData9["userResVo"].isObject()) {
			errorManager.pushErrorInfo("userResVo");
			errorManager.pushErrorInfo("pveWarData9");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject userResVo = pveWarData9["userResVo"].toObject();

			if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userResVo, errorManager)) {
				errorManager.pushErrorInfo("userResVo");
				errorManager.pushErrorInfo("pveWarData9");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	handlePveWarData9();
	return true;
}