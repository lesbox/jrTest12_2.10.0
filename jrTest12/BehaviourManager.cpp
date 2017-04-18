#include "BehaviourManager.h"

DynamicParametersInformation::DynamicParametersInformation() {

}

DynamicParametersInformation::~DynamicParametersInformation() {

}

bool DynamicParametersInformation::resetAll() {
	dataUpdateFlag.currentCampaignInfoFlag = false;
	dataUpdateFlag.pvpUserInfoListFlag = false;
	dataUpdateFlag.spoilNumFlag = false;
	dataUpdateFlag.unlockedShipsFlag = false;
	defaultStealAluminiumShipId = 0;
	drop500 = 0;
	canPvp = false;
	canCampaign = false;
	canCompleteTask = false;
	spoilNum = 0;
	maxSpoilNum = 0;
	stealAmmoBrokenCount = 0;
	stealOilBrokenCount = 0;
	completeTaskShipType = 0;
	trainingOil = 0;
	trainingAmmo = 0;
	loginFinished = false;
	collectShipSuccessFlag = false;
	collectShip_205SkipFailedCount = 0;

	return true;
}

BehaviourNode::BehaviourNode() {
	this->behaviourType = BehaviourType::IdleBehaviour;
}

BehaviourNode::~BehaviourNode() {

}

BehaviourNode::BehaviourNode(BehaviourType behaviourType, QVariant behaviourParameters) {
	this->behaviourType = behaviourType;
	this->behaviourParameters = behaviourParameters;
}

BehaviourManager::BehaviourManager() {
	currentBehaviourDepth = 0;
	networkCookie = NULL;
	networkManager = NULL;
	request = NULL;
	networkReply = NULL;
	currentRequestId = RequestId::NoRequest;
	currentRequestRepeatNum = 0;
}

BehaviourManager::~BehaviourManager() {
	if (request != NULL) {
		delete request;
	}
}

bool BehaviourManager::networkErrorSlot(QNetworkReply::NetworkError msg) {
	return true;
}

#ifdef ud_WLTNetwork
void BehaviourManager::reconnectWLAN() {
	networkSession->deleteLater();

	networkManager->deleteLater();
	networkCookie = new ud_NetworkCookie(this);
	networkManager = new QNetworkAccessManager(this);
	networkManager->setCookieJar(networkCookie);
	resendRequest();
}

void BehaviourManager::reconnectWLANError(QNetworkSession::SessionError err) {
	reconnectWLANErrorHandler();
	return;
}

void BehaviourManager::reconnectWLANErrorHandler() {
	QNetworkConfiguration cfg;
	QNetworkConfigurationManager ncm;
	auto nc = ncm.allConfigurations();

	int flag = 0;
	for (auto &x : nc)
	{
		if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
		{
			QString test = x.name();
			if (x.name() == "") {
				cfg = x;
				flag = 1;
			}
		}
	}

	if (flag == 0) {
		QTimer timerTemp;
		connect(&timerTemp, SIGNAL(timeout()), this, SLOT(reconnectWLANErrorHandler()));
		timerTemp.setSingleShot(true);
		timerTemp.start(60000 + (qrand() % 5000));
		return;
	}

	networkSession->deleteLater();

	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	timerTemp.start(10000 + (qrand() % 5000));
	eventloop.exec();

	networkSession = new QNetworkSession(cfg, this);
	connect(networkSession, SIGNAL(opened()), this, SLOT(reconnectWLAN()));
	connect(networkSession, SIGNAL(error(QNetworkSession::SessionError)), this, SLOT(reconnectWLANError(QNetworkSession::SessionError)));
	networkSession->open();
}
#endif

bool BehaviourManager::abortRequest() {
	networkReply->abort();
	return true;
}

bool BehaviourManager::resendRequest() {

	currentRequestRepeatNum++;

	qsrand(QDateTime::currentDateTimeUtc().toTime_t());
	QEventLoop eventloop;
	QTimer timerTemp;
	connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
	timerTemp.setSingleShot(true);
	timerTemp.start(10000 + (qrand() % 5000));
	eventloop.exec();

	if (currentRequestRepeatNum >= staticParameters.maxRequestRepeatNum) {
		emit(outputLog(0, "reach request repeat number top"));

		qsrand(QDateTime::currentDateTimeUtc().toTime_t());
		if (resendRequestTimer.isActive()) {
			resendRequestTimer.stop();
		}
		currentRequestId = RequestId::NoRequest;
		currentRequestRepeatNum = 0;
		resendRequestTimer.setSingleShot(true);
		resendRequestTimer.start(600000 + (qrand() % 100000) * 2);
		return true;
	}

	if (currentRequestId == RequestId::NoRequest) {

	}
	else if (currentRequestId == RequestId::BuildLogRequest1) {
		//sendBuildLogRequest1();
	}
	else if (currentRequestId == RequestId::CreateFleetRequest1) {
		sendCreateFleetRequest1();
	}
	else if (currentRequestId == RequestId::SupplyMultiBoatRequest1) {
		sendSupplyMultiBoatRequest1();
	}
	else if (currentRequestId == RequestId::LoginRequest1) {
		sendLoginRequest1();
	}
	else if (currentRequestId == RequestId::LoginRequest2) {
		sendLoginRequest2();
	}
	else if (currentRequestId == RequestId::LoginRequest3) {
		sendLoginRequest3();
	}
	else if (currentRequestId == RequestId::LoginRequest4) {
		sendLoginRequest4();
	}
	else if (currentRequestId == RequestId::LoginRequest5) {
		sendLoginRequest5();
	}
	else if (currentRequestId == RequestId::LoginRequest6) {
		sendLoginRequest6();
	}
	else if (currentRequestId == RequestId::LoginRequest7) {
		sendLoginRequest7();
	}
	else if (currentRequestId == RequestId::LoginRequest8) {
		sendLoginRequest8();
	}
	else if (currentRequestId == RequestId::LoginRequest9) {
		sendLoginRequest9();
	}
	else if (currentRequestId == RequestId::PveExploreCompleteRequest1) {
		sendPveExploreCompleteRequest1();
	}
	else if (currentRequestId == RequestId::PveExploreStartRequest1) {
		sendPveExploreStartRequest1();
	}
	else if (currentRequestId == RequestId::PveWarRequest1) {
		sendPveWarRequest1();
	}
	else if (currentRequestId == RequestId::PveWarRequest2) {
		sendPveWarRequest2();
	}
	else if (currentRequestId == RequestId::PveWarRequest3) {
		sendPveWarRequest3();
	}
	else if (currentRequestId == RequestId::PveWarRequest4) {
		sendPveWarRequest4();
	}
	else if (currentRequestId == RequestId::PveWarRequest5) {
		sendPveWarRequest5();
	}
	else if (currentRequestId == RequestId::PveWarRequest6) {
		sendPveWarRequest6();
	}
	else if (currentRequestId == RequestId::PveWarRequest7) {
		sendPveWarRequest7();
	}
	else if (currentRequestId == RequestId::PveWarRequest8) {
		sendPveWarRequest8();
	}
	else if (currentRequestId == RequestId::PveWarRequest9) {
		sendPveWarRequest9();
	}
	else if (currentRequestId == RequestId::CheckPvpStatusRequest1) {
		sendCheckPvpStatusRequest1();
	}
	else if (currentRequestId == RequestId::PvpWarRequest1) {
		sendPvpWarRequest1();
	}
	else if (currentRequestId == RequestId::PvpWarRequest2) {
		sendPvpWarRequest2();
	}
	else if (currentRequestId == RequestId::PvpWarRequest3) {
		sendPvpWarRequest3();
	}
	else if (currentRequestId == RequestId::PvpWarRequest4) {
		sendPvpWarRequest4();
	}
	else if (currentRequestId == RequestId::PvpWarRequest5) {
		sendPvpWarRequest5();
	}
	else if (currentRequestId == RequestId::PvpWarRequest6) {
		sendPvpWarRequest6();
	}
	else if (currentRequestId == RequestId::PvpWarRequest7) {
		sendPvpWarRequest7();
	}
	else if (currentRequestId == RequestId::RepairShipStartRequest1) {
		sendRepairShipStartRequest1();
	}
	else if (currentRequestId == RequestId::GetCampaignFleetRequest1) {
		sendGetCampaignFleetRequest1();
	}
	else if (currentRequestId == RequestId::CampaignRequest1) {
		sendCampaignRequest1();
	}
	else if (currentRequestId == RequestId::CampaignRequest2) {
		sendCampaignRequest2();
	}
	else if (currentRequestId == RequestId::CampaignRequest3) {
		sendCampaignRequest3();
	}
	else if (currentRequestId == RequestId::CampaignRequest4) {
		sendCampaignRequest4();
	}
	else if (currentRequestId == RequestId::CampaignRequest5) {
		sendCampaignRequest5();
	}
	else if (currentRequestId == RequestId::CampaignRequest6) {
		sendCampaignRequest6();
	}
	else if (currentRequestId == RequestId::GetTaskAwardRequest1) {
		sendGetTaskAwardRequest1();
	}
	else if (currentRequestId == RequestId::GetLoginAwardRequest1) {
		sendGetLoginAwardRequest1();
	}
	else if (currentRequestId == RequestId::SupplyBoatRequest1) {
		sendSupplyBoatRequest1();
	}
	else if (currentRequestId == RequestId::GetInitializationDataRequest1) {
		sendGetInitializationDataRequest1();
	}
	else if (currentRequestId == RequestId::InstantRepairMultiShipRequest1) {
		sendInstantRepairMultiShipRequest1();
	}
	else if (currentRequestId == RequestId::RepairShipCompleteRequest1) {
		sendRepairShipCompleteRequest1();
	}
	else if (currentRequestId == RequestId::CheckSpoilsShopRequest1) {
		sendCheckSpoilsShopRequest1();
	}
	else if (currentRequestId == RequestId::DismantleRequest1) {
		sendDismantleRequest1();
	}
	else if (currentRequestId == RequestId::RemoveEquipmentRequest1) {
		sendRemoveEquipmentRequest1();
	}
	else if (currentRequestId == RequestId::ChangeEquipmentRequest1) {
		sendChangeEquipmentRequest1();
	}
#ifdef ud_WLTNetwork
	else if (currentRequestId == RequestId::WLTRequest1) {
		sendWLTRequest1();
	}
	else if (currentRequestId == RequestId::WLTRequest2) {
		sendWLTRequest2();
	}
	else if (currentRequestId == RequestId::WLTRequest3) {
		sendWLTRequest3();
	}
#endif
	else {

	}

	return true;
}

bool BehaviourManager::handleResponse(QJsonDocument & jsonContent, ErrorManager & errorManager) {
	if (networkDelayTimer.isActive()) {
		networkDelayTimer.stop();
	}

	QString headerContentTemp, attrName, attrValue;
	int indexTemp1, indexTemp2;
	QByteArray requestContent1, decompressData;

	if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200) {
		if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 0) {

#ifdef ud_WLTNetwork
			QNetworkConfiguration cfg;
			QNetworkConfigurationManager ncm;
			auto nc = ncm.allConfigurations();

			int flag = 0;
			for (auto &x : nc)
			{
				if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
				{
					QString test = x.name();
					if (x.name() == "LAB-1213") {
						cfg = x;
						flag = 1;
					}
				}
			}

			if (flag == 0) {
				QEventLoop eventloop;
				QTimer timerTemp;
				connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
				timerTemp.setSingleShot(true);
				timerTemp.start(60000 + (qrand() % 5000));
				eventloop.exec();
			}
			else if (cfg.state() == QNetworkConfiguration::StateFlag::Discovered) {
				QEventLoop eventloop;
				QTimer timerTemp;
				connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
				timerTemp.setSingleShot(true);
				timerTemp.start(10000 + (qrand() % 5000));
				eventloop.exec();
				networkSession = new QNetworkSession(cfg, this);
				connect(networkSession, SIGNAL(opened()), this, SLOT(reconnectWLAN()));
				connect(networkSession, SIGNAL(error(QNetworkSession::SessionError)), this, SLOT(reconnectWLANError(QNetworkSession::SessionError)));
				networkSession->open();
				return false;
			}
#endif

			networkManager->deleteLater();
			networkManager = new QNetworkAccessManager(this);
			networkCookie = new ud_NetworkCookie(this);
			networkManager->setCookieJar(networkCookie);
		}
		else {
			networkReply->deleteLater();
		}
		errorManager.pushErrorInfo(QString("HTTP status : ") + QString::number(networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()));
		resendRequest();
		return false;
	}

	lastResponseContent = requestContent1 = networkReply->readAll();
	networkReply->deleteLater();

	if (requestContent1 == "") {
		errorManager.pushErrorInfo(QString("no response content"));
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(outputLog(0, errorManager.getErrorInfo()));
		emit(behaviourComplete());
		return false;
	}

	currentRequestId = RequestId::NoRequest;
	currentRequestRepeatNum = 0;

	if (-1 != requestContent1.indexOf("redirecting to http://wlt.ustc.edu.cn")) {
		emit(outputLog(0, "reconnect WLT"));
		sendWLTRequest1();
		return false;
	}

	if (networkReply->hasRawHeader("Set-Cookie")) {
		headerContentTemp = QString::fromUtf8(networkReply->rawHeader("Set-Cookie"));
		int indexTemp1 = 0;
		int indexTemp2 = 0;
		int headerContentTempLen = headerContentTemp.length();
		while (true) {
			while (indexTemp1 < headerContentTempLen && (headerContentTemp[indexTemp1] == '\n' || headerContentTemp[indexTemp1] == ' ' || headerContentTemp[indexTemp1] == ';')) {
				indexTemp1++;
			}
			if (indexTemp1 == headerContentTempLen) {
				break;
			}
			indexTemp2 = indexTemp1;
			while (indexTemp2 < headerContentTempLen && headerContentTemp[indexTemp2] != '\n' && headerContentTemp[indexTemp2] != ' ' && headerContentTemp[indexTemp2] != ';' && headerContentTemp[indexTemp2] != '=') {
				indexTemp2++;
			}
			if (indexTemp2 == headerContentTempLen) {
				break;
			}
			if (indexTemp2 == indexTemp1) {
				errorManager.pushErrorInfo(QString("Set-Cookie : ") + networkReply->rawHeader("Set-Cookie"));
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(outputLog(0, errorManager.getErrorInfo()));
				emit(behaviourComplete());
				return false;
			}
			else if (headerContentTemp[indexTemp2] != '=') {
				indexTemp1 = indexTemp2;
			}
			else {
				attrName = headerContentTemp.mid(indexTemp1, indexTemp2 - indexTemp1);
				indexTemp1 = indexTemp2 + 1;
				while (indexTemp1 < headerContentTempLen && headerContentTemp[indexTemp1] != '\n' && headerContentTemp[indexTemp1] != ' ' && headerContentTemp[indexTemp1] != ';' && headerContentTemp[indexTemp1] != '=') {
					indexTemp1++;
				}
				attrValue = headerContentTemp.mid(indexTemp2 + 1, indexTemp1 - (indexTemp2 + 1));
				if (cookie.contains(attrName)) {
					cookie[attrName] = attrValue;
				}
				else {
					cookie.insert(attrName, attrValue);
				}
			}
		}
	}

	if (!networkReply->hasRawHeader("Content-Type")) {
		errorManager.pushErrorInfo(QString("no Content-Type header"));
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(outputLog(0, errorManager.getErrorInfo()));
		emit(behaviourComplete());
		return false;
	}
	else {
		if (networkReply->header(QNetworkRequest::ContentTypeHeader).toString() == QString("application/octet-stream")) {
			if (decompress(requestContent1, &decompressData) != Z_OK) {
				errorManager.pushErrorInfo(QString("zip decompress error"));
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(outputLog(0, errorManager.getErrorInfo()));
				emit(behaviourComplete());
				return false;
			}
			else {
				requestContent1 = decompressData;
				lastResponseContent = requestContent1;
			}
		}
		else {

		}
	}

	QJsonParseError jsonError;
	jsonContent = QJsonDocument::fromJson(requestContent1, &jsonError);

	if (jsonError.error != QJsonParseError::NoError) {
		errorManager.pushErrorInfo(jsonError.errorString());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(outputLog(0, errorManager.getErrorInfo()));
		emit(behaviourComplete());
		return false;
	}

	return true;
}

bool BehaviourManager::getErrorInfo(QJsonObject data) {
	int flagTemp;
	int valueTemp;

	valueTemp = (int)getDoubleFromQJsonObject(data, "eid", flagTemp);
	if (flagTemp == 2) {
		valueTemp = (int)getDoubleFromQJsonObject(data, "code", flagTemp);
		if (flagTemp == 2) {
			return false;
		}
		else if (flagTemp == 1) {
			errorHandler("getErrorInfo error\n");
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			errorHandler(jrData.initInfo.errorCode[valueTemp]);
			if (valueTemp == -1) {
				resendRequest();
				return true;
			}
			else {
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::OperationError, QVariant(valueTemp));
				emit(behaviourComplete());
				return true;
			}
		}
	}
	else if (flagTemp == 1) {
		errorHandler("getErrorInfo error\n");
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	else {
		errorHandler(jrData.initInfo.errorCode[valueTemp]);
		if (valueTemp == -1) {
			resendRequest();
			return true;
		}
		else {
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::OperationError, QVariant(valueTemp));
			emit(behaviourComplete());
			return true;
		}
	}

	return false;
}

BehaviourNode * BehaviourManager::getParentBehaviour() {
	if (currentBehaviourDepth < 1) {
		return NULL;
	}
	else if(currentBehaviourDepth == 1){
		if (rootBehaviour.size() == 0) {
			errorHandler("getParentBehaviour error");
			return NULL;
		}
		else {
			return &(rootBehaviour[0]);
		}
	}
	else {
		if (rootBehaviour.size() == 0) {
			errorHandler("getParentBehaviour error");
			return NULL;
		}
		else {
			BehaviourNode * behaviourNodeRefTemp = &(rootBehaviour[0]);
			for (int count = 1; count < currentBehaviourDepth; count++) {
				if (behaviourNodeRefTemp->childBehaviour.size() == 0) {
					errorHandler("getParentBehaviour error");
					return behaviourNodeRefTemp;
				}
				else {
					behaviourNodeRefTemp = &(behaviourNodeRefTemp->childBehaviour[0]);
				}
			}
			return behaviourNodeRefTemp;
		}
	}
}

