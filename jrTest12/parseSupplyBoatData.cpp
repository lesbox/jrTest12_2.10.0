#include "BehaviourManager.h"

bool BehaviourManager::parseSupplyBoatData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseSupplyBoatData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseSupplyBoatData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	QJsonObject supplyBoatData1 = jsonContent.object();

	if (true == getErrorInfo(supplyBoatData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (supplyBoatData1.contains("updateTaskVo")) {
		if (!supplyBoatData1["updateTaskVo"].isArray()) {
			errorManager.pushErrorInfo("updateTaskVo");
			errorManager.pushErrorInfo("supplyBoatData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = supplyBoatData1["updateTaskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("supplyBoatData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("supplyBoatData1");
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

	if (!supplyBoatData1.contains("shipVO") || !supplyBoatData1["shipVO"].isObject()) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("supplyBoatData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject shipVo = supplyBoatData1["shipVO"].toObject();
		MiniNormalShipInformation shipTemp;

		if (false == shipTemp.fromQJsonObject(shipVo, errorManager)) {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("supplyBoatData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
			return false;
		}

		jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
	}

	if (!supplyBoatData1.contains("userVo") || !supplyBoatData1["userVo"].isObject()) {
		errorManager.pushErrorInfo("userVo");
		errorManager.pushErrorInfo("supplyBoatData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject userVo = supplyBoatData1["userVo"].toObject();

		if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userVo, errorManager)) {
			errorManager.pushErrorInfo("userVo");
			errorManager.pushErrorInfo("supplyBoatData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
			return false;
		}
	}

	handleSupplyBoatData1();
	emit(behaviourComplete());
	return true;
}