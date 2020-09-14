#include "utilities.h"

unsigned int utilities::floatToByte(float float_)
{
	MyUnion a;
	a.float_ = float_;
	return a.uint_;
}

float utilities::byteToFloat(unsigned int uint_)
{
	MyUnion a;
	a.uint_ = uint_;
	return a.float_;
}

void utilities::OpcVarToQtVar(const OpcUa_Variant& opcVar, QVariant& qtVar)
{
	//对opcua_variant中的Datatype与Arraytype的解释如下：
	//Datatype: 1(bool)  10(float)  11(double)  6(Int32)  8(Int64)  7(Uint32)  9(Uint64)  ......
	//ArrayType: 0(scarlar)  1(one demension)  ......
	
	if (opcVar.ArrayType == 0)//标量
	{
		switch (opcVar.Datatype)
		{
		case 1://bool
			qtVar.setValue<bool>(opcVar.Value.Boolean);
			break;
		case 6://Int32
			qtVar.setValue<int>(opcVar.Value.Int32);
			break;
		case 7://Uint32
			qtVar.setValue<uint>(opcVar.Value.UInt32);
			break;
		case 8://Int64
			qtVar.setValue<INT64>(opcVar.Value.Int64);
			break;
		case 9://Uint64
			qtVar.setValue<UINT64>(opcVar.Value.UInt64);
			break;
		case 10://float
			qtVar.setValue<float>(opcVar.Value.Float);
			break;
		case 11://double
			qtVar.setValue<double>(opcVar.Value.Double);
			break;
		}
	}
	else if (opcVar.ArrayType == 1)//一维向量
	{
		switch (opcVar.Datatype)
		{
		case 1://bool
		{
			QList<bool> tem;
			for (int i = 0; i < opcVar.Value.Array.Length; i++)
			{
				tem.append(opcVar.Value.Array.Value.BooleanArray[i]);
			}
			qtVar.setValue<QList<bool>>(tem);
			break;
		}
		case 6://Int32
		{
			QList<INT32> tem;
			for (int i = 0; i < opcVar.Value.Array.Length; i++)
			{
				tem.append(opcVar.Value.Array.Value.Int32Array[i]);
			}
			qtVar.setValue<QList<INT32>>(tem);
			break;
		}
		case 7://Uint32
		{
			QList<UINT32> tem;
			for (int i = 0; i < opcVar.Value.Array.Length; i++)
			{
				tem.append(opcVar.Value.Array.Value.UInt32Array[i]);
			}
			qtVar.setValue<QList<UINT32>>(tem);
			break;
		}
		case 8://Int64
		{
			QList<INT64> tem;
			for (int i = 0; i < opcVar.Value.Array.Length; i++)
			{
				tem.append(opcVar.Value.Array.Value.Int64Array[i]);
			}
			qtVar.setValue<QList<INT64>>(tem);
			break;
		}
		case 9://Uint64
		{
			QList<UINT64> tem;
			for (int i = 0; i < opcVar.Value.Array.Length; i++)
			{
				tem.append(opcVar.Value.Array.Value.UInt64Array[i]);
			}
			qtVar.setValue<QList<UINT64>>(tem);
			break;
		}
		case 10://float
		{
			QList<float> tem;
			for (int i = 0; i < opcVar.Value.Array.Length; i++)
			{
				tem.append(opcVar.Value.Array.Value.FloatArray[i]);
			}
			qtVar.setValue<QList<float>>(tem);
			break;
		}
		case 11://double
		{
			QList<double> tem;
			for (int i = 0; i < opcVar.Value.Array.Length; i++)
			{
				tem.append(opcVar.Value.Array.Value.DoubleArray[i]);
			}
			qtVar.setValue<QList<double>>(tem);
			break;
		}
		}
	}
	else if (opcVar.ArrayType == 2)//二维向量
	{
		//处理代码
	}
}