bool BehaviourManager::dispatchShip(int shipId) {
	if (staticParameters.reservedShipCidList.indexOf(jrData.userInfo.userShipVo[shipId].shipCid) != -1) {
		dynamicParameters.reservedShipIdList.append(shipId);
	}
	else if (getBrokenStatus(shipId) == 4 || jrData.userInfo.userShipVo[shipId].battleProps.oil == 0 || jrData.userInfo.userShipVo[shipId].battleProps.ammo == 0) {
		if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[shipId].shipCid].type != 12) {
			dynamicParameters.dogFoodShipIdList.append(shipId);
		}
		else {
			dynamicParameters.dismantleShipIdList.append(shipId);
		}
	}
	else if ((jrData.userInfo.userShipVo[shipId].battleProps.oil * 5 <= jrData.userInfo.userShipVo[shipId].battlePropsMax.oil || jrData.userInfo.userShipVo[shipId].battleProps.ammo <= (int)ceil(jrData.userInfo.userShipVo[shipId].battlePropsMax.ammo * 0.3))) {
		dynamicParameters.stealAluminiumDogFoodShipIdList.append(shipId);
	}
	else {
		dynamicParameters.stealOilAndAmmoDogFoodShipIdList.append(shipId);
	}
	return true;
}

int BehaviourManager::checkFleetBrokenStatus(int fleetId) {
	if (jrData.userInfo.fleetVo[fleetId].ships.size() == 0) {
		return 4;
	}
	if (4 == getBrokenStatus(jrData.userInfo.fleetVo[fleetId].ships[0])) {
		return 3;
	}
	for (int count = 1; count < jrData.userInfo.fleetVo[fleetId].ships.size(); count++) {
		if (4 == getBrokenStatus(jrData.userInfo.fleetVo[fleetId].ships[count])) {
			return 2;
		}
	}
	return 1;
}

int BehaviourManager::checkFleetSupplyStatus(int fleetId) {
	if (jrData.userInfo.fleetVo[fleetId].ships.size() == 0) {
		return 4;
	}
	bool flagTemp = true;
	for (int count = 0; count < jrData.userInfo.fleetVo[fleetId].ships.size(); count++) {
		if (flagTemp == true && (jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[fleetId].ships[count]].battleProps.oil != jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[fleetId].ships[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[fleetId].ships[count]].battleProps.ammo != jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[fleetId].ships[count]].battlePropsMax.ammo)) {
			flagTemp = false;
		}
		if (jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[fleetId].ships[count]].battleProps.oil == 0 || jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[fleetId].ships[count]].battleProps.ammo == 0) {
			return 3;
		}
	}

	if (flagTemp == true) {
		return 2;
	}

	return 1;
}

int BehaviourManager::generatePid() {
	int pidMin = 406053, pidMax = 638088;
	qsrand(QDateTime::currentDateTime().toTime_t());
	int randTemp = qrand() << 15 + qrand();
	return randTemp % (pidMax - pidMin) + pidMin;
}

void BehaviourManager::errorHandler(QString errorInfo) {
	QFile errorInfoFile, errorContentFile;
	errorInfoFile.setFileName("D:\\Documents\\VisualStudio2015Projects\\jrTest12\\jrTest12\\tempData\\errorInfo.txt");
	errorContentFile.setFileName("D:\\Documents\\VisualStudio2015Projects\\jrTest12\\jrTest12\\tempData\\errorContent.txt");

	if (true == errorInfoFile.open(QIODevice::WriteOnly)) {
		errorInfoFile.write(errorInfo.toUtf8());
		errorInfoFile.close();
	}

	if (true == errorContentFile.open(QIODevice::WriteOnly)) {
		errorContentFile.write(lastResponseContent);
		errorContentFile.close();
	}

	emit(outputLog(0, errorInfo));
}

int BehaviourManager::isTheSameClass(int shipId1, int shipId2) {
	int shipCidTemp1 = jrData.userInfo.userShipVo[shipId1].shipCid;
	while (true) {
		if (jrData.initInfo.shipCard.contains(shipCidTemp1) && jrData.initInfo.shipCard[shipCidTemp1].evoCid != shipCidTemp1 && jrData.initInfo.shipCard[shipCidTemp1].evoCid != 0) {
			shipCidTemp1 = jrData.initInfo.shipCard[shipCidTemp1].evoCid;
		}
		else {
			break;
		}
	}

	int shipCidTemp2 = jrData.userInfo.userShipVo[shipId2].shipCid;
	while (true) {
		if (jrData.initInfo.shipCard.contains(shipCidTemp2) && jrData.initInfo.shipCard[shipCidTemp2].evoCid != shipCidTemp2 && jrData.initInfo.shipCard[shipCidTemp2].evoCid != 0) {
			shipCidTemp2 = jrData.initInfo.shipCard[shipCidTemp2].evoCid;
		}
		else {
			break;
		}
	}

	if (shipCidTemp1 == shipCidTemp2) {
		return 1;
	}

	return 0;
}

int BehaviourManager::getBrokenStatus(int shipId) {
	if (jrData.userInfo.userShipVo[shipId].battleProps.hp >= jrData.userInfo.userShipVo[shipId].battlePropsMax.hp) {
		return 1;
	}
	else if (jrData.userInfo.userShipVo[shipId].battleProps.hp * 2 >= jrData.userInfo.userShipVo[shipId].battlePropsMax.hp) {
		return 2;
	}
	else if (jrData.userInfo.userShipVo[shipId].battleProps.hp * 4 >= jrData.userInfo.userShipVo[shipId].battlePropsMax.hp) {
		return 3;
	}
	else {
		return 4;
	}
}

bool BehaviourManager::buildRequest(QString url, bool appendSuffix, bool appendCookies, QMap<QByteArray, QByteArray> extraRawHeaders, QString host) {
	QString t;
	QString e;

	if (request != NULL) {
		delete request;
	}

	request = new QNetworkRequest();
	if (appendSuffix == false) {
		request->setUrl(url);
	}
	else {
		t = QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
		e = generateEncryptCode();

		request->setUrl(QUrl(url + QString("&t=") + t + QString("&e=") + e + QString("&gz=1&market=2&channel=0&version=2.10.0")));
	}

	networkCookie->setCookies(QList<QNetworkCookie>());
	if (appendCookies == false) {

	}
	else {
		if (!cookie.contains("hf_skey")) {
			errorHandler(QString("cookie error : hf_skey\n"));
			return false;
		}
		if (!cookie.contains("path")) {
			errorHandler(QString("cookie error : path\n"));
			return false;
		}
		if (!cookie.contains("QCLOUD")) {
			errorHandler(QString("cookie error : QCLOUD\n"));
			return false;
		}

		networkCookie->setCookies(QList<QNetworkCookie>());
		request->setRawHeader("Cookie", (QString("hf_skey=") + cookie["hf_skey"] + QString("; path=") + cookie["path"] + QString(";QCLOUD=") + cookie["QCLOUD"]).toUtf8());
	}

	request->setRawHeader("Accept-Encoding", "identity");
	request->setRawHeader("User-Agent", "Dalvik/1.6.0 (Linux; U; Android 4.4.2; PE-TL10 Build/HuaweiPE-TL10)");
	request->setRawHeader("Host", host.toUtf8());
	request->setRawHeader("Connection", "Keep-Alive");

	for each(QByteArray key in extraRawHeaders.keys()) {
		request->setRawHeader(key, extraRawHeaders[key]);
	}

	return true;
}

QString BehaviourManager::generateEncryptCode() {
	qsrand(QDateTime::currentDateTime().toTime_t());
	QByteArray sourceData;
	int integerTemp;
	for (int count = 0; count < 4; count++) {
		integerTemp = qrand();
		sourceData.append((char *)&integerTemp, 4);
	}
	return QCryptographicHash::hash(sourceData, QCryptographicHash::Md5).toHex();
}

bool BehaviourManager::executeNextExecutableBehaviour() {
	if (dynamicParameters.loginFinished == true && jrData.userInfo.packageVo[66641].num < 11) {
		errorHandler("package number error\n");
		return false;
	}

	if ((*getParentBehaviour()).childBehaviour.size() == 0) {
		if (currentBehaviourDepth > 1) {
			currentBehaviourDepth--;
			emit(behaviourComplete());
		}

		return true;
	}

	BehaviourNode childNodeTemp;
	BehaviourType currentBehaviourType = (*getParentBehaviour()).childBehaviour[0].behaviourType;

	if (currentBehaviourType == BehaviourType::InitStaticParametersBehaviour) {
		initStaticParameters();
	}
	else if (currentBehaviourType == BehaviourType::InitBattleParametersBehaviour) {
		initBattleParameters();
	}
	else if (currentBehaviourType == BehaviourType::InitDynamicParametersBehaviour) {
		initDynamicParameters();
	}
	else if (currentBehaviourType == BehaviourType::StealOilBehaviour) {
		stealOil();
	}
	else if (currentBehaviourType == BehaviourType::StealAmmoBehaviour) {
		stealAmmo();
	}
	else if (currentBehaviourType == BehaviourType::StealAluminiumBehaviour) {
		stealAluminium();
	}
	else if (currentBehaviourType == BehaviourType::StealPantsBehaviour) {
		stealPants();
	}
	else if (currentBehaviourType == BehaviourType::CollectDogFoodBehaviour) {
		collectDogFood();
	}
	else if (currentBehaviourType == BehaviourType::CollectShipBehaviour) {
		collectShip();
	}
	else if (currentBehaviourType == BehaviourType::TrainShipBehaviour) {
		trainShip();
	}
	else if (currentBehaviourType == BehaviourType::RepairShipBehaviour) {
		repairShip();
	}
	else if (currentBehaviourType == BehaviourType::PveExploreBehaviour) {
		pveExplore();
	}
	else if (currentBehaviourType == BehaviourType::ActiveFleetPveExploreBehaviour) {
		activeFleetPveExplore();
	}
	else if (currentBehaviourType == BehaviourType::UpdatePvpStatusBehaviour) {
		updatePvpStatus();
	}
	else if (currentBehaviourType == BehaviourType::PvpWarBehaviour) {
		pvpWar();
	}
	else if (currentBehaviourType == BehaviourType::UpdateCampaignStatusBehaviour) {
		updateCampaignStatus();
	}
	else if (currentBehaviourType == BehaviourType::CompleteTaskBehaviour) {
		completeTask();
	}
	else if (currentBehaviourType == BehaviourType::SaveAndLoadBehaviour) {
		saveAndLoad();
	}
	else {
		qsrand(QDateTime::currentDateTimeUtc().toTime_t());
		QEventLoop eventloop;
		QTimer timerTemp;
		connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
		timerTemp.setSingleShot(true);
		timerTemp.start(2000 + (qrand() % 2000));
		eventloop.exec();

		if (currentBehaviourType == BehaviourType::IdleBehaviour) {

		}
		else if (currentBehaviourType == BehaviourType::LoginBehaviour) {
			login();
		}
		else if (currentBehaviourType == BehaviourType::RepairShipStartBehaviour) {
			repairShipStart();
		}
		else if (currentBehaviourType == BehaviourType::RepairShipCompleteBehaviour) {
			repairShipComplete();
		}
		else if (currentBehaviourType == BehaviourType::InstantRepairMultiShipBehaviour) {
			instantRepairMultiShip();
		}
		else if (currentBehaviourType == BehaviourType::CreateFleetBehaviour) {
			createFleet();
		}
		else if (currentBehaviourType == BehaviourType::RemoveEquipmentBehaviour) {
			removeEquipment();
		}
		else if (currentBehaviourType == BehaviourType::ChangeEquipmentBehaviour) {
			changeEquipment();
		}
		else if (currentBehaviourType == BehaviourType::SupplyMultiBoatBehaviour) {
			supplyMultiBoat();
		}
		else if (currentBehaviourType == BehaviourType::SupplyBoatBehaviour) {
			supplyBoat();
		}
		else if (currentBehaviourType == BehaviourType::PveWarBehaviour) {
			pveWar();
		}
		else if (currentBehaviourType == BehaviourType::PveExploreStartBehaviour) {
			pveExploreStart();
		}
		else if (currentBehaviourType == BehaviourType::PveExploreCompleteBehaviour) {
			pveExploreComplete();
		}
		else if (currentBehaviourType == BehaviourType::CheckPvpStatusBehaviour) {
			checkPvpStatus();
		}
		else if (currentBehaviourType == BehaviourType::GetCampaignFleetBehaviour) {
			getCampaignFleet();
		}
		else if (currentBehaviourType == BehaviourType::CampaignBehaviour) {
			campaign();
		}
		else if (currentBehaviourType == BehaviourType::GetTaskAwardBehaviour) {
			getTaskAward();
		}
		else if (currentBehaviourType == BehaviourType::GetLoginAwardBehaviour) {
			getLoginAward();
		}
		else if (currentBehaviourType == BehaviourType::GetInitializationDataBehaviour) {
			getInitializationData();
		}
		else if (currentBehaviourType == BehaviourType::CheckSpoilsShopBehaviour) {
			checkSpoilShop();
		}
		else if (currentBehaviourType == BehaviourType::DismantleBehaviour) {
			dismantle();
		}
	}

	return true;
}

bool BehaviourManager::idle() {
	emit(behaviourComplete());

	return true;
}

bool BehaviourManager::login() {
	sendLoginRequest1();

	return true;
}

bool BehaviourManager::completeTask() {
	for each(int taskCidTemp in jrData.userInfo.taskVo.keys()) {
		//2300333 击破母港周边哨戒(第1章)敌军势力
		//2300433 击破扶桑海域攻略(第2章)敌军势力
		//2300533 击破星洲海峡突破(第3章)敌军势力
		//2200232 击破敌军主力
		//2200732 [出征]作战：战列舰
		//2201532 [出征]作战：战列舰
		//2200932 [出征]作战：航空母舰
		//2201732 [出征]作战：航空母舰
		//2200632 [出征]作战：重巡洋舰
		//2201432 [出征]作战：重巡洋舰
		//2201832 [出征]作战：战列巡洋舰
		//2201132 [出征]作战：战列巡洋舰
		//2200832 [出征]作战：轻型航空母舰
		//2201632 [出征]作战：轻型航空母舰
		if (taskCidTemp == 2300333) {
			startCompleteTask_2300333();
			return true;
		}
		else if (taskCidTemp == 2300433) {
			startCompleteTask_2300433();
			return true;
		}
		else if (taskCidTemp == 2300533) {
			startCompleteTask_2300533();
			return true;
		}
		else if (taskCidTemp == 2200232) {
			startCompleteTask_2200232();
			return true;
		}
		else if (taskCidTemp == 2200732) {
			startCompleteTask_2200732();
			return true;
		}
		else if (taskCidTemp == 2201532) {
			startCompleteTask_2201532();
			return true;
		}
		else if (taskCidTemp == 2200932) {
			startCompleteTask_2200932();
			return true;
		}
		else if (taskCidTemp == 2201732) {
			startCompleteTask_2201732();
			return true;
		}
		else if (taskCidTemp == 2200632) {
			startCompleteTask_2200632();
			return true;
		}
		else if (taskCidTemp == 2201432) {
			startCompleteTask_2201432();
			return true;
		}
		else if (taskCidTemp == 2201832) {
			startCompleteTask_2201832();
			return true;
		}
		else if (taskCidTemp == 2201132) {
			startCompleteTask_2201132();
			return true;
		}
		else if (taskCidTemp == 2200832) {
			startCompleteTask_2200832();
			return true;
		}
		else if (taskCidTemp == 2201632) {
			startCompleteTask_2201632();
			return true;
		}
	}

	dynamicParameters.canCompleteTask = false;
	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());
	emit(behaviourComplete());
	return true;
}

