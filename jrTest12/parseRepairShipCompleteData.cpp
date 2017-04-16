#include "BehaviourManager.h"

bool BehaviourManager::parseRepairShipCompleteData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseRepairShipCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseRepairShipCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject repairShipCompleteData1 = jsonContent.object();

	if (true == getErrorInfo(repairShipCompleteData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!repairShipCompleteData1.contains("repairDockVo") || !repairShipCompleteData1["repairDockVo"].isArray()) {
		errorManager.pushErrorInfo("repairDockVo");
		errorManager.pushErrorInfo("repairShipCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray dockList = repairShipCompleteData1["repairDockVo"].toArray();
		MiniRepairDockInformation dockTemp;

		for (int count = 0; count < dockList.size(); count++) {
			if (!dockList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("repairDockVo");
				errorManager.pushErrorInfo("repairShipCompleteData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == dockTemp.fromQJsonObject(dockList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("repairDockVo");
				errorManager.pushErrorInfo("repairShipCompleteData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.repairDockVo.insert(dockTemp.id, dockTemp);
		}

		(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::RepairDockIdle, QVariant());
	}

	if (!repairShipCompleteData1.contains("shipVO") || !repairShipCompleteData1["shipVO"].isObject()) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("repairShipCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject shipVo = repairShipCompleteData1["shipVO"].toObject();
		MiniNormalShipInformation shipTemp;

		if (false == shipTemp.fromQJsonObject(shipVo, errorManager)) {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("repairShipCompleteData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
	}

	handleRepairShipCompleteData1();
	emit(behaviourComplete());
	return true;
}