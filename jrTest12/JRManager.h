#ifndef _UD_NETWORKREQUEST_
#define _UD_NETWORKREQUEST_

#include <QtCore/QCoreApplication>
#include "Commen.h"
#include "UserDataManager.h"
#include "BattleDataManager.h"
#include "InitDataManager.h"

#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\lib\\zlibstat.lib")

class ud_NetworkCookie : public QNetworkCookieJar
{
	Q_OBJECT

public:
	ud_NetworkCookie(QObject *parent);
	~ud_NetworkCookie();

	QList<QNetworkCookie> getCookies();
	void setCookies(const QList<QNetworkCookie>& cookieList);
private:

};

class JRManager : public QThread {
	Q_OBJECT

public:
	MiniUserDataManager userInfo;

	MiniInitDataManager initInfo;

public:
	JRManager();
	~JRManager();
};

#endif