bool BehaviourManager::startCompleteTask_2300333() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 0;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2300333.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2300333.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2300333.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2300333.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2300333.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2300333.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300333.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2300333.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2300333.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300333.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300333.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300333.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300333.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300333.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300333.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2300333.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2300333.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2300433() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 0;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2300433.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2300433.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2300433.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2300433.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2300433.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2300433.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300433.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2300433.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2300433.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300433.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300433.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300433.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300433.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300433.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300433.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2300433.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2300433.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2300533() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 0;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2300533.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2300533.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2300533.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2300533.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2300533.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2300533.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300533.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2300533.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2300533.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300533.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300533.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300533.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300533.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300533.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2300533.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2300533.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2300533.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2200232() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 0;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2200232.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2200232.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2200232.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200232.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2200232.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2200232.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200232.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2200232.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2200232.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200232.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200232.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200232.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200232.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200232.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200232.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200232.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2200232.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2200732() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 4;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2200732.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2200732.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2200732.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200732.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2200732.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2200732.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200732.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2200732.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2200732.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200732.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200732.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200732.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200732.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200732.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200732.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200732.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2200732.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2201532() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 4;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2201532.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2201532.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2201532.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201532.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2201532.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2201532.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201532.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2201532.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2201532.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201532.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201532.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201532.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201532.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201532.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201532.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201532.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2201532.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2200932() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 1;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2200932.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2200932.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2200932.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200932.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2200932.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2200932.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200932.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2200932.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2200932.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200932.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200932.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200932.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200932.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200932.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200932.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200932.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2200932.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2201732() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 1;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2201732.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2201732.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2201732.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201732.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2201732.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2201732.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201732.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2201732.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2201732.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201732.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201732.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201732.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201732.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201732.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201732.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201732.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2201732.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2200632() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 7;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2200632.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2200632.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2200632.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200632.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2200632.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2200632.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200632.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2200632.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2200632.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200632.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200632.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200632.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200632.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200632.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200632.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200632.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2200632.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2201432() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 7;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2201432.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2201432.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2201432.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201432.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2201432.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2201432.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201432.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2201432.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2201432.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201432.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201432.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201432.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201432.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201432.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201432.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201432.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2201432.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2201832() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 6;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2201832.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2201832.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2201832.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201832.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2201832.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2201832.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201832.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2201832.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2201832.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201832.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201832.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201832.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201832.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201832.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201832.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201832.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2201832.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2201132() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 6;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2201132.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2201132.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2201132.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201132.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2201132.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2201132.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201132.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2201132.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2201132.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201132.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201132.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201132.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201132.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201132.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201132.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201132.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2201132.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2200832() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 2;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2200832.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2200832.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2200832.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200832.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2200832.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2200832.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200832.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2200832.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2200832.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200832.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200832.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200832.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200832.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200832.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2200832.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2200832.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2200832.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::startCompleteTask_2201632() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	currentBehaviourDepth++;
	dynamicParameters.completeTaskShipType = 2;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp;
			newFleetTemp.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.completeTaskInfo_2201632.fleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.completeTaskInfo_2201632.fleetInfo.size(); count++) {
			if (staticParameters.completeTaskInfo_2201632.fleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201632.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.completeTaskInfo_2201632.fleetInfo.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.completeTaskInfo_2201632.fleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201632.fleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.completeTaskInfo_2201632.fleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.completeTaskInfo_2201632.fleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201632.fleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201632.fleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201632.fleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201632.fleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201632.fleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.completeTaskInfo_2201632.fleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.completeTaskInfo_2201632.fleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.completeTaskInfo_2201632.pveWarInfo);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::stealPants() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.drop500 != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	currentBehaviourDepth++;

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp1;
			newFleetTemp1.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp1.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp1.size(); count++) {
					if (newFleetTemp1[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp1;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.stealPantsFleetConfig.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.stealPantsFleetConfig.size(); count++) {
			if (staticParameters.stealPantsFleetConfig[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.stealPantsFleetConfig;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.stealPantsFleetConfig.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.stealPantsFleetConfig[count]) || jrData.userInfo.userShipVo[staticParameters.stealPantsFleetConfig[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.stealPantsFleetConfig[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.stealPantsFleetConfig.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.stealPantsFleetConfig[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.stealPantsFleetConfig[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.stealPantsFleetConfig[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.stealPantsFleetConfig[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.stealPantsFleetConfig[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.stealPantsFleetConfig[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.stealPantsFleetConfig;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_StealPants);

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::stealOil() {
	QVector<int> newFleetTemp;
	bool flag;

	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.stealOilAndAmmoDogFoodShipIdList.size() < 5) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.drop500 != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	for (int count = dynamicParameters.stealOilAndAmmoDogFoodShipIdList.size() - 1; count >= 0; count--) {
		flag = true;
		for (int count1 = 0; count1 < newFleetTemp.size(); count1++) {
			if (0 != isTheSameClass(dynamicParameters.stealOilAndAmmoDogFoodShipIdList[count], newFleetTemp[count1])) {
				flag = false;
				break;
			}
		}
		if (flag == true) {
			newFleetTemp.append(dynamicParameters.stealOilAndAmmoDogFoodShipIdList[count]);
			dynamicParameters.stealOilAndAmmoDogFoodShipIdList.removeAt(count);
			if (newFleetTemp.size() == 4) {
				break;
			}
		}
	}

	if (newFleetTemp.size() != 4) {
		for (int count = 0; count < newFleetTemp.size(); count++) {
			dynamicParameters.stealOilAndAmmoDogFoodShipIdList.append(newFleetTemp[count]);
		}
		newFleetTemp.clear();
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	else {
		currentBehaviourDepth++;

		QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

		if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
			emit(outputLog(0, "reach ship number top"));
			if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else {
				QVector<int> newFleetTemp1;
				newFleetTemp1.append(4291);

				bool flagTemp = false;
				if (currentFleetTemp.size() != newFleetTemp1.size()) {
					flagTemp = true;
				}
				else {
					for (int count = 0; count < newFleetTemp1.size(); count++) {
						if (newFleetTemp1[count] != currentFleetTemp[count]) {
							flagTemp = true;
							break;
						}
					}
				}
				if (flagTemp == true) {
					CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
					createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
					createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

					(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
				}

				currentFleetTemp = newFleetTemp1;

				BehaviourNode behaviourNodeTemp;
				DismantleBehaviourParameter dismantleBehaviourParameterTemp;
				dismantleBehaviourParameterTemp.isDismantleEquipment = true;
				if (dynamicParameters.dismantleShipIdList.size() == 0) {
					if (dynamicParameters.dogFoodShipIdList.size() < 40) {
						dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
						dynamicParameters.dismantleShipIdList.clear();
					}
					else {
						for (int count = 0; count < 40; count++) {
							dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
							dynamicParameters.dogFoodShipIdList.removeLast();
						}
					}
				}
				else if (dynamicParameters.dismantleShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
						dynamicParameters.dismantleShipIdList.removeLast();
					}
				}
				behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
				(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
			}
		}

		double valueTemp = 1.0 * jrData.userInfo.userShipVo[newFleetTemp[0]].battleProps.hp / jrData.userInfo.userShipVo[newFleetTemp[0]].battlePropsMax.hp;
		int indexTemp = 0;
		for (int count = 1; count < newFleetTemp.size(); count++) {
			if (1.0 * jrData.userInfo.userShipVo[newFleetTemp[count]].battleProps.hp / jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.hp > valueTemp) {
				indexTemp = count;
				valueTemp = 1.0 * jrData.userInfo.userShipVo[newFleetTemp[count]].battleProps.hp / jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.hp;
			}
		}
		if (indexTemp != 0) {
			int shipIdTemp = newFleetTemp[0];
			newFleetTemp[0] = newFleetTemp[indexTemp];
			newFleetTemp[indexTemp] = shipIdTemp;
		}

		bool flagTemp = false;
		if (currentFleetTemp.size() != newFleetTemp.size()) {
			flagTemp = true;
		}
		else {
			for (int count = 0; count < newFleetTemp.size(); count++) {
				if (newFleetTemp[count] != currentFleetTemp[count]) {
					flagTemp = true;
					break;
				}
			}
		}
		if (flagTemp == true) {
			CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
			createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
			createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
		}

		(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_StealOil);

		(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

		executeNextExecutableBehaviour();
	}

	return true;
}

bool BehaviourManager::stealAmmo() {
	QVector<int> newFleetTemp;
	bool flag;

	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.stealOilAndAmmoDogFoodShipIdList.size() < 5) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.drop500 != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	for (int count = dynamicParameters.stealOilAndAmmoDogFoodShipIdList.size() - 1; count >= 0; count--) {
		if (jrData.userInfo.userShipVo[dynamicParameters.stealOilAndAmmoDogFoodShipIdList[count]].battleProps.speed < 27) {
			continue;
		}
		flag = true;
		for (int count1 = 0; count1 < newFleetTemp.size(); count1++) {
			if (0 != isTheSameClass(dynamicParameters.stealOilAndAmmoDogFoodShipIdList[count], newFleetTemp[count1])) {
				flag = false;
				break;
			}
		}
		if (flag == true) {
			newFleetTemp.append(dynamicParameters.stealOilAndAmmoDogFoodShipIdList[count]);
			dynamicParameters.stealOilAndAmmoDogFoodShipIdList.removeAt(count);
			if (newFleetTemp.size() == 4) {
				break;
			}
		}
	}

	if (newFleetTemp.size() != 4) {
		for (int count = 0; count < newFleetTemp.size(); count++) {
			dynamicParameters.stealOilAndAmmoDogFoodShipIdList.append(newFleetTemp[count]);
		}
		newFleetTemp.clear();
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	else {
		currentBehaviourDepth++;

		QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

		if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
			emit(outputLog(0, "reach ship number top"));
			if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else {
				QVector<int> newFleetTemp1;
				newFleetTemp1.append(4291);

				bool flagTemp = false;
				if (currentFleetTemp.size() != newFleetTemp1.size()) {
					flagTemp = true;
				}
				else {
					for (int count = 0; count < newFleetTemp1.size(); count++) {
						if (newFleetTemp1[count] != currentFleetTemp[count]) {
							flagTemp = true;
							break;
						}
					}
				}
				if (flagTemp == true) {
					CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
					createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
					createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

					(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
				}

				currentFleetTemp = newFleetTemp1;

				BehaviourNode behaviourNodeTemp;
				DismantleBehaviourParameter dismantleBehaviourParameterTemp;
				dismantleBehaviourParameterTemp.isDismantleEquipment = true;
				if (dynamicParameters.dismantleShipIdList.size() == 0) {
					if (dynamicParameters.dogFoodShipIdList.size() < 40) {
						dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
						dynamicParameters.dismantleShipIdList.clear();
					}
					else {
						for (int count = 0; count < 40; count++) {
							dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
							dynamicParameters.dogFoodShipIdList.removeLast();
						}
					}
				}
				else if (dynamicParameters.dismantleShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
						dynamicParameters.dismantleShipIdList.removeLast();
					}
				}
				behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
				(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
			}
		}

		double valueTemp = 1.0 * jrData.userInfo.userShipVo[newFleetTemp[0]].battleProps.hp / jrData.userInfo.userShipVo[newFleetTemp[0]].battlePropsMax.hp;
		int indexTemp = 0;
		for (int count = 1; count < newFleetTemp.size(); count++) {
			if (1.0 * jrData.userInfo.userShipVo[newFleetTemp[count]].battleProps.hp / jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.hp > valueTemp) {
				indexTemp = count;
				valueTemp = 1.0 * jrData.userInfo.userShipVo[newFleetTemp[count]].battleProps.hp / jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.hp;
			}
		}
		if (indexTemp != 0) {
			int shipIdTemp = newFleetTemp[0];
			newFleetTemp[0] = newFleetTemp[indexTemp];
			newFleetTemp[indexTemp] = shipIdTemp;
		}

		bool flagTemp = false;
		if (currentFleetTemp.size() != newFleetTemp.size()) {
			flagTemp = true;
		}
		else {
			for (int count = 0; count < newFleetTemp.size(); count++) {
				if (newFleetTemp[count] != currentFleetTemp[count]) {
					flagTemp = true;
					break;
				}
			}
		}
		if (flagTemp == true) {
			CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
			createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
			createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
		}

		(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_StealAmmo);

		(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

		executeNextExecutableBehaviour();
	}

	return true;
}

bool BehaviourManager::stealAluminium() {
	QVector<int> newFleetTemp;
	bool flag;

	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.drop500 != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	/*
	if (dynamicParameters.stealOilAndAmmoDogFoodShipIdList.size() < 5) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	*/
	if (dynamicParameters.defaultStealAluminiumShipId != 0 && (4 == getBrokenStatus(dynamicParameters.defaultStealAluminiumShipId) || jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].status != 0)) {
		dynamicParameters.defaultStealAluminiumShipId = 0;
	}

	if (dynamicParameters.defaultStealAluminiumShipId == 0) {
		for (int count = 0; count < staticParameters.stealAluminiumShipList.size(); count++) {
			if (4 != getBrokenStatus(staticParameters.stealAluminiumShipList[count].shipId) && jrData.userInfo.userShipVo[staticParameters.stealAluminiumShipList[count].shipId].status == 0) {
				dynamicParameters.defaultStealAluminiumShipId = staticParameters.stealAluminiumShipList[count].shipId;
				break;
			}
		}
	}

	if (dynamicParameters.defaultStealAluminiumShipId == 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	else {
		newFleetTemp.append(dynamicParameters.defaultStealAluminiumShipId);

		for (int count = dynamicParameters.stealAluminiumDogFoodShipIdList.size() - 1; count >= 0; count--) {
			flag = true;
			for (int count1 = 0; count1 < newFleetTemp.size(); count1++) {
				if (0 != isTheSameClass(dynamicParameters.stealAluminiumDogFoodShipIdList[count], newFleetTemp[count1])) {
					flag = false;
					break;
				}
			}
			if (flag == true) {
				newFleetTemp.append(dynamicParameters.stealAluminiumDogFoodShipIdList[count]);
				dynamicParameters.stealAluminiumDogFoodShipIdList.removeAt(count);
				if (newFleetTemp.size() == 4) {
					break;
				}
			}
		}

		if (newFleetTemp.size() != 4) {
			for (int count = 1; count < newFleetTemp.size(); count++) {
				dynamicParameters.stealAluminiumDogFoodShipIdList.append(newFleetTemp[count]);
			}
			newFleetTemp.clear();
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			currentBehaviourDepth++;

			QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

			if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
				emit(outputLog(0, "reach ship number top"));
				if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
					currentBehaviourDepth--;
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
					emit(behaviourComplete());
					return true;
				}
				else {
					QVector<int> newFleetTemp1;
					newFleetTemp1.append(4291);

					bool flagTemp = false;
					if (currentFleetTemp.size() != newFleetTemp1.size()) {
						flagTemp = true;
					}
					else {
						for (int count = 0; count < newFleetTemp1.size(); count++) {
							if (newFleetTemp1[count] != currentFleetTemp[count]) {
								flagTemp = true;
								break;
							}
						}
					}
					if (flagTemp == true) {
						CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
						createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
						createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

						(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
					}

					currentFleetTemp = newFleetTemp1;

					BehaviourNode behaviourNodeTemp;
					DismantleBehaviourParameter dismantleBehaviourParameterTemp;
					dismantleBehaviourParameterTemp.isDismantleEquipment = true;
					if (dynamicParameters.dismantleShipIdList.size() == 0) {
						if (dynamicParameters.dogFoodShipIdList.size() < 40) {
							dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
							dynamicParameters.dismantleShipIdList.clear();
						}
						else {
							for (int count = 0; count < 40; count++) {
								dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
								dynamicParameters.dogFoodShipIdList.removeLast();
							}
						}
					}
					else if (dynamicParameters.dismantleShipIdList.size() < 40) {
						dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
						dynamicParameters.dismantleShipIdList.clear();
					}
					else {
						for (int count = 0; count < 40; count++) {
							dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
							dynamicParameters.dismantleShipIdList.removeLast();
						}
					}
					behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
					(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
				}
			}

			if (jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].battleProps.oil != jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].battlePropsMax.oil || jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].battleProps.ammo != jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].battlePropsMax.ammo) {
				SupplyBoatBehaviourParameter supplyBoatBehaviourParameterTemp;
				supplyBoatBehaviourParameterTemp.shipId = dynamicParameters.defaultStealAluminiumShipId;
				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyBoatBehaviour, QVariant::fromValue(supplyBoatBehaviourParameterTemp)));
			}

			RemoveEquipmentBehaviourParameter removeEquipmentBehaviourParameterTemp;
			for (int count = 0; count < staticParameters.stealAluminiumShipList.size(); count++) {
				if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.stealAluminiumShipList[count].shipId].shipCid].type != 1 && jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.stealAluminiumShipList[count].shipId].shipCid].type != 2) {
					removeEquipmentBehaviourParameterTemp.shipId = staticParameters.stealAluminiumShipList[count].shipId;
					if (dynamicParameters.defaultStealAluminiumShipId != staticParameters.stealAluminiumShipList[count].shipId) {
						if (jrData.userInfo.userShipVo[staticParameters.stealAluminiumShipList[count].shipId].equipment.size() != 0) {
							for each(int equipmentPos in jrData.userInfo.userShipVo[staticParameters.stealAluminiumShipList[count].shipId].equipment.keys()) {
								removeEquipmentBehaviourParameterTemp.equipmentPos = equipmentPos;
								(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::RemoveEquipmentBehaviour, QVariant::fromValue(removeEquipmentBehaviourParameterTemp)));
							}
						}
					}
					else {
						for each(int equipmentPos in staticParameters.stealAluminiumShipList[count].equipmentInfo.keys()) {
							if (jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].equipment.contains(equipmentPos) && staticParameters.stealAluminiumShipList[count].equipmentInfo[equipmentPos] != jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].equipment[equipmentPos]) {
								removeEquipmentBehaviourParameterTemp.equipmentPos = equipmentPos;
								(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::RemoveEquipmentBehaviour, QVariant::fromValue(removeEquipmentBehaviourParameterTemp)));
							}
						}
					}
				}
			}

			for (int count = 0; count < staticParameters.stealAluminiumShipList.size(); count++) {
				if (dynamicParameters.defaultStealAluminiumShipId == staticParameters.stealAluminiumShipList[count].shipId) {
					if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].shipCid].type != 1 && jrData.initInfo.shipCard[jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].shipCid].type != 2) {
						ChangeEquipmentBehaviourParameter changeEquipmentBehaviourParameterTemp;
						changeEquipmentBehaviourParameterTemp.shipId = dynamicParameters.defaultStealAluminiumShipId;
						for each(int equipmentPos in staticParameters.stealAluminiumShipList[count].equipmentInfo.keys()) {
							if (!jrData.userInfo.userShipVo[dynamicParameters.defaultStealAluminiumShipId].equipment.contains(equipmentPos)) {
								changeEquipmentBehaviourParameterTemp.equipmentPos = equipmentPos;
								changeEquipmentBehaviourParameterTemp.equipmentCid = staticParameters.stealAluminiumShipList[count].equipmentInfo[equipmentPos];
								(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::ChangeEquipmentBehaviour, QVariant::fromValue(changeEquipmentBehaviourParameterTemp)));
							}
						}
					}

					break;
				}
			}

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}
			(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_StealAluminium);

			(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

			executeNextExecutableBehaviour();
		}
	}

	return true;
}

