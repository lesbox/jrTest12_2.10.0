#include "BehaviourManager.h"

bool BehaviourManager::parsePvpWarData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePvpWarData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePvpWarData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pvpWarData1 = jsonContent.object();

	if (true == getErrorInfo(pvpWarData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!pvpWarData1.contains("enemyVO") || !pvpWarData1["enemyVO"].isObject()) {
		errorManager.pushErrorInfo("enemyVO");
		errorManager.pushErrorInfo("pvpWarData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject enemyVo = pvpWarData1["enemyVO"].toObject();

		if (false == dynamicParameters.currentPvpWarInfo.pvpWarNode.enemyVo.fromQJsonObject(enemyVo, errorManager)) {
			errorManager.pushErrorInfo("enemyVO");
			errorManager.pushErrorInfo("pvpWarData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	handlePvpWarData1();
	return true;
}

bool BehaviourManager::parsePvpWarData2() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePvpWarData2");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePvpWarData2");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pvpWarData2 = jsonContent.object();

	if (true == getErrorInfo(pvpWarData2)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (pvpWarData2.contains("warReport")) {
		if (!pvpWarData2["warReport"].isObject()) {
			errorManager.pushErrorInfo("warReport");
			errorManager.pushErrorInfo("pvpWarData2");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject warReport = pvpWarData2["warReport"].toObject();

			if (false == dynamicParameters.currentPvpWarInfo.pvpWarNode.warReport.fromQJsonObject(warReport, errorManager)) {
				errorManager.pushErrorInfo("warReport");
				errorManager.pushErrorInfo("pvpWarData2");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	handlePvpWarData2();
	return true;
}

bool BehaviourManager::parsePvpWarData3() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePvpWarData3");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePvpWarData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pvpWarData3 = jsonContent.object();

	if (true == getErrorInfo(pvpWarData3)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (pvpWarData3.contains("updateTaskVo")) {
		if (!pvpWarData3["updateTaskVo"].isArray()) {
			errorManager.pushErrorInfo("updateTaskVo");
			errorManager.pushErrorInfo("pvpWarData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = pvpWarData3["updateTaskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("pvpWarData3");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("pvpWarData3");
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

	if (!pvpWarData3.contains("warResult") || !pvpWarData3["warResult"].isObject()) {
		errorManager.pushErrorInfo("warResult");
		errorManager.pushErrorInfo("pvpWarData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject warResult = pvpWarData3["warResult"].toObject();

		if (false == dynamicParameters.currentPvpWarInfo.pvpWarNode.warResult.fromQJsonObject(warResult, errorManager)) {
			errorManager.pushErrorInfo("warResult");
			errorManager.pushErrorInfo("pvpWarData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!pvpWarData3.contains("shipVO")) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("pvpWarData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userShipList;
		MiniNormalShipInformation shipTemp;

		if (pvpWarData3["shipVO"].isObject()) {
			userShipList.append(pvpWarData3["shipVO"].toObject());
		}
		else if (pvpWarData3["shipVO"].isArray()) {
			userShipList = pvpWarData3["shipVO"].toArray();
		}
		else {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("pvpWarData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		for (int count = 0; count < userShipList.size(); count++) {
			if (!userShipList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("pvpWarData3");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == shipTemp.fromQJsonObject(userShipList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("pvpWarData3");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
		}
	}

	handlePvpWarData3();
	return true;
}

bool BehaviourManager::parsePvpWarData4() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePvpWarData4");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePvpWarData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pvpWarData4 = jsonContent.object();

	if (true == getErrorInfo(pvpWarData4)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	dynamicParameters.pvpUserInfoList.clear();//attention
	if (!pvpWarData4.contains("list") || !pvpWarData4["list"].isArray()) {
		errorManager.pushErrorInfo("list");
		errorManager.pushErrorInfo("pvpWarData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userlist = pvpWarData4["list"].toArray();
		MiniPvpUserInformation userInfoTemp;

		for (int count = 0; count < userlist.size(); count++) {
			if (!userlist[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("list");
				errorManager.pushErrorInfo("pvpWarData4");
				errorHandler(errorManager.getErrorInfo());
				return false;
			}

			if (false == userInfoTemp.fromQJsonObject(userlist[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("list");
				errorManager.pushErrorInfo("pvpWarData4");
				errorHandler(errorManager.getErrorInfo());
				return false;
			}

			dynamicParameters.pvpUserInfoList.append(userInfoTemp);
		}

		dynamicParameters.canPvp = false;
		for (int count = 0; count < dynamicParameters.pvpUserInfoList.size(); count++) {
			if (dynamicParameters.pvpUserInfoList[count].resultLevel == 0) {
				dynamicParameters.canPvp = true;
			}
		}
	}

	handlePvpWarData4();
	return true;
}

bool BehaviourManager::parsePvpWarData5() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePvpWarData5");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePvpWarData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pvpWarData5 = jsonContent.object();

	if (true == getErrorInfo(pvpWarData5)) {
		return false;
	}

	if (!pvpWarData5.contains("marketingData") || !pvpWarData5["marketingData"].isObject()) {
		errorManager.pushErrorInfo("marketingData");
		errorManager.pushErrorInfo("pvpWarData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject marketingData = pvpWarData5["marketingData"].toObject();

		if (false == jrData.userInfo.marketingData.fromQJsonObject(marketingData, errorManager)) {
			errorManager.pushErrorInfo("marketingData");
			errorManager.pushErrorInfo("pvpWarData5");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		updateLoginAwardStatus();
	}

	handlePvpWarData5();
	return true;
}

bool BehaviourManager::parsePvpWarData6() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePvpWarData6");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePvpWarData6");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pvpWarData6 = jsonContent.object();

	if (true == getErrorInfo(pvpWarData6)) {
		return false;
	}

	handlePvpWarData6();
	return true;
}

bool BehaviourManager::parsePvpWarData7() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePvpWarData7");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePvpWarData7");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pvpWarData7 = jsonContent.object();

	if (true == getErrorInfo(pvpWarData7)) {
		return false;
	}

	if (!pvpWarData7.contains("passInfo") || !pvpWarData7["passInfo"].isObject()) {
		errorManager.pushErrorInfo("passInfo");
		errorManager.pushErrorInfo("pvpWarData7");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject passInfo = pvpWarData7["passInfo"].toObject();

		if (false == jrData.userInfo.passInfo.fromQJsonObject(passInfo, errorManager)) {
			errorManager.pushErrorInfo("passInfo");
			errorManager.pushErrorInfo("pvpWarData7");
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

	handlePvpWarData7();
	emit(behaviourComplete());
	return true;
}
