/***************************************************************
 * Copyright(c) 2018-2019 Shenzhen Super Man Technologies Co. Ltd.
 * All right reserved.
 *
 * Filename		:	Common.c
 * Version		:	1.0
 * Abstract		:	
 * Author		:	Cyril Zheng(zhengyuchao666@gmail.com)
 * Created Date	:	2019.04.20
 *
 * Modified History:
 * 1.Create file.	2019.04.20  Cyril Zheng
 ***************************************************************/

#include "Common.h"

void InitArray(ElementType Array[], int Length)
{
	int i;
	static unsigned int seed = 1;
	if (NULL == Array || Length <= 0) {
		return;
	}

	seed += THRESHOLD;
	/* Update Seed */
	srandom((unsigned int)(time(NULL) + seed));
	for (i = 0; i < Length; ++ i) {
		Array[i] = random() % ELEMENT_MAX;
	}

	ShowArray(Array, ARRAY_LENGTH);
}

void ShowArray(ElementType Array[], int Length)
{
	int i;
	if (NULL == Array || Length <= 0) {
		return;
	}

	for (i = 0; i < Length; ++ i) {
		printf("%d ", Array[i]);
	}

	printf("\r\n");
}

void SwapElement(ElementType *N, ElementType *M)
{
	ElementType Tmp;
	if (N && M) {
		Tmp = *N;
		*N = *M;
		*M = Tmp;
	}
}