bool BehaviourManager::collectDogFood() {
	bool flagTemp = true;

	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.drop500 != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	for (int count = 0; count < staticParameters.collectDogFood_505FleetInfo.size(); count++) {
		if (3 <= getBrokenStatus(staticParameters.collectDogFood_505FleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].status != 0) {
			flagTemp = false;
			break;
		}
	}
	if (flagTemp == true) {
		currentBehaviourDepth++;

		QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

		if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
			emit(outputLog(0, "reach ship number top"));
			if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else {
				QVector<int> newFleetTemp1;
				newFleetTemp1.append(4291);

				bool flagTemp = false;
				if (currentFleetTemp.size() != newFleetTemp1.size()) {
					flagTemp = true;
				}
				else {
					for (int count = 0; count < newFleetTemp1.size(); count++) {
						if (newFleetTemp1[count] != currentFleetTemp[count]) {
							flagTemp = true;
							break;
						}
					}
				}
				if (flagTemp == true) {
					CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
					createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
					createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

					(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
				}

				currentFleetTemp = newFleetTemp1;

				BehaviourNode behaviourNodeTemp;
				DismantleBehaviourParameter dismantleBehaviourParameterTemp;
				dismantleBehaviourParameterTemp.isDismantleEquipment = true;
				if (dynamicParameters.dismantleShipIdList.size() == 0) {
					if (dynamicParameters.dogFoodShipIdList.size() < 40) {
						dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
						dynamicParameters.dismantleShipIdList.clear();
					}
					else {
						for (int count = 0; count < 40; count++) {
							dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
							dynamicParameters.dogFoodShipIdList.removeLast();
						}
					}
				}
				else if (dynamicParameters.dismantleShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
						dynamicParameters.dismantleShipIdList.removeLast();
					}
				}
				behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
				(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
			}
		}

		flagTemp = false;
		if (currentFleetTemp.size() != staticParameters.collectDogFood_505FleetInfo.size()) {
			flagTemp = true;
		}
		else {
			for (int count = 0; count < staticParameters.collectDogFood_505FleetInfo.size(); count++) {
				if (staticParameters.collectDogFood_505FleetInfo[count] != currentFleetTemp[count]) {
					flagTemp = true;
					break;
				}
			}
		}
		if (flagTemp == true) {
			CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
			createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
			createFleetBehaviourParameterTemp.shipIdList = staticParameters.collectDogFood_505FleetInfo;

			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
		}

		flagTemp = false;
		for (int count = 0; count < staticParameters.collectDogFood_505FleetInfo.size(); count++) {
			if (jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].battlePropsMax.aluminium) {
				flagTemp = true;
				break;
			}
		}
		if (flagTemp == true) {
			SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
			supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.collectDogFood_505FleetInfo;
			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
		}

		(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_CollectDogFood_505);

		(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

		executeNextExecutableBehaviour();
		return true;
	}
	else {
		QVector<int> newFleetTemp;

		if (dynamicParameters.stealOilAndAmmoDogFoodShipIdList.size() != 0) {
			newFleetTemp.append(dynamicParameters.stealOilAndAmmoDogFoodShipIdList.last());
			dynamicParameters.stealOilAndAmmoDogFoodShipIdList.removeLast();
		}
		else if (dynamicParameters.stealAluminiumDogFoodShipIdList.size() != 0) {
			newFleetTemp.append(dynamicParameters.stealAluminiumDogFoodShipIdList.last());
			dynamicParameters.stealAluminiumDogFoodShipIdList.removeLast();
		}

		if (newFleetTemp.size() != 1) {
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			currentBehaviourDepth++;

			QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

			if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
				emit(outputLog(0, "reach ship number top"));
				if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
					currentBehaviourDepth--;
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
					emit(behaviourComplete());
					return true;
				}
				else {
					QVector<int> newFleetTemp1;
					newFleetTemp1.append(4291);

					bool flagTemp = false;
					if (currentFleetTemp.size() != newFleetTemp1.size()) {
						flagTemp = true;
					}
					else {
						for (int count = 0; count < newFleetTemp1.size(); count++) {
							if (newFleetTemp1[count] != currentFleetTemp[count]) {
								flagTemp = true;
								break;
							}
						}
					}
					if (flagTemp == true) {
						CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
						createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
						createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

						(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
					}

					currentFleetTemp = newFleetTemp1;

					BehaviourNode behaviourNodeTemp;
					DismantleBehaviourParameter dismantleBehaviourParameterTemp;
					dismantleBehaviourParameterTemp.isDismantleEquipment = true;
					if (dynamicParameters.dismantleShipIdList.size() == 0) {
						if (dynamicParameters.dogFoodShipIdList.size() < 40) {
							dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
							dynamicParameters.dismantleShipIdList.clear();
						}
						else {
							for (int count = 0; count < 40; count++) {
								dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
								dynamicParameters.dogFoodShipIdList.removeLast();
							}
						}
					}
					else if (dynamicParameters.dismantleShipIdList.size() < 40) {
						dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
						dynamicParameters.dismantleShipIdList.clear();
					}
					else {
						for (int count = 0; count < 40; count++) {
							dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
							dynamicParameters.dismantleShipIdList.removeLast();
						}
					}
					behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
					(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
				}
			}

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp.size(); count++) {
					if (newFleetTemp[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_CollectDogFood_101);

			(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

			executeNextExecutableBehaviour();
		}
	}

	return true;
}

bool BehaviourManager::collectShip() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.drop500 != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	currentBehaviourDepth++;

	QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

	if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
		emit(outputLog(0, "reach ship number top"));
		if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
			currentBehaviourDepth--;
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
		else {
			QVector<int> newFleetTemp1;
			newFleetTemp1.append(4291);

			bool flagTemp = false;
			if (currentFleetTemp.size() != newFleetTemp1.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < newFleetTemp1.size(); count++) {
					if (newFleetTemp1[count] != currentFleetTemp[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			currentFleetTemp = newFleetTemp1;

			BehaviourNode behaviourNodeTemp;
			DismantleBehaviourParameter dismantleBehaviourParameterTemp;
			dismantleBehaviourParameterTemp.isDismantleEquipment = true;
			if (dynamicParameters.dismantleShipIdList.size() == 0) {
				if (dynamicParameters.dogFoodShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
						dynamicParameters.dogFoodShipIdList.removeLast();
					}
				}
			}
			else if (dynamicParameters.dismantleShipIdList.size() < 40) {
				dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
				dynamicParameters.dismantleShipIdList.clear();
			}
			else {
				for (int count = 0; count < 40; count++) {
					dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
					dynamicParameters.dismantleShipIdList.removeLast();
				}
			}
			behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
			(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
		}
	}
	//6-4
	/*
	for (int count = 0; count < staticParameters.collectShip_604FleetInfo.size(); count++) {
		if (count == 1) {
			if (4 == getBrokenStatus(staticParameters.collectShip_604FleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].status == 2) {
				BehaviourNode behaviourNodeTemp;
				behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
				InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
				instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
				instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.collectShip_604FleetInfo[count]);
				behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

				(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
			}
		}
		else {
			if (3 <= getBrokenStatus(staticParameters.collectShip_604FleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].status == 2) {
				BehaviourNode behaviourNodeTemp;
				behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
				InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
				instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
				instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.collectShip_604FleetInfo[count]);
				behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

				(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
			}
		}
	}

	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.collectShip_604FleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.collectShip_604FleetInfo.size(); count++) {
			if (staticParameters.collectShip_604FleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.collectShip_604FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.collectShip_604FleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.collectShip_604FleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.collectShip_604FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_CollectShip_604);
	*/
	//
	//7-1
	/*
	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.collectShip_701FleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.collectShip_701FleetInfo.size(); count++) {
			if (staticParameters.collectShip_701FleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.collectShip_701FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.collectShip_701FleetInfo.size(); count++) {
		if (3 <= getBrokenStatus(staticParameters.collectShip_701FleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.collectShip_701FleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.collectShip_701FleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.collectShip_701FleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.collectShip_701FleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.collectShip_701FleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.collectShip_701FleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.collectShip_701FleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.collectShip_701FleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.collectShip_701FleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.collectShip_701FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_CollectShip_701);
	*/
	//
	//2-5
	/*
	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.collectShip_205FleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.collectShip_205FleetInfo.size(); count++) {
			if (staticParameters.collectShip_205FleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.collectShip_205FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}

	for (int count = 0; count < staticParameters.collectShip_205FleetInfo.size(); count++) {
		if (3 <= getBrokenStatus(staticParameters.collectShip_205FleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.collectShip_205FleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.collectShip_205FleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	flagTemp = false;
	for (int count = 0; count < staticParameters.collectShip_205FleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.collectShip_205FleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.collectShip_205FleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.collectShip_205FleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.collectShip_205FleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.collectShip_205FleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.collectShip_205FleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.collectShip_205FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_CollectShip_205);
	*/
	//
	//7-2
	bool flagTemp = false;
	if (currentFleetTemp.size() != staticParameters.collectShip_702_1FleetInfo.size()) {
		flagTemp = true;
	}
	else {
		for (int count = 0; count < staticParameters.collectShip_702_1FleetInfo.size(); count++) {
			if (staticParameters.collectShip_702_1FleetInfo[count] != currentFleetTemp[count]) {
				flagTemp = true;
				break;
			}
		}
	}
	if (flagTemp == true) {
		CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
		createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		createFleetBehaviourParameterTemp.shipIdList = staticParameters.collectShip_702_1FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
	}
	
	int repairCountTemp = 0;
	for (int count = 0; count < staticParameters.collectShip_702_1FleetInfo.size(); count++) {
		if (3 <= getBrokenStatus(staticParameters.collectShip_702_1FleetInfo[count]) || jrData.userInfo.userShipVo[staticParameters.collectShip_702_1FleetInfo[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(staticParameters.collectShip_702_1FleetInfo[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
			repairCountTemp++;
		}
	}

	emit(outputLog(0, "repair number : " + QString::number(repairCountTemp)));

	flagTemp = false;
	for (int count = 0; count < staticParameters.collectShip_702_1FleetInfo.size(); count++) {
		if (jrData.userInfo.userShipVo[staticParameters.collectShip_702_1FleetInfo[count]].battleProps.oil != jrData.userInfo.userShipVo[staticParameters.collectShip_702_1FleetInfo[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[staticParameters.collectShip_702_1FleetInfo[count]].battleProps.ammo != jrData.userInfo.userShipVo[staticParameters.collectShip_702_1FleetInfo[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[staticParameters.collectShip_702_1FleetInfo[count]].battleProps.aluminium != jrData.userInfo.userShipVo[staticParameters.collectShip_702_1FleetInfo[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = staticParameters.collectShip_702_1FleetInfo;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_CollectShip_702_1);
	//
	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	executeNextExecutableBehaviour();
	return true;
}

bool BehaviourManager::trainShip() {
	QVector<int> newFleetTemp;
	bool flag;

	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	if (dynamicParameters.drop500 != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	for (int count = 0; count < staticParameters.trainingShipList.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.trainingShipList[count].shipId) || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].status != 0 || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].level >= staticParameters.trainingShipList[count].Level) {
			continue;
		}
		if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type != 10 && jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type != 12 && jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type != 2) {
			newFleetTemp.append(staticParameters.trainingShipList[count].shipId);
			break;
		}
	}
	if (newFleetTemp.size() == 0 || jrData.userInfo.userShipVo[newFleetTemp[0]].battleProps.speed >= 27) {
		bool flagTemp = false;
		for (int count = 0; count < staticParameters.trainingShipList.size(); count++) {
			if (4 == getBrokenStatus(staticParameters.trainingShipList[count].shipId) || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].status != 0 || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].level >= staticParameters.trainingShipList[count].Level || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].battleProps.speed >= 27) {
				continue;
			}
			if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type == 10 || jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type == 12 || (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type == 2 && 3 > getBrokenStatus(staticParameters.trainingShipList[count].shipId))) {
				flag = true;
				for (int count1 = 0; count1 < newFleetTemp.size(); count1++) {
					if (0 != isTheSameClass(newFleetTemp[count1], staticParameters.trainingShipList[count].shipId)) {
						flag = false;
						break;
					}
				}
				if (flag == true) {
					newFleetTemp.append(staticParameters.trainingShipList[count].shipId);
					flagTemp = true;
					break;
				}
			}
		}

		if (flagTemp == false) {
			newFleetTemp.clear();
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}
	}
	for (int count = 0; count < staticParameters.trainingShipList.size(); count++) {
		if (4 == getBrokenStatus(staticParameters.trainingShipList[count].shipId) || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].status != 0 || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].level >= staticParameters.trainingShipList[count].Level) {
			continue;
		}
		if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type == 10 || jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type == 12 || (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type == 2 && 3 > getBrokenStatus(staticParameters.trainingShipList[count].shipId))) {
			flag = true;
			for (int count1 = 0; count1 < newFleetTemp.size(); count1++) {
				if (0 != isTheSameClass(newFleetTemp[count1], staticParameters.trainingShipList[count].shipId)) {
					flag = false;
					break;
				}
			}
			if (flag == true) {
				newFleetTemp.append(staticParameters.trainingShipList[count].shipId);
				if (newFleetTemp.size() == 6) {
					break;
				}
			}
		}
	}

	if (newFleetTemp.size() != 6) {
		newFleetTemp.clear();
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}
	else {
		int trainingOilTemp = 0;
		int trainingAmmoTemp = 0;
		for (int count = 0; count < newFleetTemp.size(); count++) {
			trainingOilTemp += jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.oil;
			trainingAmmoTemp += jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.ammo;
		}
		if (dynamicParameters.trainingOil * 5 < trainingOilTemp || dynamicParameters.trainingAmmo * 5 < trainingAmmoTemp) {
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
			emit(behaviourComplete());
			return true;
		}

		currentBehaviourDepth++;

		QVector<int> currentFleetTemp = jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships;

		if (jrData.userInfo.userShipVo.size() >= jrData.userInfo.shipNumTop) {
			emit(outputLog(0, "reach ship number top"));
			if (jrData.userInfo.userShipVo.size() - dynamicParameters.dismantleShipIdList.size() - dynamicParameters.dogFoodShipIdList.size() >= jrData.userInfo.shipNumTop) {
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else {
				QVector<int> newFleetTemp1;
				newFleetTemp1.append(4291);

				bool flagTemp = false;
				if (currentFleetTemp.size() != newFleetTemp1.size()) {
					flagTemp = true;
				}
				else {
					for (int count = 0; count < newFleetTemp1.size(); count++) {
						if (newFleetTemp1[count] != currentFleetTemp[count]) {
							flagTemp = true;
							break;
						}
					}
				}
				if (flagTemp == true) {
					CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
					createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
					createFleetBehaviourParameterTemp.shipIdList = newFleetTemp1;

					(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
				}

				currentFleetTemp = newFleetTemp1;

				BehaviourNode behaviourNodeTemp;
				DismantleBehaviourParameter dismantleBehaviourParameterTemp;
				dismantleBehaviourParameterTemp.isDismantleEquipment = true;
				if (dynamicParameters.dismantleShipIdList.size() == 0) {
					if (dynamicParameters.dogFoodShipIdList.size() < 40) {
						dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dogFoodShipIdList;
						dynamicParameters.dismantleShipIdList.clear();
					}
					else {
						for (int count = 0; count < 40; count++) {
							dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dogFoodShipIdList.last());
							dynamicParameters.dogFoodShipIdList.removeLast();
						}
					}
				}
				else if (dynamicParameters.dismantleShipIdList.size() < 40) {
					dismantleBehaviourParameterTemp.dismantleShipIdList = dynamicParameters.dismantleShipIdList;
					dynamicParameters.dismantleShipIdList.clear();
				}
				else {
					for (int count = 0; count < 40; count++) {
						dismantleBehaviourParameterTemp.dismantleShipIdList.append(dynamicParameters.dismantleShipIdList.last());
						dynamicParameters.dismantleShipIdList.removeLast();
					}
				}
				behaviourNodeTemp.behaviourType = BehaviourType::DismantleBehaviour;
				(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::DismantleBehaviour, QVariant::fromValue(dismantleBehaviourParameterTemp)));
			}
		}

		bool flagTemp = false;
		if (currentFleetTemp.size() != newFleetTemp.size()) {
			flagTemp = true;
		}
		else {
			for (int count = 0; count < newFleetTemp.size(); count++) {
				if (newFleetTemp[count] != currentFleetTemp[count]) {
					flagTemp = true;
					break;
				}
			}
		}
		if (flagTemp == true) {
			CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
			createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
			createFleetBehaviourParameterTemp.shipIdList = newFleetTemp;

			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
		}

		flagTemp = false;
		for (int count = 0; count < newFleetTemp.size(); count++) {
			if (jrData.userInfo.userShipVo[newFleetTemp[count]].battleProps.oil != jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[newFleetTemp[count]].battleProps.ammo != jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[newFleetTemp[count]].battleProps.aluminium != jrData.userInfo.userShipVo[newFleetTemp[count]].battlePropsMax.aluminium) {
				flagTemp = true;
				break;
			}
		}
		if (flagTemp == true) {
			SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
			supplyMultiBoatBehaviourParameterTemp.shipIdList = newFleetTemp;

			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
		}

		RemoveEquipmentBehaviourParameter removeEquipmentBehaviourParameterTemp;
		for (int count = 0; count < staticParameters.trainingShipList.size(); count++) {
			if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type != 1 && jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type != 2) {
				removeEquipmentBehaviourParameterTemp.shipId = staticParameters.trainingShipList[count].shipId;
				if (!newFleetTemp.contains(staticParameters.trainingShipList[count].shipId)) {
					if (jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].equipment.size() != 0) {
						for each(int equipmentPos in jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].equipment.keys()) {
							removeEquipmentBehaviourParameterTemp.equipmentPos = equipmentPos;
							(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::RemoveEquipmentBehaviour, QVariant::fromValue(removeEquipmentBehaviourParameterTemp)));
						}
					}
				}
				else {
					for each(int equipmentPos in jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].equipment.keys()) {
						if (!staticParameters.trainingShipList[count].equipmentInfo.contains(equipmentPos) || staticParameters.trainingShipList[count].equipmentInfo[equipmentPos] != jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].equipment[equipmentPos]) {
							removeEquipmentBehaviourParameterTemp.equipmentPos = equipmentPos;
							(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::RemoveEquipmentBehaviour, QVariant::fromValue(removeEquipmentBehaviourParameterTemp)));
						}
					}
				}
			}
		}

		for (int count = 0; count < staticParameters.trainingShipList.size(); count++) {
			if (newFleetTemp.contains(staticParameters.trainingShipList[count].shipId)) {
				if (jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type != 1 && jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type != 2) {
					ChangeEquipmentBehaviourParameter changeEquipmentBehaviourParameterTemp;
					changeEquipmentBehaviourParameterTemp.shipId = staticParameters.trainingShipList[count].shipId;
					for each(int equipmentPos in staticParameters.trainingShipList[count].equipmentInfo.keys()) {
						if (!jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].equipment.contains(equipmentPos) || jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].equipment[equipmentPos] != staticParameters.trainingShipList[count].equipmentInfo[equipmentPos]) {
							changeEquipmentBehaviourParameterTemp.equipmentPos = equipmentPos;
							changeEquipmentBehaviourParameterTemp.equipmentCid = staticParameters.trainingShipList[count].equipmentInfo[equipmentPos];
							(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::ChangeEquipmentBehaviour, QVariant::fromValue(changeEquipmentBehaviourParameterTemp)));
						}
					}
				}
			}
		}

		(*getParentBehaviour()).childBehaviour.push_back(staticParameters.behaviourNode_PveWar_TrainShip);

		(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

		executeNextExecutableBehaviour();
	}

	return true;
}

bool BehaviourManager::createFleet() {
	sendCreateFleetRequest1();

	return true;
}

bool BehaviourManager::repairShipStart() {
	sendRepairShipStartRequest1();

	return true;
}

bool BehaviourManager::repairShipComplete() {
	sendRepairShipCompleteRequest1();

	return true;
}

bool BehaviourManager::instantRepairMultiShip() {
	InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<InstantRepairMultiShipBehaviourParameter>();

	if (!jrData.userInfo.packageVo.contains(541) || jrData.userInfo.packageVo[541].num < instantRepairMultiShipBehaviourParameterTemp.shipIdList.size()) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	sendInstantRepairMultiShipRequest1();

	return true;
}

bool BehaviourManager::removeEquipment() {
	sendRemoveEquipmentRequest1();

	return true;
}

bool BehaviourManager::changeEquipment() {
	ChangeEquipmentBehaviourParameter changeEquipmentBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<ChangeEquipmentBehaviourParameter>();

	if (!jrData.userInfo.equipmentVo.contains(changeEquipmentBehaviourParameterTemp.equipmentCid) || jrData.userInfo.equipmentVo[changeEquipmentBehaviourParameterTemp.equipmentCid].num < 1) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	sendChangeEquipmentRequest1();

	return true;
}

bool BehaviourManager::supplyMultiBoat() {
	SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<SupplyMultiBoatBehaviourParameter>();

	int oilTemp = 0;
	int ammoTemp = 0;
	int aluminiumTemp = 0;

	for (int count = 0; count < supplyMultiBoatBehaviourParameterTemp.shipIdList.size(); count++) {
		oilTemp += jrData.userInfo.userShipVo[supplyMultiBoatBehaviourParameterTemp.shipIdList[count]].battlePropsMax.oil - jrData.userInfo.userShipVo[supplyMultiBoatBehaviourParameterTemp.shipIdList[count]].battleProps.oil;
		ammoTemp += jrData.userInfo.userShipVo[supplyMultiBoatBehaviourParameterTemp.shipIdList[count]].battlePropsMax.ammo - jrData.userInfo.userShipVo[supplyMultiBoatBehaviourParameterTemp.shipIdList[count]].battleProps.ammo;
		aluminiumTemp += jrData.userInfo.userShipVo[supplyMultiBoatBehaviourParameterTemp.shipIdList[count]].battlePropsMax.aluminium - jrData.userInfo.userShipVo[supplyMultiBoatBehaviourParameterTemp.shipIdList[count]].battleProps.aluminium;
	}

	updateResource();
	if (oilTemp > jrData.userInfo.userResourceVo.oil || ammoTemp > jrData.userInfo.userResourceVo.ammo || aluminiumTemp > jrData.userInfo.userResourceVo.aluminium) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	sendSupplyMultiBoatRequest1();

	return true;
}

