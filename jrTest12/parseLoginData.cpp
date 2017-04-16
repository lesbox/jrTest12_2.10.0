#include "BehaviourManager.h"

bool BehaviourManager::parseLoginData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData1 = jsonContent.object();

	if (true == getErrorInfo(loginData1)) {
		return false;
	}

	handleLoginData1();
	return true;
}

bool BehaviourManager::parseLoginData2() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData2");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData2");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData2 = jsonContent.object();

	if (true == getErrorInfo(loginData2)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	jrData.userInfo.userId = (int)getDoubleFromQJsonObject(loginData2, "userId", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("userId");
		errorManager.pushErrorInfo("loginData2");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	handleLoginData2();
	return true;
}

bool BehaviourManager::parseLoginData3() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData3");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData3 = jsonContent.object();

	if (true == getErrorInfo(loginData3)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!loginData3.contains("user") || !loginData3["user"].isObject()) {
		errorManager.pushErrorInfo("user");
		errorManager.pushErrorInfo("loginData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject user = loginData3["user"].toObject();

		if (false == jrData.userInfo.userResourceVo.fromQJsonObject(user, errorManager)) {
			errorManager.pushErrorInfo("user");
			errorManager.pushErrorInfo("loginData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	handleLoginData3();
	return true;
}

bool BehaviourManager::parseLoginData4() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData4");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData4 = jsonContent.object();

	if (true == getErrorInfo(loginData4)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!loginData4.contains("userVo") || !loginData4["userVo"].isObject()) {
		errorManager.pushErrorInfo("userVo");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject userVo = loginData4["userVo"].toObject();

		jrData.userInfo.shipNumTop = (int)getDoubleFromQJsonObject(userVo, "shipNumTop", flagTemp);
		if (flagTemp != 0) {
			errorManager.pushErrorInfo("shipNumTop");
			errorManager.pushErrorInfo("userVo");
			errorManager.pushErrorInfo("loginData4");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userVo, errorManager)) {
			errorManager.pushErrorInfo("userVo");
			errorManager.pushErrorInfo("loginData4");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	jrData.userInfo.userShipVo.clear();
	if (!loginData4.contains("userShipVO") || !loginData4["userShipVO"].isArray()) {
		errorManager.pushErrorInfo("userShipVO");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userShipList = loginData4["userShipVO"].toArray();
		MiniNormalShipInformation shipTemp;

		for (int count = 0; count < userShipList.size(); count++) {
			if (!userShipList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("userShipVO");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == shipTemp.fromQJsonObject(userShipList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("userShipVO");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
		}
	}

	jrData.userInfo.equipmentVo.clear();
	if (!loginData4.contains("equipmentVo") || !loginData4["equipmentVo"].isArray()) {
		errorManager.pushErrorInfo("equipmentVo");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray equipmentList = loginData4["equipmentVo"].toArray();
		MiniEquipmentInformation equipmentTemp;

		for (int count = 0; count < equipmentList.size(); count++) {
			if (!equipmentList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == equipmentTemp.fromQJsonObject(equipmentList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.equipmentVo.insert(equipmentTemp.equipmentCid, equipmentTemp);
		}
	}

	jrData.userInfo.repairDockVo.clear();
	if (!loginData4.contains("repairDockVo") || !loginData4["repairDockVo"].isArray()) {
		errorManager.pushErrorInfo("repairDockVo");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray dockList = loginData4["repairDockVo"].toArray();
		MiniRepairDockInformation dockTemp;

		for (int count = 0; count < dockList.size(); count++) {
			if (!dockList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("repairDockVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == dockTemp.fromQJsonObject(dockList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("repairDockVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.repairDockVo.insert(dockTemp.id, dockTemp);
		}
	}

	jrData.userInfo.fleetVo.clear();
	if (!loginData4.contains("fleetVo") || !loginData4["fleetVo"].isArray()) {
		errorManager.pushErrorInfo("fleetVo");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray fleetList = loginData4["fleetVo"].toArray();
		MiniNormalFleetInformation fleetTemp;

		for (int count = 0; count < fleetList.size(); count++) {
			if (!fleetList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == fleetTemp.fromQJsonObject(fleetList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.fleetVo.insert(fleetTemp.id, fleetTemp);
		}
	}

	jrData.userInfo.packageVo.clear();
	if (!loginData4.contains("packageVo") || !loginData4["packageVo"].isArray()) {
		errorManager.pushErrorInfo("packageVo");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray packageList = loginData4["packageVo"].toArray();
		MiniPackageInformation packageTemp;

		for (int count = 0; count < packageList.size(); count++) {
			if (!packageList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("packageVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == packageTemp.fromQJsonObject(packageList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("packageVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.packageVo.insert(packageTemp.itemCid, packageTemp);
		}
	}

	jrData.userInfo.taskVo.clear();
	if (!loginData4.contains("taskVo") || !loginData4["taskVo"].isArray()) {
		errorManager.pushErrorInfo("taskVo");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray taskList = loginData4["taskVo"].toArray();
		MiniTaskInformation taskTemp;

		for (int count = 0; count < taskList.size(); count++) {
			if (!taskList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("taskVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("taskVo");
				errorManager.pushErrorInfo("loginData4");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.taskVo.insert(taskTemp.taskCid, taskTemp);
		}

		updateTaskAwardStatus();
	}

	if (!loginData4.contains("pveExploreVo") || !loginData4["pveExploreVo"].isObject()) {
		errorManager.pushErrorInfo("pveExploreVo");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject pveExplore = loginData4["pveExploreVo"].toObject();

		if (false == jrData.userInfo.pveExploreVo.fromQJsonObject(pveExplore, errorManager)) {
			errorManager.pushErrorInfo("pveExploreVo");
			errorManager.pushErrorInfo("loginData4");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!loginData4.contains("marketingData") || !loginData4["marketingData"].isObject()) {
		errorManager.pushErrorInfo("marketingData");
		errorManager.pushErrorInfo("loginData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject marketingData = loginData4["marketingData"].toObject();

		if (false == jrData.userInfo.marketingData.fromQJsonObject(marketingData, errorManager)) {
			errorManager.pushErrorInfo("marketingData");
			errorManager.pushErrorInfo("loginData4");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		updateLoginAwardStatus();
	}

	handleLoginData4();
	return true;
}

bool BehaviourManager::parseLoginData5() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData5");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData5 = jsonContent.object();

	if (true == getErrorInfo(loginData5)) {
		return false;
	}

	if (!loginData5.contains("pveNode") || !loginData5["pveNode"].isArray()) {
		errorManager.pushErrorInfo("pveNode");
		errorManager.pushErrorInfo("loginData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray pveNodeList = loginData5["pveNode"].toArray();

		if (false == jrData.userInfo.pveNodeInfo.fromQJsonArray(pveNodeList, errorManager)) {
			errorManager.pushErrorInfo("pveNode");
			errorManager.pushErrorInfo("loginData5");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	handleLoginData5();
	return true;
}

bool BehaviourManager::parseLoginData6() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData6");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (jsonContent.isObject()) {
		QJsonObject loginData6 = jsonContent.object();

		if (true == getErrorInfo(loginData6)) {
			return false;
		}
	}
	else if (jsonContent.isArray()) {

	}
	else {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData6");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	handleLoginData6();
	return true;
}

bool BehaviourManager::parseLoginData7() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData7");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData7");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData7 = jsonContent.object();

	if (true == getErrorInfo(loginData7)) {
		return false;
	}

	if (!loginData7.contains("marketingData") || !loginData7["marketingData"].isObject()) {
		errorManager.pushErrorInfo("marketingData");
		errorManager.pushErrorInfo("loginData7");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject marketingData = loginData7["marketingData"].toObject();

		if (false == jrData.userInfo.marketingData.fromQJsonObject(marketingData, errorManager)) {
			errorManager.pushErrorInfo("marketingData");
			errorManager.pushErrorInfo("loginData7");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		updateLoginAwardStatus();
	}

	handleLoginData7();
	return true;
}

bool BehaviourManager::parseLoginData8() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData8");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData8");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData8 = jsonContent.object();

	if (true == getErrorInfo(loginData8)) {
		return false;
	}

	handleLoginData8();
	return true;
}

bool BehaviourManager::parseLoginData9() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseLoginData9");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseLoginData9");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject loginData9 = jsonContent.object();

	if (true == getErrorInfo(loginData9)) {
		return false;
	}

	if (!loginData9.contains("passInfo") || !loginData9["passInfo"].isObject()) {
		errorManager.pushErrorInfo("passInfo");
		errorManager.pushErrorInfo("loginData9");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject passInfo = loginData9["passInfo"].toObject();

		if (false == jrData.userInfo.passInfo.fromQJsonObject(passInfo, errorManager)) {
			errorManager.pushErrorInfo("passInfo");
			errorManager.pushErrorInfo("loginData9");
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

	handleLoginData9();
	emit(behaviourComplete());
	return true;
}
