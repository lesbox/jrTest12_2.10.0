#include "BehaviourManager.h"

bool BehaviourManager::parseGetInitializationDataData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseGetInitializationDataData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseGetInitializationDataData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	QJsonObject getInitializationDataData1 = jsonContent.object();

	if (true == getErrorInfo(getInitializationDataData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (false == jrData.initInfo.fromQJsonObject(getInitializationDataData1, errorManager)) {
		errorManager.pushErrorInfo("getInitializationDataData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	QFile initInfoFile;
	initInfoFile.setFileName(staticParameters.initInfoFilePath);
	if (false == initInfoFile.open(QIODevice::WriteOnly)) {
		errorManager.pushErrorInfo("open initialization file error");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	initInfoFile.write(jsonContent.toJson());
	initInfoFile.close();

	handleGetInitializationDataData1();
	emit(behaviourComplete());
	return true;
}