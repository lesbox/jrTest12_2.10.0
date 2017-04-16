#include "BehaviourManager.h"

bool BehaviourManager::parseRepairShipStartData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseRepairShipStartData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseRepairShipStartData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject repairShipStartData1 = jsonContent.object();

	if (true == getErrorInfo(repairShipStartData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (repairShipStartData1.contains("updateTaskVo")) {
		if (!repairShipStartData1["updateTaskVo"].isArray()) {
			errorManager.pushErrorInfo("updateTaskVo");
			errorManager.pushErrorInfo("repairShipStartData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = repairShipStartData1["updateTaskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("repairShipStartData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("repairShipStartData1");
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

	if (!repairShipStartData1.contains("userVo") || !repairShipStartData1["userVo"].isObject()) {
		errorManager.pushErrorInfo("userVo");
		errorManager.pushErrorInfo("repairShipStartData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject userVo = repairShipStartData1["userVo"].toObject();

		if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userVo, errorManager)) {
			errorManager.pushErrorInfo("userVo");
			errorManager.pushErrorInfo("repairShipStartData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!repairShipStartData1.contains("repairDockVo") || !repairShipStartData1["repairDockVo"].isArray()) {
		errorManager.pushErrorInfo("repairDockVo");
		errorManager.pushErrorInfo("repairShipStartData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray dockList = repairShipStartData1["repairDockVo"].toArray();
		MiniRepairDockInformation dockTemp;

		for (int count = 0; count < dockList.size(); count++) {
			if (!dockList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("repairDockVo");
				errorManager.pushErrorInfo("repairShipStartData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == dockTemp.fromQJsonObject(dockList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("repairDockVo");
				errorManager.pushErrorInfo("repairShipStartData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.repairDockVo.insert(dockTemp.id, dockTemp);
		}
	}

	if (!repairShipStartData1.contains("shipVO") || !repairShipStartData1["shipVO"].isObject()) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("repairShipStartData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject shipVo = repairShipStartData1["shipVO"].toObject();
		MiniNormalShipInformation shipTemp;

		if (false == shipTemp.fromQJsonObject(shipVo, errorManager)) {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("repairShipStartData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
	}

	handleRepairShipStartData1();
	emit(behaviourComplete());
	return true;
}