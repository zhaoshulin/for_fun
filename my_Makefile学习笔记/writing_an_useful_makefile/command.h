#ifndef COMMAND_H
#define COMMAND_H

#include "pub.h"//复合嵌套

extern "C"//为了能够在C++程序里面调用C函数，必须把每一个需要使用的C函数，其声明都包括在extern "C"{}块里面，这样C++链接时才能成功链接它们
{
	void command();
}

#endif
