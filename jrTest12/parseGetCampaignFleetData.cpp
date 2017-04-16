#include "BehaviourManager.h"

bool BehaviourManager::parseGetCampaignFleetData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseGetCampaignFleetData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseGetCampaignFleetData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject getCampaignFleetData1 = jsonContent.object();

	if (true == getErrorInfo(getCampaignFleetData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet.clear();
	if (!getCampaignFleetData1.contains("campaignLevelFleet") || !getCampaignFleetData1["campaignLevelFleet"].isArray()) {
		errorManager.pushErrorInfo("campaignLevelFleet");
		errorManager.pushErrorInfo("getCampaignFleetData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray campaignLevelFleet = getCampaignFleetData1["campaignLevelFleet"].toArray();

		for (int count = 0; count < campaignLevelFleet.size(); count++) {
			valueTemp = (int)getDoubleFromQJsonValueRef(campaignLevelFleet[count], flagTemp);
			if (flagTemp != 0) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("campaignLevelFleet");
				errorManager.pushErrorInfo("getCampaignFleetData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
			dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet.append(valueTemp);
		}
	}

	handleGetCampaignFleetData1();
	emit(behaviourComplete());
	return true;
}