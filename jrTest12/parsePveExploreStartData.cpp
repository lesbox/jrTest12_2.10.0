#include "BehaviourManager.h"

bool BehaviourManager::parsePveExploreStartData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveExploreStartData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveExploreStartData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveExploreStartData1 = jsonContent.object();

	if (true == getErrorInfo(pveExploreStartData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!pveExploreStartData1.contains("pveExploreVo") || !pveExploreStartData1["pveExploreVo"].isObject()) {
		errorManager.pushErrorInfo("pveExploreVo");
		errorManager.pushErrorInfo("pveExploreStartData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject pveExplore = pveExploreStartData1["pveExploreVo"].toObject();

		if (false == jrData.userInfo.pveExploreVo.fromQJsonObject(pveExplore, errorManager)) {
			errorManager.pushErrorInfo("pveExploreVo");
			errorManager.pushErrorInfo("pveExploreStartData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!pveExploreStartData1.contains("fleetVo") || !pveExploreStartData1["fleetVo"].isArray()) {
		errorManager.pushErrorInfo("fleetVo");
		errorManager.pushErrorInfo("pveExploreStartData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray fleetList = pveExploreStartData1["fleetVo"].toArray();
		MiniNormalFleetInformation fleetTemp;

		for (int count = 0; count < fleetList.size(); count++) {
			if (!fleetList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("pveExploreStartData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == fleetTemp.fromQJsonObject(fleetList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("pveExploreStartData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.fleetVo.insert(fleetTemp.id, fleetTemp);
		}
	}

	handlePveExploreStartData1();
	emit(behaviourComplete());
	return true;
}