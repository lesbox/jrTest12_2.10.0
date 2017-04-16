#include "Commen.h"

double getDoubleFromQJsonValueRef(QJsonValueRef data, int & flag) {
	bool flagTemp;
	double valueTemp;

	if (data.isDouble()) {
		flag = 0;
		return data.toDouble();
	}
	else if (data.isString()) {
		if (data.toString().isEmpty()) {
			flag = 0;
			return 0;
		}
		else {
			valueTemp = data.toString().toDouble(&flagTemp);
			if (flagTemp == false) {
				flag = 1;
				return 0;
			}
			else {
				flag = 0;
				return valueTemp;
			}
		}
	}
	else {
		flag = 1;
		return 0;

	}
}

double getDoubleFromQJsonObject(QJsonObject data, QString key, int & flag) {
	bool flagTemp;
	double valueTemp;

	if (!data.contains(key)) {
		flag = 2;
		return 0;
	}
	else {
		if (data[key].isDouble()) {
			flag = 0;
			return data[key].toDouble();
		}
		else if (data[key].isString()) {
			if (data[key].toString() == "") {
				flag = 0;
				return 0;
			}
			else {
				valueTemp = data[key].toString().toDouble(&flagTemp);
				if (flagTemp == false) {
					QString test1 = data[key].toString();
					flag = 1;
					return 0;
				}
				else {
					flag = 0;
					return valueTemp;
				}
			}
		}
		else {
			flag = 1;
			return 0;
		}
	}
}

QString getStringFromQJsonValueRef(QJsonValueRef data, int & flag) {
	if (data.isString()) {
		flag = 0;
		return data.toString();
	}
	else {
		flag = 1;
		return "";
	}
}

QString getStringFromQJsonObject(QJsonObject data, QString key, int & flag) {
	if (!data.contains(key)) {
		flag = 2;
		return "";
	}
	else {
		if (data[key].isString()) {
			flag = 0;
			return data[key].toString();
		}
		else if (data[key].isDouble()) {
			flag = 0;
			return QString::number(data[key].toDouble());
		}
		else {
			flag = 1;
			return "";
		}
	}
}

int decompress(QByteArray source, QByteArray * dest) {
	int flag, flush;
	unsigned have;
	z_stream strm;
	unsigned char buffer[1024];

	dest->clear();

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;

	flag = inflateInit(&strm);
	if (flag != Z_OK) {
		return flag;
	}
	strm.avail_in = source.length();
	strm.next_in = (unsigned char *)(source.data());
	do {
		strm.avail_out = 1024;
		strm.next_out = buffer;
		flag = inflate(&strm, Z_NO_FLUSH);
		switch (flag) {
		case Z_NEED_DICT:
			flag = Z_DATA_ERROR;
		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
			inflateEnd(&strm);
			return flag;
		}
		dest->append((char *)buffer, 1024 - strm.avail_out);
	} while (strm.avail_out == 0);

	inflateEnd(&strm);

	if (flag != Z_STREAM_END) {
		dest->clear();
		return Z_DATA_ERROR;
	}
	return Z_OK;
}