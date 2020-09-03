#pragma once
#include <stdlib.h>
#include <QtCore>
#include "Uabase.h"

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
	static uint psIdToNum(const QString);
};
