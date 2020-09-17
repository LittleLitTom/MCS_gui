#pragma once
#include <stdlib.h>
#include <QtCore>
#include "uasession.h"

union MyUnion
{
	float float_;
	unsigned int uint_;
};

class utilities
{
public:
	static unsigned int floatToByte(float float_);
	static float byteToFloat(unsigned int uint_);
	static void OpcVarToQtVar(const OpcUa_Variant&,QVariant&);
	static void QtVarToOpcVar(const QVariant&,OpcUa_Variant&);
	static void UaVarToQtVar(const UaVariant&,QVariant&);
	static void QtVarToUaVar(const QVariant&,UaVariant&);
	static uint psIdToNum(const QString);
	static uint scIdToNum(const QString);

	//.....”Î ¯≤‚≤‚ ‘œ‡πÿ
	static QString scStandardToUserId(uint);
	static uint scUserToStandardId(QString);
	//....
};