bool BehaviourManager::supplyBoat() {
	SupplyBoatBehaviourParameter supplyBoatBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<SupplyBoatBehaviourParameter>();

	int oilTemp = jrData.userInfo.userShipVo[supplyBoatBehaviourParameterTemp.shipId].battlePropsMax.oil - jrData.userInfo.userShipVo[supplyBoatBehaviourParameterTemp.shipId].battleProps.oil;
	int ammoTemp = jrData.userInfo.userShipVo[supplyBoatBehaviourParameterTemp.shipId].battlePropsMax.ammo - jrData.userInfo.userShipVo[supplyBoatBehaviourParameterTemp.shipId].battleProps.ammo;
	int aluminiumTemp = jrData.userInfo.userShipVo[supplyBoatBehaviourParameterTemp.shipId].battlePropsMax.aluminium - jrData.userInfo.userShipVo[supplyBoatBehaviourParameterTemp.shipId].battleProps.aluminium;

	updateResource();
	if (oilTemp > jrData.userInfo.userResourceVo.oil || ammoTemp > jrData.userInfo.userResourceVo.ammo || aluminiumTemp > jrData.userInfo.userResourceVo.aluminium) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	sendSupplyBoatRequest1();

	return true;
}

bool BehaviourManager::pveWar() {
	sendPveWarRequest1();

	return true;
}

bool BehaviourManager::pveExploreStart() {
	sendPveExploreStartRequest1();

	return true;
}

bool BehaviourManager::pveExploreComplete() {
	sendPveExploreCompleteRequest1();

	return true;
}

bool BehaviourManager::checkPvpStatus() {
	sendCheckPvpStatusRequest1();

	return true;
}

bool BehaviourManager::updatePvpStatus() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
		emit(behaviourComplete());
		return true;
	}

	for (int count = 0; count < dynamicParameters.pvpUserInfoList.size(); count++) {
		if (dynamicParameters.pvpUserInfoList[count].resultLevel == 0) {
			currentBehaviourDepth++;

			bool flagTemp = false;
			if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size() != staticParameters.pvpFleetConfig.size()) {
				flagTemp = true;
			}
			else {
				for (int count = 0; count < staticParameters.pvpFleetConfig.size(); count++) {
					if (staticParameters.pvpFleetConfig[count] != jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]) {
						flagTemp = true;
						break;
					}
				}
			}
			if (flagTemp == true) {
				CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
				createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
				createFleetBehaviourParameterTemp.shipIdList = staticParameters.pvpFleetConfig;

				(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
			}

			PvpWarBehaviourParameter pvpWarBehaviourParameterTemp;
			pvpWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
			pvpWarBehaviourParameterTemp.fuid = dynamicParameters.pvpUserInfoList[count].uid;
			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::PvpWarBehaviour, QVariant::fromValue(pvpWarBehaviourParameterTemp)));

			(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

			executeNextExecutableBehaviour();

			return true;
		}
	}

	dynamicParameters.canPvp = false;

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());

	emit(behaviourComplete());
	return true;
}

bool BehaviourManager::updateCampaignStatus() {
	currentBehaviourDepth++;

	for (int count = 0; count < dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet.size(); count++) {
		if (4 == getBrokenStatus(dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]) || ((jrData.initInfo.shipCard[jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].shipCid].type == 1 || jrData.initInfo.shipCard[jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].shipCid].type == 2) && 3 <= getBrokenStatus(dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count])) || jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].status == 2) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::InstantRepairMultiShipBehaviour;
			InstantRepairMultiShipBehaviourParameter instantRepairMultiShipBehaviourParameterTemp;
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.clear();
			instantRepairMultiShipBehaviourParameterTemp.shipIdList.append(dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]);
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(instantRepairMultiShipBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	bool flagTemp = false;
	for (int count = 0; count < dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet.size(); count++) {
		if (jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].battleProps.oil != jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].battlePropsMax.oil || jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].battleProps.ammo != jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].battlePropsMax.ammo || jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].battleProps.aluminium != jrData.userInfo.userShipVo[dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet[count]].battlePropsMax.aluminium) {
			flagTemp = true;
			break;
		}
	}
	if (flagTemp == true) {
		SupplyMultiBoatBehaviourParameter supplyMultiBoatBehaviourParameterTemp;
		supplyMultiBoatBehaviourParameterTemp.shipIdList = dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet;

		(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::SupplyMultiBoatBehaviour, QVariant::fromValue(supplyMultiBoatBehaviourParameterTemp)));
	}

	CampaignBehaviourParameter campaignBehaviourParameterTemp;
	campaignBehaviourParameterTemp.campaignFleet = dynamicParameters.currentCampaignInfo.campaignInfo.campaignFleet;
	campaignBehaviourParameterTemp.campaignId = staticParameters.defaultCampaignId;
	(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CampaignBehaviour, QVariant::fromValue(campaignBehaviourParameterTemp)));

	(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::CampaignFinished, QVariant());

	executeNextExecutableBehaviour();

	return true;
}

bool BehaviourManager::pvpWar() {
	sendPvpWarRequest1();

	return true;
}

bool BehaviourManager::getCampaignFleet() {
	sendGetCampaignFleetRequest1();

	return true;
}

bool BehaviourManager::campaign() {
	sendCampaignRequest1();

	return true;
}

bool BehaviourManager::dismantle() {
	sendDismantleRequest1();

	return true;
}

bool BehaviourManager::checkSpoilShop() {
	sendCheckSpoilsShopRequest1();

	return true;
}

bool BehaviourManager::getInitializationData() {
	sendGetInitializationDataRequest1();

	return true;
}

bool BehaviourManager::updateTaskAwardStatus() {
	bool completeFlag;
	QVector<int> taskCidListTemp;

	taskCidListTemp.clear();
	dynamicParameters.canCompleteTask = false;
	for each(int taskCidTemp in jrData.userInfo.taskVo.keys()) {
		completeFlag = true;
		for (int count = 0; count < jrData.userInfo.taskVo[taskCidTemp].condition.size(); count++) {
			if (jrData.userInfo.taskVo[taskCidTemp].condition[count].finishedAmount < jrData.userInfo.taskVo[taskCidTemp].condition[count].totalAmount) {
				completeFlag = false;
				break;
			}
		}

		if (completeFlag == true) {
			taskCidListTemp.append(taskCidTemp);
		}
		else {
			if (dynamicParameters.canCompleteTask == false && staticParameters.canCompleteTaskCidList.contains(taskCidTemp)) {
				dynamicParameters.canCompleteTask = true;
			}
		}
	}

	if (taskCidListTemp.size() != 0) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::GetTaskAward, QVariant::fromValue(taskCidListTemp));
	}

	return true;
}

bool BehaviourManager::updateLoginAwardStatus() {
	if (jrData.userInfo.marketingData.continueLoginAward.canGetDay != -1) {
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::GetLoginAward, QVariant());
	}

	return true;
}

bool BehaviourManager::getTaskAward() {
	GetTaskAwardBehaviourParameter getTaskAwardBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<GetTaskAwardBehaviourParameter>();
	
	if (jrData.userInfo.taskVo.contains(getTaskAwardBehaviourParameterTemp.taskId)) {//attention
		sendGetTaskAwardRequest1();
	}
	else {
		emit(behaviourComplete());
	}

	return true;
}

bool BehaviourManager::getLoginAward() {
	if (jrData.userInfo.marketingData.continueLoginAward.canGetDay != -1) {//attention
		sendGetLoginAwardRequest1();
	}
	else {
		emit(behaviourComplete());
	}

	return true;
}

