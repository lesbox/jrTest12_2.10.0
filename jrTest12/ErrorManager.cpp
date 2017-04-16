#include "ErrorManager.h"

ErrorManager::ErrorManager() {

}

ErrorManager::~ErrorManager() {

}

void ErrorManager::clear() {
	this->errorInfo.clear();
	return;
}

void ErrorManager::pushErrorInfo(QString errorInfo) {
	if (this->errorInfo.isEmpty()) {
		this->errorInfo = errorInfo;
	}
	else {
		this->errorInfo = errorInfo + "/" + this->errorInfo;
	}
	return;
}

QString ErrorManager::getErrorInfo() {
	return this->errorInfo;
}