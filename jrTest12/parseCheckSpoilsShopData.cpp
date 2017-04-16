#include "BehaviourManager.h"

bool BehaviourManager::parseCheckSpoilsShopData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCheckSpoilsShopData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCheckSpoilsShopData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject checkSpoilsShopData1 = jsonContent.object();

	if (true == getErrorInfo(checkSpoilsShopData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	dynamicParameters.spoilNum = (int)getDoubleFromQJsonObject(checkSpoilsShopData1, "spoils", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("spoils");
		errorManager.pushErrorInfo("checkSpoilsShopData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	handleCheckSpoilsShopData1();
	emit(behaviourComplete());
	return true;
}