void utilities::QtVarToOpcVar(const QVariant& qtVar, OpcUa_Variant& opcVar)
{
	switch (qtVar.type())
	{
	case 1://bool
		opcVar.Value.Boolean = qtVar.toBool();
		break;
	case 2://Int
		opcVar.Value.Int32 = qtVar.toInt();
		break;
	case 3://Uint
		opcVar.Value.UInt32 = qtVar.toUInt();
		break;
	case 4://LongLong
		opcVar.Value.Int64 = qtVar.toLongLong();
		break;
	case 5://ULongLong
		opcVar.Value.UInt64 = qtVar.toULongLong();
		break;
	case 6://Double
		opcVar.Value.Double = qtVar.toDouble();
		break;
	case 38://Float
		opcVar.Value.Float = qtVar.toFloat();
		break;
	case 9://QVariantList
		auto varList = qtVar.toList();
		opcVar.Value.Array.Length = varList.count();
		opcVar.ArrayType = 1;
		switch (varList[0].type())
		{
		case 1://bool
			for (int i = 0; i < varList.count(); i++)
			{
				opcVar.Value.Array.Value.BooleanArray[i] = qtVar.toList()[i].toBool();
			}
			break;
		case 2://Int
			for (int i = 0; i < varList.count(); i++)
			{
				opcVar.Value.Array.Value.Int32Array[i] = qtVar.toList()[i].toInt();
			}
			break;
		case 3://Uint
			for (int i = 0; i < varList.count(); i++)
			{
				opcVar.Value.Array.Value.UInt32Array[i] = qtVar.toList()[i].toUInt();
			}
			break;
		case 4://LongLong
			for (int i = 0; i < varList.count(); i++)
			{
				opcVar.Value.Array.Value.Int64Array[i] = qtVar.toList()[i].toLongLong();
			}
			break;
		case 5://ULongLong
			for (int i = 0; i < varList.count(); i++)
			{
				opcVar.Value.Array.Value.UInt64Array[i] = qtVar.toList()[i].toULongLong();
			}
			break;
		case 6://Double
			for (int i = 0; i < varList.count(); i++)
			{
				opcVar.Value.Array.Value.DoubleArray[i] = qtVar.toList()[i].toDouble();
			}
			break;
		case 38://Float
			for (int i = 0; i < varList.count(); i++)
			{
				opcVar.Value.Array.Value.FloatArray[i] = qtVar.toList()[i].toFloat();
			}
			break;
		}
	}
}

void utilities::UaVarToQtVar(const UaVariant& UaVar, QVariant& QtVar)
{
	if (UaVar.isArray())//如果UaVariant是数组形式
	{
		QVariantList ret;
		switch (UaVar.type())
		{
		case 1://bool
		{
			UaBoolArray uaSpecific;
			UaVar.toBoolArray(uaSpecific);

			for (int i=0;i<UaVar.arraySize();i++)
			{
				ret.push_back(QVariant(static_cast<bool>(uaSpecific[i])));
			}
			QtVar.setValue<QVariantList>(ret);
		}
			break;
		case 6://Int32
		{
			UaInt32Array uaSpecific;
			UaVar.toInt32Array(uaSpecific);

			for (int i = 0; i < UaVar.arraySize(); i++)
			{
				ret.push_back(QVariant(static_cast<int>(uaSpecific[i])));
			}
			QtVar.setValue<QVariantList>(ret);
		}
			break;
		case 7://Uint32
		{
			UaUInt32Array uaSpecific;
			UaVar.toUInt32Array(uaSpecific);

			for (int i = 0; i < UaVar.arraySize(); i++)
			{
				ret.push_back(QVariant(static_cast<uint>(uaSpecific[i])));
			}
			QtVar.setValue<QVariantList>(ret);
		}
			break;
		case 8://Int64
		{
			UaInt64Array uaSpecific;
			UaVar.toInt64Array(uaSpecific);

			for (int i = 0; i < UaVar.arraySize(); i++)
			{
				ret.push_back(QVariant(static_cast<long long>(uaSpecific[i])));
			}
			QtVar.setValue<QVariantList>(ret);
		}
			break;
		case 9://Uint64
		{
			UaUInt64Array uaSpecific;
			UaVar.toUInt64Array(uaSpecific);

			for (int i = 0; i < UaVar.arraySize(); i++)
			{
				ret.push_back(QVariant(static_cast<unsigned long long>(uaSpecific[i])));
			}
			QtVar.setValue<QVariantList>(ret);
		}
			break;
		case 10://float
		{
			UaFloatArray uaSpecific;
			UaVar.toFloatArray(uaSpecific);

			for (int i = 0; i < UaVar.arraySize(); i++)
			{
				ret.push_back(QVariant(static_cast<float>(uaSpecific[i])));
			}
			QtVar.setValue<QVariantList>(ret);
		}
			break;
		case 11://double
		{
			UaDoubleArray uaSpecific;
			UaVar.toDoubleArray(uaSpecific);

			for (int i = 0; i < UaVar.arraySize(); i++)
			{
				ret.push_back(QVariant(static_cast<double>(uaSpecific[i])));
			}
			QtVar.setValue<QVariantList>(ret);
		}
			break;
		}
	}
	else//如果UaVariant是标量形式
	{
		switch (UaVar.type())
		{
		case 1://bool
		{
			boolean ret;
			UaVar.toBool(ret);
			QtVar.setValue<bool>(ret);
		}
		break;
		case 6://Int32
		{
			OpcUa_Int32 ret;
			UaVar.toInt32(ret);
			QtVar.setValue<int>(ret);
		}
		break;
		case 7://Uint32
		{
			OpcUa_UInt32 ret;
			UaVar.toUInt32(ret);
			QtVar.setValue<uint>(ret);
		}
		break;
		case 8://Int64
		{	OpcUa_Int64 ret;
			UaVar.toInt64(ret);
			QtVar.setValue<INT64>(ret);
		}
		break;
		case 9://Uint64
		{
			OpcUa_UInt64 ret;
			UaVar.toUInt64(ret);
			QtVar.setValue<UINT64>(ret);
		}
		break;
		case 10://float
		{
			OpcUa_Float ret;
			UaVar.toFloat(ret);
			QtVar.setValue<float>(ret);
		}
		break;
		case 11://double
		{
			OpcUa_Double ret;
			UaVar.toDouble(ret);
			QtVar.setValue<double>(ret);
		}
		break;
		}
	}
}

