#include "BehaviourManager.h"

#ifdef ud_WLTNetwork
bool BehaviourManager::sendWLTRequest1() {
	if (currentRequestId != RequestId::NoRequest) {
		return false;
	}
	currentRequestId = RequestId::WLTRequest1;

	if (request != NULL) {
		delete request;
	}
	request = new QNetworkRequest();

	networkCookie->setCookies(QList<QNetworkCookie>());
	request->setUrl(QUrl("http://wlt.ustc.edu.cn/cgi-bin/ip"));
	request->setRawHeader("Host", "wlt.ustc.edu.cn");
	request->setRawHeader("Connection", "keep-alive");
	request->setRawHeader("Upgrade-Insecure-Requests", "1");
	request->setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36");
	request->setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
	request->setRawHeader("Referer", "http://wlt.ustc.edu.cn/");
	request->setRawHeader("Accept-Encoding", "gzip, deflate, sdch");
	request->setRawHeader("Accept-Language", "en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4");
	request->setRawHeader("Cookie", "name=; password=");

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseWLTData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendWLTRequest2() {
	if (currentRequestId != RequestId::NoRequest) {
		return false;
	}
	currentRequestId = RequestId::WLTRequest2;

	if (request != NULL) {
		delete request;
	}
	request = new QNetworkRequest();

	QByteArray Content = (QString("cmd=login&url=URL&ip=") + ipAddress + QString("&name=PW1994&password=123456&savepass=on&go=%B5%C7%C2%BC%D5%CA%BB%A7")).toUtf8();

	networkCookie->setCookies(QList<QNetworkCookie>());
	request->setUrl(QUrl("http://wlt.ustc.edu.cn/cgi-bin/ip"));
	request->setRawHeader("Host", "wlt.ustc.edu.cn");
	request->setRawHeader("Connection", "keep-alive");
	request->setRawHeader("Content-Length", QString::number(Content.length()).toUtf8());
	request->setRawHeader("Cache-Control", "max-age=0");
	request->setRawHeader("Origin", "http://wlt.ustc.edu.cn");
	request->setRawHeader("Upgrade-Insecure-Requests", "1");
	request->setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36");
	request->setRawHeader("Content-Type", "application/x-www-form-urlencoded");
	request->setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
	request->setRawHeader("Referer", "http://wlt.ustc.edu.cn/");
	request->setRawHeader("Accept-Encoding", "gzip, deflate");
	request->setRawHeader("Accept-Language", "en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4");
	request->setRawHeader("Cookie", "name=PW1994; password=123456");

	networkReply = networkManager->post(*request, Content);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseWLTData2()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}

bool BehaviourManager::sendWLTRequest3() {
	if (currentRequestId != RequestId::NoRequest) {
		return false;
	}
	currentRequestId = RequestId::WLTRequest3;

	if (request != NULL) {
		delete request;
	}
	request = new QNetworkRequest();

	networkCookie->setCookies(QList<QNetworkCookie>());
	request->setUrl(QUrl("http://wlt.ustc.edu.cn/cgi-bin/ip?cmd=set&url=URL&type=8&exp=0&go=+%BF%AA%CD%A8%CD%F8%C2%E7+"));
	request->setRawHeader("Host", "wlt.ustc.edu.cn");
	request->setRawHeader("Connection", "keep-alive");
	request->setRawHeader("Upgrade-Insecure-Requests", "1");
	request->setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36");
	request->setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
	request->setRawHeader("Referer", "http://wlt.ustc.edu.cn/");
	request->setRawHeader("Accept-Encoding", "gzip, deflate, sdch");
	request->setRawHeader("Accept-Language", "en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4");
	request->setRawHeader("Cookie", (QString("name=PW1994; password=123456; rn=") + rn).toUtf8());

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseWLTData3()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}
#endif