bool BehaviourManager::initStaticParameters() {
	staticParameters.initInfoFilePath = "D:\\Documents\\VisualStudio2015Projects\\jrTest12\\jrTest12\\tempData\\initData2_10_0.json";

	staticParameters.maxResponseDelay = 60000;
	staticParameters.maxRequestRepeatNum = 30;
	staticParameters.activeFleetId = 4;

	staticParameters.behaviourNode_Login.behaviourType = BehaviourType::LoginBehaviour;
	LoginBehaviourParameter loginBehaviourParameterTemp;
	loginBehaviourParameterTemp.username = "";
	loginBehaviourParameterTemp.password = "";
	loginBehaviourParameterTemp.serverId = 12;
	staticParameters.behaviourNode_Login.behaviourParameters = QVariant::fromValue(loginBehaviourParameterTemp);

	staticParameters.behaviourNode_PveWar_StealOil.behaviourType = BehaviourType::PveWarBehaviour;
	PveWarBehaviourParameter pveWarBehaviourParameterTemp;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 2;
	pveWarBehaviourParameterTemp.pveId = 202;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	PveWarRouteInformation_OneNode routeInfo_OneNodeTemp;
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(20201, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20201].childNodes.insert(20202, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20201].childNodes[20202].childNodes.insert(20204, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_StealOil.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.behaviourNode_PveWar_StealAmmo.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 3;
	pveWarBehaviourParameterTemp.pveId = 301;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(30101, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[30101].childNodes.insert(30102, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[30101].childNodes[30102].childNodes.insert(30104, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_StealAmmo.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.behaviourNode_PveWar_StealAluminium.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 4;
	pveWarBehaviourParameterTemp.pveId = 403;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(40301, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[40301].childNodes.insert(40303, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[40301].childNodes[40303].childNodes.insert(40305, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_StealAluminium.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.behaviourNode_PveWar_TrainShip.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 6;
	pveWarBehaviourParameterTemp.pveId = 601;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(60101, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 5;
	pveWarBehaviourParameterTemp.routeInfo[60101].childNodes.insert(60102, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_TrainShip.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.behaviourNode_PveWar_CollectDogFood_101.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 1;
	pveWarBehaviourParameterTemp.pveId = 101;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(10101, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[10101].childNodes.insert(10102, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CollectDogFood_101.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.behaviourNode_PveWar_CollectDogFood_505.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 5;
	pveWarBehaviourParameterTemp.pveId = 505;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(50501, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[50501].childNodes.insert(50504, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[50501].childNodes[50504].childNodes.insert(50507, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 4;
	pveWarBehaviourParameterTemp.routeInfo[50501].childNodes[50504].childNodes[50507].childNodes.insert(50510, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CollectDogFood_505.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.collectDogFood_505FleetInfo.clear();
	staticParameters.collectDogFood_505FleetInfo.append(75347);
	staticParameters.collectDogFood_505FleetInfo.append(73481);
	staticParameters.collectDogFood_505FleetInfo.append(36439);
	staticParameters.collectDogFood_505FleetInfo.append(87826);
	staticParameters.collectDogFood_505FleetInfo.append(57613);
	staticParameters.collectDogFood_505FleetInfo.append(18221);

	staticParameters.behaviourNode_PveWar_StealPants.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 2;
	pveWarBehaviourParameterTemp.pveId = 201;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(20101, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20101].childNodes.insert(20103, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20101].childNodes[20103].childNodes.insert(20105, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20101].childNodes[20103].childNodes[20105].childNodes.insert(20107, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_StealPants.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.stealPantsFleetConfig.clear();
	staticParameters.stealPantsFleetConfig.append(2201);
	staticParameters.stealPantsFleetConfig.append(2035);
	staticParameters.stealPantsFleetConfig.append(415);
	staticParameters.stealPantsFleetConfig.append(3421);

	staticParameters.behaviourNode_PveWar_CollectShip_604.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 6;
	pveWarBehaviourParameterTemp.pveId = 604;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(60401, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[60401].childNodes.insert(60402, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[60401].childNodes[60402].childNodes.insert(60403, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 5;
	pveWarBehaviourParameterTemp.routeInfo[60401].childNodes[60402].childNodes[60403].childNodes.insert(60406, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CollectShip_604.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.collectShip_604FleetInfo.clear();
	staticParameters.collectShip_604FleetInfo.append(32424);
	staticParameters.collectShip_604FleetInfo.append(325);
	staticParameters.collectShip_604FleetInfo.append(7874);
	staticParameters.collectShip_604FleetInfo.append(406);
	staticParameters.collectShip_604FleetInfo.append(134);
	staticParameters.collectShip_604FleetInfo.append(1075);

	staticParameters.behaviourNode_PveWar_CollectShip_701.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 7;
	pveWarBehaviourParameterTemp.pveId = 701;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(70101, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes.insert(70102, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = true;
	routeInfo_OneNodeTemp.mustSkip = true;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes.insert(70104, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes[70104].childNodes.insert(70107, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes[70104].childNodes.insert(70108, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes[70104].childNodes[70107].childNodes.insert(70113, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes[70104].childNodes[70108].childNodes.insert(70110, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes[70104].childNodes[70107].childNodes[70113].childNodes.insert(70114, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes[70104].childNodes[70108].childNodes[70110].childNodes.insert(70114, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[70101].childNodes[70102].childNodes[70104].childNodes[70108].childNodes[70110].childNodes.insert(70115, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CollectShip_701.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.collectShip_701FleetInfo.clear();
	staticParameters.collectShip_701FleetInfo.append(216);
	staticParameters.collectShip_701FleetInfo.append(211);
	staticParameters.collectShip_701FleetInfo.append(1226);
	staticParameters.collectShip_701FleetInfo.append(33641);
	staticParameters.collectShip_701FleetInfo.append(134);
	staticParameters.collectShip_701FleetInfo.append(1075);

	staticParameters.behaviourNode_PveWar_CollectShip_702_1.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 7;
	pveWarBehaviourParameterTemp.pveId = 702;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(70201, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70201].childNodes.insert(70202, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70201].childNodes[70202].childNodes.insert(70205, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = true;
	routeInfo_OneNodeTemp.mustSkip = true;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70201].childNodes[70202].childNodes[70205].childNodes.insert(70209, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70201].childNodes[70202].childNodes[70205].childNodes[70209].childNodes.insert(70212, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 5;
	pveWarBehaviourParameterTemp.routeInfo[70201].childNodes[70202].childNodes[70205].childNodes[70209].childNodes[70212].childNodes.insert(70214, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CollectShip_702_1.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.collectShip_702_1FleetInfo.clear();
	staticParameters.collectShip_702_1FleetInfo.append(32424);
	staticParameters.collectShip_702_1FleetInfo.append(7874);
	staticParameters.collectShip_702_1FleetInfo.append(99103);
	staticParameters.collectShip_702_1FleetInfo.append(95444);
	staticParameters.collectShip_702_1FleetInfo.append(134);
	staticParameters.collectShip_702_1FleetInfo.append(1075);

	staticParameters.behaviourNode_PveWar_CollectShip_702_2.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 7;
	pveWarBehaviourParameterTemp.pveId = 702;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(70201, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[70201].childNodes.insert(70207, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 4;
	pveWarBehaviourParameterTemp.routeInfo[70201].childNodes[70207].childNodes.insert(70213, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CollectShip_702_2.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.collectShip_702_2FleetInfo.clear();
	staticParameters.collectShip_702_2FleetInfo.append(75347);
	staticParameters.collectShip_702_2FleetInfo.append(73481);
	staticParameters.collectShip_702_2FleetInfo.append(36439);
	staticParameters.collectShip_702_2FleetInfo.append(87826);
	staticParameters.collectShip_702_2FleetInfo.append(1226);
	staticParameters.collectShip_702_2FleetInfo.append(57613);

	staticParameters.behaviourNode_PveWar_CollectShip_205.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 2;
	pveWarBehaviourParameterTemp.pveId = 205;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(20501, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes.insert(20502, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes.insert(20503, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes.insert(20504, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = true;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes.insert(20505, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes.insert(20506, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20504].childNodes.insert(20507, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20504].childNodes.insert(20508, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = true;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20505].childNodes.insert(20509, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20506].childNodes.insert(20510, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20504].childNodes[20507].childNodes.insert(20511, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20504].childNodes[20508].childNodes.insert(20511, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = true;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20505].childNodes[20509].childNodes.insert(20512, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20506].childNodes[20510].childNodes.insert(20513, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20506].childNodes[20510].childNodes.insert(20514, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20506].childNodes[20510].childNodes.insert(20515, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20501].childNodes[20502].childNodes[20503].childNodes[20505].childNodes[20509].childNodes[20512].childNodes.insert(20516, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CollectShip_205.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.collectShip_205FleetInfo.clear();
	staticParameters.collectShip_205FleetInfo.append(1782);
	staticParameters.collectShip_205FleetInfo.append(83032);
	staticParameters.collectShip_205FleetInfo.append(87826);
	staticParameters.collectShip_205FleetInfo.append(7874);
	staticParameters.collectShip_205FleetInfo.append(134);
	staticParameters.collectShip_205FleetInfo.append(1075);

	staticParameters.behaviourNode_PveWar_CompleteTask_104.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 1;
	pveWarBehaviourParameterTemp.pveId = 104;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(10401, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[10401].childNodes.insert(10402, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[10401].childNodes[10402].childNodes.insert(10404, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[10401].childNodes[10402].childNodes[10404].childNodes.insert(10406, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CompleteTask_104.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.completeTask_104FleetInfo.clear();
	staticParameters.completeTask_104FleetInfo.append(2201);
	staticParameters.completeTask_104FleetInfo.append(2035);
	staticParameters.completeTask_104FleetInfo.append(415);
	staticParameters.completeTask_104FleetInfo.append(3421);

	staticParameters.behaviourNode_PveWar_CompleteTask_201.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 2;
	pveWarBehaviourParameterTemp.pveId = 201;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(20101, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20101].childNodes.insert(20103, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo[20101].childNodes[20103].childNodes.insert(20105, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[20101].childNodes[20103].childNodes[20105].childNodes.insert(20107, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CompleteTask_201.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.completeTask_201FleetInfo.clear();
	staticParameters.completeTask_201FleetInfo.append(2201);
	staticParameters.completeTask_201FleetInfo.append(2035);
	staticParameters.completeTask_201FleetInfo.append(415);
	staticParameters.completeTask_201FleetInfo.append(3421);

	staticParameters.behaviourNode_PveWar_CompleteTask_302.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 3;
	pveWarBehaviourParameterTemp.pveId = 302;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(30201, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[30201].childNodes.insert(30204, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[30201].childNodes[30204].childNodes.insert(30206, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 2;
	pveWarBehaviourParameterTemp.routeInfo[30201].childNodes[30204].childNodes[30206].childNodes.insert(30208, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CompleteTask_302.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.completeTask_302FleetInfo.clear();
	staticParameters.completeTask_302FleetInfo.append(2201);
	staticParameters.completeTask_302FleetInfo.append(240);
	staticParameters.completeTask_302FleetInfo.append(2035);
	staticParameters.completeTask_302FleetInfo.append(415);
	staticParameters.completeTask_302FleetInfo.append(1502);
	staticParameters.completeTask_302FleetInfo.append(3421);

	staticParameters.behaviourNode_PveWar_CompleteTask_601.behaviourType = BehaviourType::PveWarBehaviour;
	pveWarBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
	pveWarBehaviourParameterTemp.pveChapter = 6;
	pveWarBehaviourParameterTemp.pveId = 601;
	pveWarBehaviourParameterTemp.routeInfo.clear();
	routeInfo_OneNodeTemp.canDoNightWar = false;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 1;
	pveWarBehaviourParameterTemp.routeInfo.insert(60101, routeInfo_OneNodeTemp);
	routeInfo_OneNodeTemp.canDoNightWar = true;
	routeInfo_OneNodeTemp.canSkip = false;
	routeInfo_OneNodeTemp.mustSkip = false;
	routeInfo_OneNodeTemp.defaultFormation = 4;
	pveWarBehaviourParameterTemp.routeInfo[60101].childNodes.insert(60102, routeInfo_OneNodeTemp);
	pveWarBehaviourParameterTemp.pveNodeIter = pveWarBehaviourParameterTemp.routeInfo.begin();
	staticParameters.behaviourNode_PveWar_CompleteTask_601.behaviourParameters = QVariant::fromValue(pveWarBehaviourParameterTemp);

	staticParameters.completeTask_601FleetInfo.clear();
	staticParameters.completeTask_601FleetInfo.append(75347);

	staticParameters.stealAluminiumShipList.clear();

	ShipConfigInformation shipConfigInformationTemp;
	shipConfigInformationTemp.shipId = 101;//标枪
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);

	shipConfigInformationTemp.shipId = 3801;//初雪
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);

	shipConfigInformationTemp.shipId = 2023;//凉月
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);

	shipConfigInformationTemp.shipId = 3549;//黑背豺
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);

	shipConfigInformationTemp.shipId = 45432;//秋月
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);
	
	shipConfigInformationTemp.shipId = 24820;//空想
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);

	shipConfigInformationTemp.shipId = 2417;//空想
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);

	shipConfigInformationTemp.shipId = 1311;//空想
	shipConfigInformationTemp.equipmentInfo.clear();
	shipConfigInformationTemp.equipmentInfo.insert(0, 10024021);
	shipConfigInformationTemp.equipmentInfo.insert(1, 10011721);
	shipConfigInformationTemp.equipmentInfo.insert(2, 10011721);
	staticParameters.stealAluminiumShipList.append(shipConfigInformationTemp);

	staticParameters.reservedShipCidList.clear();
	staticParameters.reservedShipCidList.append(10009911);//空想
	staticParameters.reservedShipCidList.append(10021113);//卡约•杜伊里奥
	staticParameters.reservedShipCidList.append(10012712);//独角兽
	staticParameters.reservedShipCidList.append(10003113);//大黄蜂
	//staticParameters.reservedShipCidList.append(10008211);//萤火虫
	//staticParameters.reservedShipCidList.append(10009711);//果敢
	staticParameters.reservedShipCidList.append(10002812);//突击者
	staticParameters.reservedShipCidList.append(10001613);//榛名

	staticParameters.repairShipIdList.clear();
	staticParameters.repairShipIdList.append(272);//海伦娜
	staticParameters.repairShipIdList.append(27122);//声望_1
	staticParameters.repairShipIdList.append(1);//萤火虫
	staticParameters.repairShipIdList.append(216);//胡德_1
	staticParameters.repairShipIdList.append(7044);//埃塞克斯
	//staticParameters.repairShipIdList.append(30092);//萨拉托加_1
	staticParameters.repairShipIdList.append(30054);//翔鹤
	staticParameters.repairShipIdList.append(40003);//企业
	//staticParameters.repairShipIdList.append(7874);//大凤
	staticParameters.repairShipIdList.append(7055);//瑞鹤
	staticParameters.repairShipIdList.append(5597);//反击
	staticParameters.repairShipIdList.append(1158);//科罗拉多
	staticParameters.repairShipIdList.append(1599);//z16
	staticParameters.repairShipIdList.append(104);//敷波
	staticParameters.repairShipIdList.append(415);//信赖
	staticParameters.repairShipIdList.append(325);//欧根亲王
	staticParameters.repairShipIdList.append(211);//威奇塔
	staticParameters.repairShipIdList.append(1328);//逸仙
	staticParameters.repairShipIdList.append(356);//黎塞留
	staticParameters.repairShipIdList.append(1165);//提尔比茨
	staticParameters.repairShipIdList.append(366);//声望
	//staticParameters.repairShipIdList.append(134);//列克星敦
	//staticParameters.repairShipIdList.append(1075);//萨拉托加
	staticParameters.repairShipIdList.append(1226);//拉菲
	staticParameters.repairShipIdList.append(33641);//弗莱彻
	staticParameters.repairShipIdList.append(474);//空想
	staticParameters.repairShipIdList.append(2806);//纳尔逊
	staticParameters.repairShipIdList.append(645);//罗德尼
	staticParameters.repairShipIdList.append(1299);//俾斯麦
	staticParameters.repairShipIdList.append(1660);//威尔士亲王
	staticParameters.repairShipIdList.append(18741);//威尔士亲王_1
	staticParameters.repairShipIdList.append(255);//突击者
	staticParameters.repairShipIdList.append(32426);//加贺
	staticParameters.repairShipIdList.append(21635);//赤城
	staticParameters.repairShipIdList.append(1782);//安德烈亚.多利亚
	staticParameters.repairShipIdList.append(186);//日向
	staticParameters.repairShipIdList.append(292);//伊势
	staticParameters.repairShipIdList.append(8810);//龙田
	//staticParameters.repairShipIdList.append(32424);//赤城_1
	staticParameters.repairShipIdList.append(7248);//紫石英
	staticParameters.repairShipIdList.append(116);//基阿特
	staticParameters.repairShipIdList.append(21937);//果敢
	staticParameters.repairShipIdList.append(117);//z22
	staticParameters.repairShipIdList.append(105);//z21
	//staticParameters.repairShipIdList.append(95444);//齐柏林伯爵
	staticParameters.repairShipIdList.append(9259);//突击者_1
	staticParameters.repairShipIdList.append(5497);//宁海
	staticParameters.repairShipIdList.append(106);//五十铃
	staticParameters.repairShipIdList.append(30096);//追赶者
	staticParameters.repairShipIdList.append(8316);//博格
	staticParameters.repairShipIdList.append(94713);//果敢_1
	//staticParameters.repairShipIdList.append(99103);//亚特兰大

	TrainingShipConfigInformation TrainingShipInfoTemp;
	TrainingShipInfoTemp.shipId = 83032;//U47_1
	TrainingShipInfoTemp.Level = 66;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10015421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 87829;//射水鱼_2
	TrainingShipInfoTemp.Level = 80;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10015421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 59204;//大青花鱼_2
	TrainingShipInfoTemp.Level = 80;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10015421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 95622;//射水鱼_3
	TrainingShipInfoTemp.Level = 80;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10015421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 5408;//M1
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10015421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 8618;//絮库夫
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10015421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10015421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 153;//龙田
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 406;//飞鹰
	TrainingShipInfoTemp.Level = 95;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10007121);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10007121);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10007121);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 633;//隼鹰
	TrainingShipInfoTemp.Level = 95;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10007421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10007421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10007421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 1196;//普林斯顿
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10007421);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10007421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10007421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 36455;//空想
	TrainingShipInfoTemp.Level = 60;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 45912;//空想
	TrainingShipInfoTemp.Level = 60;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 290;//鲍尔
	TrainingShipInfoTemp.Level = 80;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 228;//弗兰克·诺克斯
	TrainingShipInfoTemp.Level = 80;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 243;//奥希金斯
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 9492;//海伦娜
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 41613;//z28
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 36496;//z24
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 5449;//平海
	TrainingShipInfoTemp.Level = 100;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	TrainingShipInfoTemp.equipmentInfo.insert(2, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 74919;//空想
	TrainingShipInfoTemp.Level = 60;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 45695;//凉月
	TrainingShipInfoTemp.Level = 42;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 77482;//萤火虫
	TrainingShipInfoTemp.Level = 35;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 73291;//紫石英
	TrainingShipInfoTemp.Level = 60;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 78820;//萤火虫
	TrainingShipInfoTemp.Level = 35;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	TrainingShipInfoTemp.shipId = 34393;//紫石英
	TrainingShipInfoTemp.Level = 60;
	TrainingShipInfoTemp.equipmentInfo.clear();
	TrainingShipInfoTemp.equipmentInfo.insert(0, 10008621);
	TrainingShipInfoTemp.equipmentInfo.insert(1, 10008421);
	staticParameters.trainingShipList.append(TrainingShipInfoTemp);

	staticParameters.defaultCollectStrategy = CollectStrategy::CollectShipStrategy;

	staticParameters.pveExploreConfig.clear();
	staticParameters.pveExploreConfig.insert(1, 20001);
	staticParameters.pveExploreConfig.insert(2, 50004);
	staticParameters.pveExploreConfig.insert(3, 30002);//40001
	staticParameters.pveExploreConfig.insert(4, 10002);//50003

	staticParameters.activeFleetPveExploreFleetConfig.clear();
	staticParameters.activeFleetPveExploreFleetConfig.append(468);//134
	staticParameters.activeFleetPveExploreFleetConfig.append(1);
	staticParameters.activeFleetPveExploreFleetConfig.append(1165);
	staticParameters.activeFleetPveExploreFleetConfig.append(1782);
	staticParameters.activeFleetPveExploreFleetConfig.append(1339);
	staticParameters.activeFleetPveExploreFleetConfig.append(255);

	staticParameters.canCompleteTaskCidList.clear();
	staticParameters.canCompleteTaskCidList.append(2300333);
	staticParameters.canCompleteTaskCidList.append(2300433);
	staticParameters.canCompleteTaskCidList.append(2300533);
	staticParameters.canCompleteTaskCidList.append(2200232);
	staticParameters.canCompleteTaskCidList.append(2200732);
	staticParameters.canCompleteTaskCidList.append(2201532);
	staticParameters.canCompleteTaskCidList.append(2200932);
	staticParameters.canCompleteTaskCidList.append(2201732);
	staticParameters.canCompleteTaskCidList.append(2200632);
	staticParameters.canCompleteTaskCidList.append(2201432);
	staticParameters.canCompleteTaskCidList.append(2201832);
	staticParameters.canCompleteTaskCidList.append(2201132);
	staticParameters.canCompleteTaskCidList.append(2200832);
	staticParameters.canCompleteTaskCidList.append(2201632);

	staticParameters.completeTaskInfo_2300333.fleetInfo = staticParameters.completeTask_104FleetInfo;
	staticParameters.completeTaskInfo_2300333.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_104;

	staticParameters.completeTaskInfo_2300433.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2300433.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2300533.fleetInfo = staticParameters.completeTask_302FleetInfo;
	staticParameters.completeTaskInfo_2300533.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_302;

	staticParameters.completeTaskInfo_2200232.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2200232.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2200732.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2200732.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2201532.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2201532.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2200932.fleetInfo = staticParameters.completeTask_601FleetInfo;
	staticParameters.completeTaskInfo_2200932.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_601;

	staticParameters.completeTaskInfo_2201732.fleetInfo = staticParameters.completeTask_601FleetInfo;
	staticParameters.completeTaskInfo_2201732.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_601;

	staticParameters.completeTaskInfo_2200632.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2200632.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2201432.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2201432.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2201832.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2201832.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2201132.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2201132.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2200832.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2200832.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.completeTaskInfo_2201632.fleetInfo = staticParameters.completeTask_201FleetInfo;
	staticParameters.completeTaskInfo_2201632.pveWarInfo = staticParameters.behaviourNode_PveWar_CompleteTask_201;

	staticParameters.pvpFleetConfig.clear();
	staticParameters.pvpFleetConfig.append(27149);
	staticParameters.pvpFleetConfig.append(1158);
	staticParameters.pvpFleetConfig.append(1462);
	staticParameters.pvpFleetConfig.append(39967);
	staticParameters.pvpFleetConfig.append(30123);
	staticParameters.pvpFleetConfig.append(95602);

	staticParameters.defaultCampaignId = 402;

	staticParameters.spoilEventStartTime = QDateTime::fromString("2017.3.25 00:00:00", "yyyy.M.d hh:mm:ss");

	staticParameters.maxSpoilNumList.clear();
	staticParameters.maxSpoilNumList.append(1174);//25
	staticParameters.maxSpoilNumList.append(1224);//26
	staticParameters.maxSpoilNumList.append(1274);//27
	staticParameters.maxSpoilNumList.append(1324);//28
	staticParameters.maxSpoilNumList.append(1374);//29
	staticParameters.maxSpoilNumList.append(1424);//30
	staticParameters.maxSpoilNumList.append(1474);//31

	/*
	staticParameters.mutexBehaviourList.clear();
	staticParameters.mutexBehaviourList.append(BehaviourType::StealAluminiumBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::StealOilBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::StealAmmoBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::CollectDogFoodBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::UpdatePvpStatusBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::UpdateCampaignStatusBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::CompleteTaskBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::StealPantsBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::CollectShipBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::PveExploreBehaviour);
	staticParameters.mutexBehaviourList.append(BehaviourType::RepairShipBehaviour);
	*/

	staticParameters.collectShipShipCidList.clear();
	staticParameters.collectShipShipCidList.append(10016911);
	staticParameters.collectShipShipCidList.append(10001413);
	staticParameters.collectShipShipCidList.append(10010213);
	staticParameters.collectShipShipCidList.append(10010113);
	staticParameters.collectShipShipCidList.append(10026711);
	staticParameters.collectShipShipCidList.append(10022113);
	staticParameters.collectShipShipCidList.append(10022213);
	staticParameters.collectShipShipCidList.append(10001513);
	staticParameters.collectShipShipCidList.append(10029211);

	staticParameters.commenShipIdList.clear();
	staticParameters.commenShipIdList.append(2201);
	staticParameters.commenShipIdList.append(3421);
	staticParameters.commenShipIdList.append(1502);
	staticParameters.commenShipIdList.append(1361);
	staticParameters.commenShipIdList.append(240);
	staticParameters.commenShipIdList.append(2035);
	staticParameters.commenShipIdList.append(415);
	//staticParameters.commenShipIdList.append(32424);
	//staticParameters.commenShipIdList.append(134);
	staticParameters.commenShipIdList.append(30092);

	staticParameters.resultLevelDescriptorList.clear();
	staticParameters.resultLevelDescriptorList.append("SS");
	staticParameters.resultLevelDescriptorList.append("S");
	staticParameters.resultLevelDescriptorList.append("A");
	staticParameters.resultLevelDescriptorList.append("B");
	staticParameters.resultLevelDescriptorList.append("C");
	staticParameters.resultLevelDescriptorList.append("D");

	return true;
}

bool BehaviourManager::initDynamicParameters() {
	dynamicParameters.currentPveWarInfo = PveWarInformation();
	dynamicParameters.currentPvpWarInfo = PvpWarInformation();
	dynamicParameters.currentCampaignInfo = CampaignInformation();

	currentBehaviourDepth++;

	if (dynamicParameters.dataUpdateFlag.unlockedShipsFlag == false) {
		dynamicParameters.stealOilAndAmmoDogFoodShipIdList.clear();
		dynamicParameters.stealAluminiumDogFoodShipIdList.clear();
		dynamicParameters.dogFoodShipIdList.clear();
		dynamicParameters.dismantleShipIdList.clear();
		for each(int shipIdTemp in jrData.userInfo.userShipVo.keys()) {
			if (jrData.userInfo.userShipVo[shipIdTemp].isLocked == 0 && (jrData.userInfo.userShipVo[shipIdTemp].fleetId == staticParameters.activeFleetId || jrData.userInfo.userShipVo[shipIdTemp].fleetId == 0)) {
				dispatchShip(shipIdTemp);
			}
		}
		dynamicParameters.dataUpdateFlag.unlockedShipsFlag = true;
	}
	if (dynamicParameters.dataUpdateFlag.pvpUserInfoListFlag == false) {
		(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::CheckPvpStatusBehaviour, QVariant()));
	}
	if (dynamicParameters.dataUpdateFlag.currentCampaignInfoFlag == false) {
		dynamicParameters.currentCampaignInfo.campaignInfo.campaignId = staticParameters.defaultCampaignId;
		(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::GetCampaignFleetBehaviour, QVariant()));
	}
	if (dynamicParameters.dataUpdateFlag.spoilNumFlag == false) {
		(*getParentBehaviour()).childBehaviour.append(BehaviourNode(BehaviourType::CheckSpoilsShopBehaviour, QVariant()));
	}

	executeNextExecutableBehaviour();
	return true;
}

bool BehaviourManager::startCollectProcess() {
	networkCookie = new ud_NetworkCookie(this);
	networkManager = new QNetworkAccessManager(this);
	networkManager->setCookieJar(networkCookie);

	for (int count = 0; count < 4; count++) {
		connect(&(repairDockTimer[count]), SIGNAL(timeout()), this, SLOT(repairDockTimerTimeout()));
	}
	for (int count = 0; count < 4; count++) {
		connect(&(pveExploreTimer[count]), SIGNAL(timeout()), this, SLOT(pveExploreTimerTimeout()));
	}

	connect(&networkDelayTimer, SIGNAL(timeout()), this, SLOT(abortRequest()));
	connect(&resendRequestTimer, SIGNAL(timeout()), this, SLOT(resendRequest()));
	connect(&updatePvpStatusTimer, SIGNAL(timeout()), this, SLOT(updatePvpStatusTimerTimeout()));
	connect(&updateDrop500Timer, SIGNAL(timeout()), this, SLOT(updateDrop500TimerTimeout()));
	connect(&serverMaintenanceTimer, SIGNAL(timeout()), this, SLOT(serverMaintenanceTimerTimeout()));

	connect(this, SIGNAL(behaviourComplete()), this, SLOT(handleBehaviourResult()));

	uint currentTime = QDateTime::currentDateTime().toTime_t() - 600;
	QString currentDate = QDateTime::fromTime_t(currentTime).toString("yyyy.M.d");
	int currentHour = QDateTime::fromTime_t(currentTime).toString("h").toInt();

	uint nextUpdateTime;

	if (currentHour < 12) {
		nextUpdateTime = QDateTime::fromString(currentDate + " 12:00:00", "yyyy.M.d hh:mm:ss").toTime_t();
		if (nextUpdateTime <= currentTime) {
			nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
		}
		updatePvpStatusTimer.setSingleShot(true);
		updatePvpStatusTimer.start((nextUpdateTime - currentTime) * 1000);

		QTime timeTemp(0, 0, 0, 0);
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
		emit(outputLog(6, "wait : " + timeTemp.toString("hh:mm:ss")));
	}
	else if (currentHour < 18) {
		nextUpdateTime = QDateTime::fromString(currentDate + " 18:00:00", "yyyy.M.d hh:mm:ss").toTime_t();
		if (nextUpdateTime <= currentTime) {
			nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
		}
		updatePvpStatusTimer.setSingleShot(true);
		updatePvpStatusTimer.start((nextUpdateTime - currentTime) * 1000);

		QTime timeTemp(0, 0, 0, 0);
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
		emit(outputLog(6, "wait : " + timeTemp.toString("hh:mm:ss")));
	}
	else {
		nextUpdateTime = QDateTime::fromString(currentDate + " 00:00:00", "yyyy.M.d hh:mm:ss").toTime_t() + 24 * 60 * 60;
		if (nextUpdateTime <= currentTime) {
			nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
		}
		updatePvpStatusTimer.setSingleShot(true);
		updatePvpStatusTimer.start((nextUpdateTime - currentTime) * 1000);

		QTime timeTemp(0, 0, 0, 0);
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
		emit(outputLog(6, "wait : " + timeTemp.toString("hh:mm:ss")));
	}

	nextUpdateTime = QDateTime::fromString(currentDate + " 00:00:00", "yyyy.M.d hh:mm:ss").toTime_t() + 24 * 60 * 60;
	if (nextUpdateTime <= currentTime) {
		nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
	}
	updateDrop500Timer.setSingleShot(true);
	updateDrop500Timer.start((nextUpdateTime - currentTime) * 1000);

	if (serverMaintenanceTimer.isActive()) {
		serverMaintenanceTimer.stop();
	}

	QTime timeTemp(0, 0, 0, 0);
	if (nextUpdateTime - currentTime >= 24 * 60 * 60) {
		timeTemp = timeTemp.addSecs(24 * 60 * 60 - 1);
	}
	else {
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
	}
	emit(outputLog(7, "wait : " + timeTemp.toString("hh:mm:ss")));

	initStaticParameters();

	QFile initInfoFile;
	initInfoFile.setFileName(staticParameters.initInfoFilePath);
	if (false == initInfoFile.open(QIODevice::ReadOnly)) {
		errorHandler("initialization file open error");
		return false;
	}

	QByteArray initContent = initInfoFile.readAll();

	QJsonParseError errorTemp;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(initContent, &errorTemp);
	if (errorTemp.error != QJsonParseError::NoError || !jsonDocument.isObject()) {
		errorHandler("initialization file parse error");
		return false;
	}

	ErrorManager errorManager;
	if (false == jrData.initInfo.fromQJsonObject(jsonDocument.object(), errorManager)) {
		errorHandler("initialization file parse error : " + errorManager.errorInfo);
		return false;
	}

	dynamicParameters.resetAll();
	initBehaviourparameters();

	executeNextExecutableBehaviour();
	return true;
}

bool BehaviourManager::initBehaviourparameters() {
	rootBehaviour.clear();

	BehaviourNode behaviourNodeTemp;
	behaviourNodeTemp.behaviourType = BehaviourType::RootBehavior;
	rootBehaviour.push_back(behaviourNodeTemp);

	currentBehaviourDepth = 1;

	rootBehaviour[0].childBehaviour.push_back(staticParameters.behaviourNode_Login);

	behaviourNodeTemp.behaviourType = BehaviourType::InitDynamicParametersBehaviour;
	rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);

	behaviourNodeTemp.behaviourType = BehaviourType::RepairShipBehaviour;
	rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);

	behaviourNodeTemp.behaviourType = BehaviourType::PveExploreBehaviour;
	rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);

	behaviourNodeTemp.behaviourType = BehaviourType::InitBattleParametersBehaviour;
	rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);

	return true;
}

bool BehaviourManager::generateNextBattleParameters() {
	BehaviourNode behaviourNodeTemp;
	bool flagTemp;
	/*
	for (int count = 1; count < rootBehaviour[0].childBehaviour.size(); count++) {
		if (staticParameters.mutexBehaviourList.contains(rootBehaviour[0].childBehaviour[count].behaviourType)) {
			return true;
		}
	}
	*/
	dynamicParameters.canCompleteTask = false;
	if (dynamicParameters.canPvp == true) {
		behaviourNodeTemp.behaviourType = BehaviourType::UpdatePvpStatusBehaviour;
		rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
		return true;
	}
	else if (dynamicParameters.canCampaign == true) {
		behaviourNodeTemp.behaviourType = BehaviourType::UpdateCampaignStatusBehaviour;
		rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
		return true;
	}
	else if (dynamicParameters.canCompleteTask == true) {
		behaviourNodeTemp.behaviourType = BehaviourType::CompleteTaskBehaviour;
		rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
		return true;
	}
	else {
		if (staticParameters.defaultCollectStrategy == CollectStrategy::StealResourceStrategy) {
			behaviourNodeTemp.behaviourType = BehaviourType::StealAluminiumBehaviour;
			rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
			return true;
		}
		else if (staticParameters.defaultCollectStrategy == CollectStrategy::StealPantsStrategy) {
			if (dynamicParameters.spoilNum < dynamicParameters.maxSpoilNum) {
				if (jrData.userInfo.userShipVo.size() + 10 <= jrData.userInfo.shipNumTop) {
					behaviourNodeTemp.behaviourType = BehaviourType::StealPantsBehaviour;
					rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
					return true;
				}
				else {
					behaviourNodeTemp.behaviourType = BehaviourType::StealAluminiumBehaviour;
					rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
					return true;
				}
			}
			else {
				staticParameters.defaultCollectStrategy = CollectStrategy::StealResourceStrategy;
				behaviourNodeTemp.behaviourType = BehaviourType::StealAluminiumBehaviour;
				rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
				return true;
			}
		}
		else if (staticParameters.defaultCollectStrategy == CollectStrategy::CollectShipStrategy) {
			if (dynamicParameters.collectShipSuccessFlag == false) {
				behaviourNodeTemp.behaviourType = BehaviourType::CollectShipBehaviour;
				rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
			}
			else {
				behaviourNodeTemp.behaviourType = BehaviourType::ActiveFleetPveExploreBehaviour;
				rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
			}
			return true;
		}
	}

	return true;
}

bool BehaviourManager::initBattleParameters() {
	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status == 0) {
		generateNextBattleParameters();
	}

	emit(behaviourComplete());
	return true;
}

bool BehaviourManager::handleBehaviourResult() {
	bool flagTemp;

	if ((*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.size() == 0) {
		/*
		if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealAluminiumBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealOilBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealAmmoBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CollectDogFoodBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::UpdatePvpStatusBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::UpdateCampaignStatusBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CompleteTaskBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealPantsBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CollectShipBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::PveExploreBehaviour) {
			generateNextBattleParameters();
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::RepairShipBehaviour) {
			generateNextBattleParameters();
		}
		else*/ if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CheckPvpStatusBehaviour) {
			dynamicParameters.dataUpdateFlag.pvpUserInfoListFlag = true;
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::GetCampaignFleetBehaviour) {
			dynamicParameters.dataUpdateFlag.currentCampaignInfoFlag = true;
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CheckSpoilsShopBehaviour) {
			int dateIndexTemp = (QDateTime::currentDateTime().toTime_t() - staticParameters.spoilEventStartTime.toTime_t()) / (24 * 60 * 60);
			if (dateIndexTemp < 0 || dateIndexTemp >= staticParameters.maxSpoilNumList.size()) {
				dynamicParameters.maxSpoilNum = dynamicParameters.spoilNum;
			}
			else {
				dynamicParameters.maxSpoilNum = staticParameters.maxSpoilNumList[dateIndexTemp];
			}
			emit(outputLog(12, QString::number(dynamicParameters.spoilNum) + " / " + QString::number(dynamicParameters.maxSpoilNum)));
			dynamicParameters.dataUpdateFlag.spoilNumFlag = true;
		}
		else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::LoginBehaviour) {
			dynamicParameters.loginFinished = true;
		}

		(*getParentBehaviour()).childBehaviour.pop_front();
		executeNextExecutableBehaviour();

		return true;
	}

	if ((*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.contains(ErrorCode::SaveAndLoad)) {
		saveAndLoad();

		return true;
	}

	if ((*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.contains(ErrorCode::OperationError)) {
		int errorCodeTemp = (*getParentBehaviour()).childBehaviour[0].behaviourReturnValues[ErrorCode::OperationError].toInt();
		if (errorCodeTemp != -9999) {
			if (errorCodeTemp == -9995) {
				QEventLoop eventloop;
				QTimer timerTemp;
				connect(&timerTemp, SIGNAL(timeout()), &eventloop, SLOT(quit()));
				timerTemp.setSingleShot(true);
				timerTemp.start(60000 + (qrand() % 5000));
				eventloop.exec();

				dynamicParameters.dataUpdateFlag.currentCampaignInfoFlag = false;
				dynamicParameters.dataUpdateFlag.pvpUserInfoListFlag = false;
				dynamicParameters.dataUpdateFlag.spoilNumFlag = false;

				for (int count = 0; count < 3; count++) {
					if (repairDockTimer[count].isActive()) {
						repairDockTimer[count].stop();
					}
				}
				for (int count = 0; count < 4; count++) {
					if (pveExploreTimer[count].isActive()) {
						pveExploreTimer[count].stop();
					}
				}
			}

			dynamicParameters.dataUpdateFlag.unlockedShipsFlag = false;
			initBehaviourparameters();

			executeNextExecutableBehaviour();
			return true;
		}
		else {
			rootBehaviour.clear();

			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::RootBehavior;
			rootBehaviour.push_back(behaviourNodeTemp);

			currentBehaviourDepth = 1;

			if (!serverMaintenanceTimer.isActive()) {
				serverMaintenanceTimer.setSingleShot(true);
				serverMaintenanceTimer.start(30 * 60 * 1000);
				emit(outputLog(0, "wait : 30:00:00"));
			}

			return true;
		}
	}

	if ((*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.contains(ErrorCode::DataParseError)) {
		dynamicParameters.dataUpdateFlag.unlockedShipsFlag = false;
		dynamicParameters.dataUpdateFlag.pvpUserInfoListFlag = false;
		dynamicParameters.dataUpdateFlag.currentCampaignInfoFlag = false;
		dynamicParameters.dataUpdateFlag.spoilNumFlag = false;
		initBehaviourparameters();
		executeNextExecutableBehaviour();
		return true;
	}

	if ((*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.contains(ErrorCode::RouteError)) {
		for (int count = 0; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count++) {
			if (jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].isLocked == 0) {
				dispatchShip(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]);
			}
		}
		initBehaviourparameters();
		executeNextExecutableBehaviour();
		return true;
	}

	for each(ErrorCode errorCodeTemp in (*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.keys()) {
		if (errorCodeTemp == ErrorCode::GetTaskAward) {
			QVector<int> taskCidListTemp = (*getParentBehaviour()).childBehaviour[0].behaviourReturnValues[ErrorCode::GetTaskAward].value<QVector<int>>();
			GetTaskAwardBehaviourParameter getTaskAwardBehaviourParameterTemp;
			for (int count = 0; count < taskCidListTemp.size(); count++) {
				getTaskAwardBehaviourParameterTemp.taskId = taskCidListTemp[count];
				rootBehaviour[0].childBehaviour.push_back(BehaviourNode(BehaviourType::GetTaskAwardBehaviour, QVariant::fromValue(getTaskAwardBehaviourParameterTemp)));
			}
		}
		else if (errorCodeTemp == ErrorCode::GetLoginAward) {
			rootBehaviour[0].childBehaviour.push_back(BehaviourNode(BehaviourType::GetLoginAwardBehaviour, QVariant()));
		}
		else if (errorCodeTemp == ErrorCode::NonactiveFleetIdle) {
			rootBehaviour[0].childBehaviour.push_back(BehaviourNode(BehaviourType::PveExploreBehaviour, QVariant()));
		}
		else if (errorCodeTemp == ErrorCode::RepairDockIdle) {
			rootBehaviour[0].childBehaviour.push_back(BehaviourNode(BehaviourType::RepairShipBehaviour, QVariant()));
		}
		else if (errorCodeTemp == ErrorCode::CampaignFinished) {
			rootBehaviour[0].childBehaviour.push_back(BehaviourNode(BehaviourType::RepairShipBehaviour, QVariant()));
			generateNextBattleParameters();
		}
		else if (errorCodeTemp == ErrorCode::ActiveFleetIdle) {
			if (dynamicParameters.drop500 != 0) {
				for (int count = 0; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count++) {
					if (jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].isLocked != 0 && 1 != getBrokenStatus(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count])) {
						rootBehaviour[0].childBehaviour.push_back(BehaviourNode(BehaviourType::RepairShipBehaviour, QVariant()));
						break;
					}
				}
			}
			else {
				for (int count = 0; count < jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size(); count++) {
					if (jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].isLocked != 0 && (4 == getBrokenStatus(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]) || ((jrData.initInfo.shipCard[jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].shipCid].type == 1 || jrData.initInfo.shipCard[jrData.userInfo.userShipVo[jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]].shipCid].type == 2) && 3 <= getBrokenStatus(jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count])))) {
						rootBehaviour[0].childBehaviour.push_back(BehaviourNode(BehaviourType::RepairShipBehaviour, QVariant()));
						break;
					}
				}
			}
			generateNextBattleParameters();
		}
		else if (errorCodeTemp == ErrorCode::InsufficientResourceError) {
			BehaviourNode behaviourNodeTemp;
			if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealAluminiumBehaviour) {
				if (dynamicParameters.stealAmmoBrokenCount >= dynamicParameters.stealOilBrokenCount) {
					behaviourNodeTemp.behaviourType = BehaviourType::StealOilBehaviour;
					(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
				}
				else {
					behaviourNodeTemp.behaviourType = BehaviourType::StealAmmoBehaviour;
					(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
				}
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealOilBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::TrainShipBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealAmmoBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::TrainShipBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::TrainShipBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::CollectDogFoodBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CollectDogFoodBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::ActiveFleetPveExploreBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CollectShipBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::ActiveFleetPveExploreBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::StealPantsBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::ActiveFleetPveExploreBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::ChangeEquipmentBehaviour) {
				(*getParentBehaviour()).childBehaviour.clear();
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::SupplyMultiBoatBehaviour) {
				(*getParentBehaviour()).childBehaviour.clear();
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::SupplyBoatBehaviour) {
				(*getParentBehaviour()).childBehaviour.clear();
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::InstantRepairMultiShipBehaviour) {
				(*getParentBehaviour()).childBehaviour.clear();
				currentBehaviourDepth--;
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::InsufficientResourceError, QVariant());
				emit(behaviourComplete());
				return true;
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::CompleteTaskBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::ActiveFleetPveExploreBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
			else if ((*getParentBehaviour()).childBehaviour[0].behaviourType == BehaviourType::UpdatePvpStatusBehaviour) {
				behaviourNodeTemp.behaviourType = BehaviourType::ActiveFleetPveExploreBehaviour;
				(*getParentBehaviour()).childBehaviour.push_back(behaviourNodeTemp);
			}
		}
	}

	(*getParentBehaviour()).childBehaviour.pop_front();

	executeNextExecutableBehaviour();
	return true;
}

bool BehaviourManager::updateResource() {
	/*
	uint currentTimeTemp = QDateTime::currentDateTime().toTime_t();

	if (currentTimeTemp <= jrData.userInfo.userResourceVo.lastUpdateTime) {
		emit(behaviourComplete());
		return true;
	}

	int maxResourceNum = jrData.userInfo.level * 500 + 500;

	if (jrData.userInfo.userResourceVo.oil < maxResourceNum) {
		jrData.userInfo.userResourceVo.oil = jrData.userInfo.userResourceVo.oil + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 60.0 < maxResourceNum ? jrData.userInfo.userResourceVo.oil + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 60.0 : maxResourceNum;
	}
	if (jrData.userInfo.userResourceVo.ammo < maxResourceNum) {
		jrData.userInfo.userResourceVo.ammo = jrData.userInfo.userResourceVo.ammo + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 60.0 < maxResourceNum ? jrData.userInfo.userResourceVo.ammo + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 60.0 : maxResourceNum;
	}
	if (jrData.userInfo.userResourceVo.steel < maxResourceNum) {
		jrData.userInfo.userResourceVo.steel = jrData.userInfo.userResourceVo.steel + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 60.0 < maxResourceNum ? jrData.userInfo.userResourceVo.steel + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 60.0 : maxResourceNum;
	}
	if (jrData.userInfo.userResourceVo.aluminium < maxResourceNum) {
		jrData.userInfo.userResourceVo.aluminium = jrData.userInfo.userResourceVo.aluminium + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 180.0 < maxResourceNum ? jrData.userInfo.userResourceVo.aluminium + (currentTimeTemp - jrData.userInfo.userResourceVo.lastUpdateTime) / 180.0 : maxResourceNum;
	}

	jrData.userInfo.userResourceVo.lastUpdateTime = currentTimeTemp;
	return true;
	*/
	return true;
}

bool BehaviourManager::repairShip() {
	bool flagTemp = true;
	bool flagTemp1 = false;
	QVector<int> repairShipIdListTemp;
	
	currentBehaviourDepth++;

	uint currentTime = QDateTime::currentDateTime().toTime_t();
	for each(int repairDockIdTemp in jrData.userInfo.repairDockVo.keys()) {
		if (jrData.userInfo.repairDockVo[repairDockIdTemp].locked == 0) {
			if (jrData.userInfo.repairDockVo[repairDockIdTemp].shipId != 0) {
				if (jrData.userInfo.repairDockVo[repairDockIdTemp].endTime < currentTime) {
					if (repairDockTimer[repairDockIdTemp - 1].isActive()) {
						repairDockTimer[repairDockIdTemp - 1].stop();
					}

					BehaviourNode behaviourNodeTemp;
					behaviourNodeTemp.behaviourType = BehaviourType::RepairShipCompleteBehaviour;
					RepairShipCompleteBehaviourParameter repairShipCompleteBehaviourParameterTemp;
					repairShipCompleteBehaviourParameterTemp.repairDockId = repairDockIdTemp;
					repairShipCompleteBehaviourParameterTemp.shipId = jrData.userInfo.repairDockVo[repairDockIdTemp].shipId;
					behaviourNodeTemp.behaviourParameters = QVariant::fromValue(repairShipCompleteBehaviourParameterTemp);

					(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
				}
				else {
					if (flagTemp == true && staticParameters.collectDogFood_505FleetInfo.contains(jrData.userInfo.repairDockVo[repairDockIdTemp].shipId)) {
						flagTemp = false;
					}
					if (!repairDockTimer[repairDockIdTemp - 1].isActive()) {
						repairDockTimer[repairDockIdTemp - 1].setSingleShot(true);
						repairDockTimer[repairDockIdTemp - 1].start((jrData.userInfo.repairDockVo[repairDockIdTemp].endTime - currentTime + 5) * 1000);
					
						if (repairDockIdTemp < 3) {
							QTime timeTemp(0, 0, 0, 0);
							int waitTime = jrData.userInfo.repairDockVo[repairDockIdTemp].endTime - currentTime;
							timeTemp = timeTemp.addSecs(waitTime > 0 ? waitTime : 0);
							emit(outputLog(repairDockIdTemp + 3, "wait : " + timeTemp.toString("hh:mm:ss")));
						}
					}
				}
			}
			else {
				flagTemp1 = false;

				if (flagTemp == true) {
					for (int count = 0; count < staticParameters.collectDogFood_505FleetInfo.size(); count++) {
						if (!repairShipIdListTemp.contains(staticParameters.collectDogFood_505FleetInfo[count]) && ((dynamicParameters.drop500 != 0 && 1 != getBrokenStatus(staticParameters.collectDogFood_505FleetInfo[count])) || 3 <= getBrokenStatus(staticParameters.collectDogFood_505FleetInfo[count])) && jrData.userInfo.userShipVo[staticParameters.collectDogFood_505FleetInfo[count]].status == 0) {
							BehaviourNode behaviourNodeTemp;
							behaviourNodeTemp.behaviourType = BehaviourType::RepairShipStartBehaviour;
							RepairShipStartBehaviourParameter repairShipStartBehaviourParameterTemp;
							repairShipStartBehaviourParameterTemp.repairDockId = repairDockIdTemp;
							repairShipStartBehaviourParameterTemp.shipId = staticParameters.collectDogFood_505FleetInfo[count];
							behaviourNodeTemp.behaviourParameters = QVariant::fromValue(repairShipStartBehaviourParameterTemp);

							repairShipIdListTemp.append(repairShipStartBehaviourParameterTemp.shipId);
							flagTemp1 = true;
							(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
							break;
						}
					}
				}

				if (flagTemp1 == true) {
					continue;
				}

				for (int count = 0; count < staticParameters.stealAluminiumShipList.size(); count++) {
					if (!repairShipIdListTemp.contains(staticParameters.stealAluminiumShipList[count].shipId) && ((dynamicParameters.drop500 != 0 && 1 != getBrokenStatus(staticParameters.stealAluminiumShipList[count].shipId)) || 4 == getBrokenStatus(staticParameters.stealAluminiumShipList[count].shipId)) && jrData.userInfo.userShipVo[staticParameters.stealAluminiumShipList[count].shipId].status == 0) {
						BehaviourNode behaviourNodeTemp;
						behaviourNodeTemp.behaviourType = BehaviourType::RepairShipStartBehaviour;
						RepairShipStartBehaviourParameter repairShipStartBehaviourParameterTemp;
						repairShipStartBehaviourParameterTemp.repairDockId = repairDockIdTemp;
						repairShipStartBehaviourParameterTemp.shipId = staticParameters.stealAluminiumShipList[count].shipId;
						behaviourNodeTemp.behaviourParameters = QVariant::fromValue(repairShipStartBehaviourParameterTemp);

						repairShipIdListTemp.append(repairShipStartBehaviourParameterTemp.shipId);
						flagTemp1 = true;
						(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
						break;
					}
				}

				if (flagTemp1 == true) {
					continue;
				}

				for (int count = 0; count < staticParameters.trainingShipList.size(); count++) {
					if (!repairShipIdListTemp.contains(staticParameters.trainingShipList[count].shipId) && ((dynamicParameters.drop500 != 0 && 1 != getBrokenStatus(staticParameters.trainingShipList[count].shipId)) || 4 == getBrokenStatus(staticParameters.trainingShipList[count].shipId) || (3 <= getBrokenStatus(staticParameters.trainingShipList[count].shipId) && jrData.initInfo.shipCard[jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].shipCid].type == 2)) && jrData.userInfo.userShipVo[staticParameters.trainingShipList[count].shipId].status == 0) {
						BehaviourNode behaviourNodeTemp;
						behaviourNodeTemp.behaviourType = BehaviourType::RepairShipStartBehaviour;
						RepairShipStartBehaviourParameter repairShipStartBehaviourParameterTemp;
						repairShipStartBehaviourParameterTemp.repairDockId = repairDockIdTemp;
						repairShipStartBehaviourParameterTemp.shipId = staticParameters.trainingShipList[count].shipId;
						behaviourNodeTemp.behaviourParameters = QVariant::fromValue(repairShipStartBehaviourParameterTemp);

						repairShipIdListTemp.append(repairShipStartBehaviourParameterTemp.shipId);
						flagTemp1 = true;
						(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
						break;
					}
				}

				if (flagTemp1 == true) {
					continue;
				}

				if (dynamicParameters.spoilNum >= dynamicParameters.maxSpoilNum && dynamicParameters.dataUpdateFlag.currentCampaignInfoFlag == true && jrData.userInfo.passInfo.remainNum == 0 && dynamicParameters.canCompleteTask == false) {
					for (int count = 0; count < staticParameters.commenShipIdList.size(); count++) {
						if (!repairShipIdListTemp.contains(staticParameters.commenShipIdList[count]) && 1 != getBrokenStatus(staticParameters.commenShipIdList[count]) && jrData.userInfo.userShipVo[staticParameters.commenShipIdList[count]].status == 0) {
							BehaviourNode behaviourNodeTemp;
							behaviourNodeTemp.behaviourType = BehaviourType::RepairShipStartBehaviour;
							RepairShipStartBehaviourParameter repairShipStartBehaviourParameterTemp;
							repairShipStartBehaviourParameterTemp.repairDockId = repairDockIdTemp;
							repairShipStartBehaviourParameterTemp.shipId = staticParameters.commenShipIdList[count];
							behaviourNodeTemp.behaviourParameters = QVariant::fromValue(repairShipStartBehaviourParameterTemp);

							repairShipIdListTemp.append(repairShipStartBehaviourParameterTemp.shipId);
							flagTemp1 = true;
							(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
							break;
						}
					}
				}

				if (flagTemp1 == true) {
					continue;
				}

				for (int count = 0; count < staticParameters.repairShipIdList.size(); count++) {
					if (!repairShipIdListTemp.contains(staticParameters.repairShipIdList[count]) && 1 != getBrokenStatus(staticParameters.repairShipIdList[count]) && jrData.userInfo.userShipVo[staticParameters.repairShipIdList[count]].status == 0) {
						BehaviourNode behaviourNodeTemp;
						behaviourNodeTemp.behaviourType = BehaviourType::RepairShipStartBehaviour;
						RepairShipStartBehaviourParameter repairShipStartBehaviourParameterTemp;
						repairShipStartBehaviourParameterTemp.repairDockId = repairDockIdTemp;
						repairShipStartBehaviourParameterTemp.shipId = staticParameters.repairShipIdList[count];
						behaviourNodeTemp.behaviourParameters = QVariant::fromValue(repairShipStartBehaviourParameterTemp);

						repairShipIdListTemp.append(repairShipStartBehaviourParameterTemp.shipId);
						flagTemp1 = true;
						(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
						break;
					}
				}
			}
		}
	}

	executeNextExecutableBehaviour();
	return true;
}

bool BehaviourManager::pveExplore() {
	bool flagTemp;
	currentBehaviourDepth++;

	uint currentTime = QDateTime::currentDateTime().toTime_t();
	for each(int pveExploreIdTemp in jrData.userInfo.pveExploreVo.levels.keys()) {
		if (jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].endTime < currentTime) {
			if (pveExploreTimer[jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].fleetId - 1].isActive()) {
				pveExploreTimer[jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].fleetId - 1].stop();
			}

			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::PveExploreCompleteBehaviour;
			PveExploreCompleteBehaviourParameter pveExploreCompleteBehaviourParameterTemp;
			pveExploreCompleteBehaviourParameterTemp.pveExploreId = pveExploreIdTemp;
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(pveExploreCompleteBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
		else {
			if (!pveExploreTimer[jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].fleetId - 1].isActive()) {
				pveExploreTimer[jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].fleetId - 1].setSingleShot(true);
				pveExploreTimer[jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].fleetId - 1].start((jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].endTime - currentTime + 5) * 1000);
				
				QTime timeTemp(0, 0, 0, 0);
				int waitTime = jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].endTime - currentTime;
				timeTemp = timeTemp.addSecs(waitTime > 0 ? waitTime : 0);
				if (jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].fleetId == staticParameters.activeFleetId) {
					emit(outputLog(0, "wait : " + timeTemp.toString("hh:mm:ss")));
				}
				else {
					emit(outputLog(jrData.userInfo.pveExploreVo.levels[pveExploreIdTemp].fleetId, "wait : " + timeTemp.toString("hh:mm:ss")));
				}
			}
		}
	}

	for (int count = 1; count < 5; count++) {
		if (count != staticParameters.activeFleetId && jrData.userInfo.fleetVo[count].status == 0) {
			BehaviourNode behaviourNodeTemp;
			behaviourNodeTemp.behaviourType = BehaviourType::PveExploreStartBehaviour;
			PveExploreStartBehaviourParameter pveExploreStartBehaviourParameterTemp;
			pveExploreStartBehaviourParameterTemp.fleetId = count;
			pveExploreStartBehaviourParameterTemp.pveExploreId = staticParameters.pveExploreConfig[count];
			behaviourNodeTemp.behaviourParameters = QVariant::fromValue(pveExploreStartBehaviourParameterTemp);

			(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);
		}
	}

	executeNextExecutableBehaviour();
	return true;
}

bool BehaviourManager::activeFleetPveExplore() {
	bool flagTemp;

	if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].status != 0) {
		emit(behaviourComplete());
		return true;
	}
	else {
		currentBehaviourDepth++;

		bool flagTemp = false;
		if (jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships.size() != staticParameters.activeFleetPveExploreFleetConfig.size()) {
			flagTemp = true;
		}
		else {
			for (int count = 0; count < staticParameters.activeFleetPveExploreFleetConfig.size(); count++) {
				if (staticParameters.activeFleetPveExploreFleetConfig[count] != jrData.userInfo.fleetVo[staticParameters.activeFleetId].ships[count]) {
					flagTemp = true;
					break;
				}
			}
		}
		if (flagTemp == true) {
			CreateFleetBehaviourParameter createFleetBehaviourParameterTemp;
			createFleetBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
			createFleetBehaviourParameterTemp.shipIdList = staticParameters.activeFleetPveExploreFleetConfig;

			(*getParentBehaviour()).childBehaviour.push_back(BehaviourNode(BehaviourType::CreateFleetBehaviour, QVariant::fromValue(createFleetBehaviourParameterTemp)));
		}

		BehaviourNode behaviourNodeTemp;
		behaviourNodeTemp.behaviourType = BehaviourType::PveExploreStartBehaviour;
		PveExploreStartBehaviourParameter pveExploreStartBehaviourParameterTemp;
		pveExploreStartBehaviourParameterTemp.fleetId = staticParameters.activeFleetId;
		pveExploreStartBehaviourParameterTemp.pveExploreId = staticParameters.pveExploreConfig[staticParameters.activeFleetId];
		behaviourNodeTemp.behaviourParameters = QVariant::fromValue(pveExploreStartBehaviourParameterTemp);

		(*getParentBehaviour()).childBehaviour.append(behaviourNodeTemp);

		executeNextExecutableBehaviour();
	}

	return true;
}

bool BehaviourManager::repairDockTimerTimeout() {
	bool flagTemp = false;
	BehaviourNode behaviourNodeTemp;
	behaviourNodeTemp.behaviourType = BehaviourType::RepairShipBehaviour;
	if (rootBehaviour.size() == 0) {
		return true;
	}

	if (rootBehaviour[0].childBehaviour.size() == 0) {
		flagTemp = true;
	}
	rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
	if (flagTemp == true) {
		executeNextExecutableBehaviour();
	}

	return true;
}

bool BehaviourManager::pveExploreTimerTimeout() {
	bool flagTemp = false;
	BehaviourNode behaviourNodeTemp;
	behaviourNodeTemp.behaviourType = BehaviourType::PveExploreBehaviour;
	if (rootBehaviour.size() == 0) {
		return true;
	}

	if (rootBehaviour[0].childBehaviour.size() == 0) {
		flagTemp = true;
	}
	rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
	if (flagTemp == true) {
		executeNextExecutableBehaviour();
	}

	return true;
}

bool BehaviourManager::saveAndLoad() {
	dynamicParameters.dataUpdateFlag.unlockedShipsFlag = false;
	dynamicParameters.dataUpdateFlag.pvpUserInfoListFlag = false;
	dynamicParameters.dataUpdateFlag.currentCampaignInfoFlag = false;
	dynamicParameters.dataUpdateFlag.spoilNumFlag = false;
	initBehaviourparameters();

	executeNextExecutableBehaviour();
	return true;
}

bool BehaviourManager::updatePvpStatusTimerTimeout() {
	bool flagTemp = false;
	BehaviourNode behaviourNodeTemp;
	behaviourNodeTemp.behaviourType = BehaviourType::SaveAndLoadBehaviour;
	if (rootBehaviour.size() == 0) {
		return true;
	}

	if (rootBehaviour[0].childBehaviour.size() == 0) {
		rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
		executeNextExecutableBehaviour();
	}
	else {
		BehaviourNode * behaviourNodeRefTemp = &(rootBehaviour[0]);
		while (behaviourNodeRefTemp->childBehaviour.size() != 0) {
			behaviourNodeRefTemp = &(behaviourNodeRefTemp->childBehaviour[0]);
		}
		behaviourNodeRefTemp->behaviourReturnValues.insert(ErrorCode::SaveAndLoad, QVariant());
	}

	uint currentTime = QDateTime::currentDateTime().toTime_t() - 600;
	QString currentDate = QDateTime::fromTime_t(currentTime).toString("yyyy.M.d");
	int currentHour = QDateTime::fromTime_t(currentTime).toString("h").toInt();

	uint nextUpdateTime;

	if (currentHour < 12) {
		nextUpdateTime = QDateTime::fromString(currentDate + " 12:00:00", "yyyy.M.d hh:mm:ss").toTime_t();
		if (nextUpdateTime <= currentTime) {
			nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
		}
		updatePvpStatusTimer.setSingleShot(true);
		updatePvpStatusTimer.start((nextUpdateTime - currentTime) * 1000);

		QTime timeTemp(0, 0, 0, 0);
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
		emit(outputLog(6, "wait : " + timeTemp.toString("hh:mm:ss")));
	}
	else if (currentHour < 18) {
		nextUpdateTime = QDateTime::fromString(currentDate + " 18:00:00", "yyyy.M.d hh:mm:ss").toTime_t();
		if (nextUpdateTime <= currentTime) {
			nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
		}
		updatePvpStatusTimer.setSingleShot(true);
		updatePvpStatusTimer.start((nextUpdateTime - currentTime) * 1000);

		QTime timeTemp(0, 0, 0, 0);
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
		emit(outputLog(6, "wait : " + timeTemp.toString("hh:mm:ss")));
	}
	else {
		nextUpdateTime = QDateTime::fromString(currentDate + " 00:00:00", "yyyy.M.d hh:mm:ss").toTime_t() + 24 * 60 * 60;
		if (nextUpdateTime <= currentTime) {
			nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
		}
		updatePvpStatusTimer.setSingleShot(true);
		updatePvpStatusTimer.start((nextUpdateTime - currentTime) * 1000);

		QTime timeTemp(0, 0, 0, 0);
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
		emit(outputLog(6, "wait : " + timeTemp.toString("hh:mm:ss")));
	}

	return true;
}

bool BehaviourManager::updateDrop500TimerTimeout() {
	bool flagTemp = false;
	dynamicParameters.drop500 = 1;
	BehaviourNode behaviourNodeTemp;
	behaviourNodeTemp.behaviourType = BehaviourType::SaveAndLoadBehaviour;
	if (rootBehaviour.size() == 0) {
		return true;
	}

	if (rootBehaviour[0].childBehaviour.size() == 0) {
		rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
		executeNextExecutableBehaviour();
	}
	else {
		BehaviourNode * behaviourNodeRefTemp = &(rootBehaviour[0]);
		while (behaviourNodeRefTemp->childBehaviour.size() != 0) {
			behaviourNodeRefTemp = &(behaviourNodeRefTemp->childBehaviour[0]);
		}
		behaviourNodeRefTemp->behaviourReturnValues.insert(ErrorCode::SaveAndLoad, QVariant());
	}

	uint currentTime = QDateTime::currentDateTime().toTime_t() - 600;
	QString currentDate = QDateTime::fromTime_t(currentTime).toString("yyyy.M.d");
	int currentHour = QDateTime::fromTime_t(currentTime).toString("h").toInt();

	uint nextUpdateTime;

	nextUpdateTime = QDateTime::fromString(currentDate + " 00:00:00", "yyyy.M.d hh:mm:ss").toTime_t() + 24 * 60 * 60;
	if (nextUpdateTime <= currentTime) {
		nextUpdateTime += 24 * 60 * 60 * ceil(((double)currentTime - nextUpdateTime) / (24.0 * 60 * 60));;
	}
	updateDrop500Timer.setSingleShot(true);
	updateDrop500Timer.start((nextUpdateTime - currentTime) * 1000);

	QTime timeTemp(0, 0, 0, 0);
	if (nextUpdateTime - currentTime >= 24 * 60 * 60) {
		timeTemp = timeTemp.addSecs(24 * 60 * 60 - 1);
	}
	else {
		timeTemp = timeTemp.addSecs(nextUpdateTime - currentTime);
	}
	emit(outputLog(7, "wait : " + timeTemp.toString("hh:mm:ss") + "+"));

	int dateIndexTemp = (QDateTime::currentDateTime().toTime_t() - staticParameters.spoilEventStartTime.toTime_t()) / (24 * 60 * 60);
	if (dateIndexTemp < 0 || dateIndexTemp >= staticParameters.maxSpoilNumList.size()) {
		dynamicParameters.maxSpoilNum = dynamicParameters.spoilNum;
	}
	else {
		dynamicParameters.maxSpoilNum = staticParameters.maxSpoilNumList[dateIndexTemp];
		staticParameters.defaultCollectStrategy = CollectStrategy::StealPantsStrategy;
	}
	emit(outputLog(12, QString::number(dynamicParameters.spoilNum) + " / " + QString::number(dynamicParameters.maxSpoilNum)));

	return true;
}

bool BehaviourManager::serverMaintenanceTimerTimeout() {
	if (serverMaintenanceTimer.isActive()) {
		serverMaintenanceTimer.stop();
	}

	emit(outputLog(0, "test maintenance status"));

	bool flagTemp = false;
	BehaviourNode behaviourNodeTemp;
	behaviourNodeTemp.behaviourType = BehaviourType::SaveAndLoadBehaviour;
	if (rootBehaviour.size() == 0) {
		return true;
	}

	if (rootBehaviour[0].childBehaviour.size() == 0) {
		rootBehaviour[0].childBehaviour.push_back(behaviourNodeTemp);
		executeNextExecutableBehaviour();
	}
	else {
		BehaviourNode * behaviourNodeRefTemp = &(rootBehaviour[0]);
		while (behaviourNodeRefTemp->childBehaviour.size() != 0) {
			behaviourNodeRefTemp = &(behaviourNodeRefTemp->childBehaviour[0]);
		}
		behaviourNodeRefTemp->behaviourReturnValues.insert(ErrorCode::SaveAndLoad, QVariant());
	}

	return true;
}
