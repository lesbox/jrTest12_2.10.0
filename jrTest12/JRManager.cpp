#include "JRManager.h"

ud_NetworkCookie::ud_NetworkCookie(QObject *parent) {

}

ud_NetworkCookie::~ud_NetworkCookie() {

}

QList<QNetworkCookie> ud_NetworkCookie::getCookies() {
	return allCookies();
}

void ud_NetworkCookie::setCookies(const QList<QNetworkCookie>& cookieList) {
	setAllCookies(cookieList);
	return;
}

JRManager::JRManager() {

}

JRManager::~JRManager() {

}