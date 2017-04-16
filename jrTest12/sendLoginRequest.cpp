#include "BehaviourManager.h"

bool BehaviourManager::sendLoginRequest1() {
	currentRequestId = RequestId::LoginRequest1;

	buildRequest("http://version.jr.moefantasy.com/index/checkVer/2.10.0/2/0&market=2&channel=0&version=2.10.0", false, false, QMap<QByteArray, QByteArray>(), QString("version.jr.moefantasy.com"));
	
	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);
	return true;
}

bool BehaviourManager::sendLoginRequest2() {
	currentRequestId = RequestId::LoginRequest2;

	LoginBehaviourParameter loginBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<LoginBehaviourParameter>();
	jrData.userInfo.currentServer = loginBehaviourParameterTemp.serverId;

	QByteArray Content = (QString("username=") + loginBehaviourParameterTemp.username + QString("&pwd=") + loginBehaviourParameterTemp.password).toUtf8();

	QMap<QByteArray, QByteArray> extraRawHeader;
	extraRawHeader.insert("Content-Type", "application/x-www-form-urlencoded");
	extraRawHeader.insert("Content-Length", QString::number(Content.length()).toUtf8());

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/index/passportLogin/"), true, false, extraRawHeader, QString("login.jr.moefantasy.com"));

	networkReply = networkManager->post(*request, Content);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData2()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendLoginRequest3() {
	currentRequestId = RequestId::LoginRequest3;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com//index/login/") + QString::number(jrData.userInfo.userId));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData3()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendLoginRequest4() {
	currentRequestId = RequestId::LoginRequest4;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/api/initGame/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData4()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendLoginRequest5() {
	currentRequestId = RequestId::LoginRequest5;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/getPveData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData5()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendLoginRequest6() {
	currentRequestId = RequestId::LoginRequest6;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pevent/getPveData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData6()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendLoginRequest7() {
	currentRequestId = RequestId::LoginRequest7;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/active/getUserData/"));
	
	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData7()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendLoginRequest8() {
	currentRequestId = RequestId::LoginRequest8;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/pve/getUserData/"));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData8()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendLoginRequest9() {
	currentRequestId = RequestId::LoginRequest9;

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/campaign/getUserData/"));
	
	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseLoginData9()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}