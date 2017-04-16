#include "BehaviourManager.h"

bool BehaviourManager::parseCreateFleetData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCreateFleetData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCreateFleetData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	QJsonObject createFleetData1 = jsonContent.object();

	if (true == getErrorInfo(createFleetData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!createFleetData1.contains("fleetVo") || !createFleetData1["fleetVo"].isArray()) {
		errorManager.pushErrorInfo("fleetVo");
		errorManager.pushErrorInfo("createFleetData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray fleetList = createFleetData1["fleetVo"].toArray();
		MiniNormalFleetInformation fleetTemp;

		for (int count = 0; count < fleetList.size(); count++) {
			if (!fleetList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("createFleetData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			if (false == fleetTemp.fromQJsonObject(fleetList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("createFleetData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.fleetVo.insert(fleetTemp.id, fleetTemp);
		}
	}

	if (!createFleetData1.contains("shipVO") || !createFleetData1["shipVO"].isArray()) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("createFleetData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userShipList = createFleetData1["userShipVO"].toArray();
		MiniNormalShipInformation shipTemp;

		for (int count = 0; count < userShipList.size(); count++) {
			if (!userShipList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("userShipVO");
				errorManager.pushErrorInfo("createFleetData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			if (false == shipTemp.fromQJsonObject(userShipList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("userShipVO");
				errorManager.pushErrorInfo("createFleetData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
		}
	}

	handleCreateFleetData1();
	emit(behaviourComplete());
	return true;
}