void utilities::QtVarToUaVar(const QVariant& QtVar, UaVariant& UaVar)
{
	switch (QtVar.type())
	{
	case 1://bool
		UaVar.setBool(QtVar.toBool());
		break;
	case 2://int
		UaVar.setInt32(QtVar.toInt());
		break;
	case 3://Uint
		UaVar.setUInt32(QtVar.toUInt());
		break;
	case 4://LongLong
		UaVar.setInt64(QtVar.toLongLong());
		break;
	case 5://ULongLong
		UaVar.setUInt64(QtVar.toULongLong());
		break;
	case 6://Double
		UaVar.setDouble(QtVar.toDouble());
		break;
	case 9://QvariantList
		{
		auto varList = QtVar.toList();
		if (varList[0].type() == 1)//bool
		{
			UaBoolArray tem;
			tem.create(varList.count());
			int i = 0;
			for (auto var : varList)
			{
				tem[i] = var.toBool();
				i++;
			}
			UaVar.setBoolArray(tem);
		}
		else if (varList[0].type() == 2)//int
		{
			UaInt32Array tem;
			tem.create(varList.count());
			int i = 0;
			for (auto var : varList)
			{
				tem[i] = var.toInt();
				i++;
			}
			UaVar.setInt32Array(tem);
		}
		else if (varList[0].type() == 3)//Uint
		{
			UaUInt32Array tem;
			tem.create(varList.count());
			int i = 0;
			for (auto var : varList)
			{
				tem[i] = var.toUInt();
				i++;
			}
			UaVar.setUInt32Array(tem);
		}
		else if (varList[0].type() == 4)//LongLong
		{
			UaInt64Array tem;
			tem.create(varList.count());
			int i = 0;
			for (auto var : varList)
			{
				tem[i] = var.toLongLong();
				i++;
			}
			UaVar.setInt64Array(tem);
		}
		else if (varList[0].type() == 5)//ULongLong
		{
			UaUInt64Array tem;
			tem.create(varList.count());
			int i = 0;
			for (auto var : varList)
			{
				tem[i] = var.toULongLong();
				i++;
			}
			UaVar.setUInt64Array(tem);
		}
		else if (varList[0].type() == 6)//Double
		{
			UaDoubleArray tem;
			tem.create(varList.count());
			int i = 0;
			for (auto var : varList)
			{
				tem[i] = var.toDouble();
				i++;
			}
			UaVar.setDoubleArray(tem);
		}
		else if (varList[0].type() == 38)//float
		{
			UaFloatArray tem;
			tem.create(varList.count());
			int i = 0;
			for (auto var : varList)
			{
				tem[i] = var.toFloat();
				i++;
			}
			UaVar.setFloatArray(tem);
		}
		}
		break;
	case 38://float
		UaVar.setFloat(QtVar.toFloat());
		break;
	}
}

