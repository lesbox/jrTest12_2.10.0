#include "BehaviourManager.h"

#ifdef ud_WLTNetwork
bool BehaviourManager::parseWLTData1() {
	ErrorManager errorManager;
	if (networkDelayTimer.isActive()) {
		networkDelayTimer.stop();
	}

	QByteArrayList headerList = networkReply->rawHeaderList();
	QString headerContentTemp, attrName, attrValue, errInfo;
	int indexTemp1, indexTemp2, flag;
	QByteArray requestContent1, requestContent2, decompressData;

	if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200) {
		errorHandler(QString("HTTP status : ") + QString::number(networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()) + QString("\n"));
		if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 0) {

#ifdef ud_WLTNetwork
			QNetworkConfiguration cfg;
			QNetworkConfigurationManager ncm;
			auto nc = ncm.allConfigurations();

			flag = 0;
			for (auto &x : nc)
			{
				if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
				{
					QString test = x.name();
					if (x.name() == "614wireless") {
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
		errorManager.pushErrorInfo("parseWLTData1");
		errorHandler(errorManager.getErrorInfo());
		resendRequest();
		return false;
	}

	lastResponseContent = requestContent1 = networkReply->readAll();
	networkReply->deleteLater();

	if (requestContent1 == "") {
		errorManager.pushErrorInfo(QString("no response content"));
		emit(outputLog(0, errorManager.getErrorInfo()));
		resendRequest();
		return false;
	}

	currentRequestId = RequestId::NoRequest;
	currentRequestRepeatNum = 0;

	indexTemp1 = requestContent1.indexOf("IP地址", 0);
	if (indexTemp1 == -1) {
		errorHandler("parseWLTData1 error : IP地址\n");
		return false;
	}
	indexTemp1 = requestContent1.indexOf("<td", indexTemp1);
	if (indexTemp1 == -1) {
		errorHandler("parseWLTData1 error : <td\n");
		return false;
	}
	indexTemp1 = requestContent1.indexOf(">", indexTemp1);
	if (indexTemp1 == -1) {
		errorHandler("parseWLTData1 error : >\n");
		return false;
	}
	indexTemp2 = requestContent1.indexOf("</", indexTemp1);
	if (indexTemp2 == -1) {
		errorHandler("parseWLTData1 error : </\n");
		return false;
	}
	ipAddress = requestContent1.mid(indexTemp1 + 1, indexTemp2 - indexTemp1 - 1).trimmed();

	handleWLTData1();

	return true;
}

bool BehaviourManager::parseWLTData2() {
	ErrorManager errorManager;
	if (networkDelayTimer.isActive()) {
		networkDelayTimer.stop();
	}

	QByteArrayList headerList = networkReply->rawHeaderList();
	QString headerContentTemp, attrName, attrValue, errInfo;
	int indexTemp1, indexTemp2, flag;
	QByteArray requestContent1, requestContent2, decompressData;

	if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200) {
		errorHandler(QString("HTTP status : ") + QString::number(networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()) + QString("\n"));
		if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 0) {

#ifdef ud_WLTNetwork
			QNetworkConfiguration cfg;
			QNetworkConfigurationManager ncm;
			auto nc = ncm.allConfigurations();

			flag = 0;
			for (auto &x : nc)
			{
				if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
				{
					QString test = x.name();
					if (x.name() == "614wireless") {
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
		errorManager.pushErrorInfo("parseWLTData1");
		errorHandler(errorManager.getErrorInfo());
		resendRequest();
		return false;
	}

	if (!headerList.contains("Set-Cookie")) {
		errorHandler("parseWLTData2 error : Set-Cookie\n");
		return false;
	}

	requestContent2 = networkReply->rawHeader("Set-Cookie");
	if (requestContent2.length() < 3) {
		errorHandler("parseWLTData2 error : requestContent2.length()\n");
		return false;
	}
	rn = requestContent2.mid(3, requestContent2.length() - 3);

	currentRequestId = RequestId::NoRequest;
	currentRequestRepeatNum = 0;

	handleWLTData2();

	return true;
}

bool BehaviourManager::parseWLTData3() {
	ErrorManager errorManager;
	if (networkDelayTimer.isActive()) {
		networkDelayTimer.stop();
	}

	QByteArrayList headerList = networkReply->rawHeaderList();
	QString headerContentTemp, attrName, attrValue, errInfo;
	int indexTemp1, indexTemp2, flag;
	QByteArray requestContent1, requestContent2, decompressData;

	if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200) {
		errorHandler(QString("HTTP status : ") + QString::number(networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()) + QString("\n"));
		if (networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 0) {

#ifdef ud_WLTNetwork
			QNetworkConfiguration cfg;
			QNetworkConfigurationManager ncm;
			auto nc = ncm.allConfigurations();

			flag = 0;
			for (auto &x : nc)
			{
				if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
				{
					QString test = x.name();
					if (x.name() == "614wireless") {
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
		errorManager.pushErrorInfo("parseWLTData1");
		errorHandler(errorManager.getErrorInfo());
		resendRequest();
		return false;
	}

	lastResponseContent = requestContent1 = networkReply->readAll();
	networkReply->deleteLater();

	if (requestContent1 == "") {
		errorManager.pushErrorInfo(QString("no response content"));
		emit(outputLog(0, errorManager.getErrorInfo()));
		resendRequest();
		return false;
	}

	currentRequestId = RequestId::NoRequest;
	currentRequestRepeatNum = 0;

	if (-1 == requestContent1.indexOf("出口: 9移动测试国际出口", 0)) {
		errorHandler("set network export error\n");
		return false;
	}
	
	handleWLTData3();
	return true;
}
#endif