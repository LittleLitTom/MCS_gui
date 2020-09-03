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

uint utilities::psIdToNum(const QString psId)
{
	if (psId.count() < 3 || psId.count()>8)
	{
		return 0;
	}
	int m, n,p,q = 0;
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
	return (100000000+m*1000000+n*10000+tem.toInt()*100);
}
