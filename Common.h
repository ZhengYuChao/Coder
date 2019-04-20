/***************************************************************
 * Copyright(c) 2018-2019 Shenzhen Super Man Technologies Co. Ltd.
 * All right reserved.
 *
 * Filename		:	Common.h
 * Version		:	1.0
 * Abstract		:	
 * Author		:	Cyril Zheng(zhengyuchao666@gmail.com)
 * Created Date	:	2019.04.20
 *
 * Modified History:
 * 1.Create file.	2019.04.20  Cyril Zheng
 ***************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>
#include <ctype.h>

#include <sys/queue.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Debug.h"

typedef int ElementType;

#define		ARRAY_LENGTH			32
#define		ELEMENT_MAX				128
#define		THRESHOLD				(3)

void InitArray(ElementType Array[], int Length);
void ShowArray(ElementType Array[], int Length);
void SwapElement(ElementType *N, ElementType *M);

#endif