uint utilities::psIdToNum(const QString psId)
{
	//非TreeWidget叶子节点，此时不能够构成电源Id
	if (psId.count() < 3 || psId.count()>8)
	{
		return 0;
	}
	uint m=0, n=0, p=0, q = 0;
	if ((*psId.begin()) == 'Q')
	{
		m = 1;
		p = 1;
	}
	else if ((*psId.begin()) == 'B')
	{
		m = 2;
		p = 1;
	}
	else if ((*(psId.begin()+2)) == 'X')
	{
		m = 3;
		p = 3;
	}
	else if ((*(psId.begin()+2)) == 'Y')
	{
		m = 4;
		p = 3;
	}

	if ((*(psId.end() - 1)) == 'E')
	{
		n = 1;
		q = 1;
	}
	else if ((*(psId.end() - 1)) == '1')
	{
		q = 2;
		if ((*(psId.end() - 2)) == 'S')
		{
			n = 2;
		}
		else if ((*(psId.end() - 2)) == 'F')
		{
			n = 3;
		}
	}
	else if ((*(psId.end() - 1)) == '2')
	{
		q = 2;
		if ((*(psId.end() - 2)) == 'P')
		{
			n = 4;
		}
		else if ((*(psId.end() - 2)) == 'S')
		{
			n = 5;
		}
		else if ((*(psId.end() - 2)) == 'G')
		{
			n = 6;
		}
	}
	else if ((*(psId.end() - 1)) == '3')
	{
		q = 2;
		if ((*(psId.end() - 2)) == 'P')
		{
			n = 7;
		}
		else if ((*(psId.end() - 2)) == 'S')
		{
			n = 8;
		}
		else if ((*(psId.end() - 2)) == 'G')
		{
			n = 9;
		}
	}

	QString tem;
	for (auto iter = psId.begin() + p; iter < psId.end() - q; iter++)
	{
		tem.append(*iter);
	}
	//100000000是子系统
	return (100000000+m*1000000+n*10000+tem.toUInt()*100);
}

uint utilities::scIdToNum(const QString bdId)
{
	uint m = 0, n = 0, p = 0, q = 0;

	//求m
	if (*bdId.begin() == "F")
	{
		m = 1;
		p = 2;
	}
	else if (*bdId.begin() == "S")
	{
		m = 2;
		p = 2;
	}
	else if (*bdId.begin() == "I")
	{
		m = 3;
		p = 2;
	}
	//求n及q
	if ((*(bdId.end() - 1)) == 'E')
	{
		n = 1;
		q = 1;
	}
	else if ((*(bdId.end() - 1)) == '1')
	{
		q = 2;
		if ((*(bdId.end() - 2)) == 'S')
		{
			n = 2;
		}
		else if ((*(bdId.end() - 2)) == 'F')
		{
			n = 3;
		}
	}
	else if ((*(bdId.end() - 1)) == '2')
	{
		q = 2;
		if ((*(bdId.end() - 2)) == 'P')
		{
			n = 4;
		}
		else if ((*(bdId.end() - 2)) == 'S')
		{
			n = 5;
		}
		else if ((*(bdId.end() - 2)) == 'G')
		{
			n = 6;
		}
	}
	else if ((*(bdId.end() - 1)) == '3')
	{
		q = 2;
		if ((*(bdId.end() - 2)) == 'P')
		{
			n = 7;
		}
		else if ((*(bdId.end() - 2)) == 'S')
		{
			n = 8;
		}
		else if ((*(bdId.end() - 2)) == 'G')
		{
			n = 9;
		}
	}
	//求tem
	QString tem;
	for (auto iter = bdId.begin() + p; iter < bdId.end() - q; iter++)
	{
		tem.append(*iter);
	}
	//200000000
	return (200000000 + m * 1000000 + n * 10000 + tem.toUInt() * 100);
}
