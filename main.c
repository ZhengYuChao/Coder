/***************************************************************
 * Copyright(c) 2018-2019 Shenzhen Super Man Technologies Co. Ltd.
 * All right reserved.
 *
 * Filename		:	main.c
 * Version		:	1.0
 * Abstract		:	
 * Author		:	Cyril Zheng(zhengyuchao666@gmail.com)
 * Created Date	:	2019.04.20
 *
 * Modified History:
 * 1.Create file.	2019.04.20  Cyril Zheng
 ***************************************************************/

#include "Common.h"

static void BubbleSort(ElementType Array[], int Length);
static void InsertSort(ElementType Array[], int Length);
static void ShellSort(ElementType Array[], int Length);
static void SelectSort(ElementType Array[], int Length);
static void HeapSort(ElementType Array[], int Length);
static void MergeSort(ElementType Array[], int Length);
static void QuickSort(ElementType Array[], int Length);
static void RadixSort(ElementType Array[], int Length);

typedef void (*SortFunc)(ElementType Array[], int Length);

static SortFunc SortFuncList[] = {
	BubbleSort,
	InsertSort,
	ShellSort,
	SelectSort,
	HeapSort,
	MergeSort,
	QuickSort,
	RadixSort,
	NULL
};

#define				LeftChild(i)			(2*(i) + 1)

static void BubbleSort(ElementType Array[], int Length)
{
	int i;
	int j;

	if (NULL == Array || Length <= 1) {
		return;
	}
	
	for (i = 0; i < Length; ++ i) {
		for (j = i; j < Length; ++ j) {
			if (Array[i] > Array[j]) {
				SwapElement(&Array[i], &Array[j]);
			}
		}
	}
}

static void InsertSort(ElementType Array[], int Length)
{
	int i;
	int j;
	ElementType Tmp;

	if (NULL == Array || Length <= 1) {
		return;
	}

	for (i = 1; i < Length; ++ i) {
		Tmp = Array[i];
		for (j = i; j > 0 && Array[j - 1] > Tmp; -- j) {
			Array[j] = Array[j - 1];
		}

		Array[j] = Tmp;
	}
}

static void SelectSort(ElementType Array[], int Length)
{
	int i;
	int j;
	int k;
	ElementType Tmp;

	if (NULL == Array || Length <= 1) {
		return;
	}

	for (i = 0; i < Length; ++ i) {
		Tmp = Array[i];
		k = i;
		for (j = i + 1; j < Length; ++ j) {
			if (Array[j] < Tmp) {
				Tmp = Array[j];
				k = j;
			}
		}

		SwapElement(&Array[i], &Array[k]);
	}
}

static void ShellSort(ElementType Array[], int Length)
{
	int i;
	int j;
	ElementType Tmp;
	int Increament = 0;

	if (NULL == Array || Length <= 1) {
		return;
	}

	for (Increament = Length; Increament > 0; Increament /= 2) {
		for (i = Increament; i < Length; ++ i) {
			Tmp = Array[i];
			for (j = i; j >= Increament && Array[j - Increament] > Tmp; j -= Increament) {
				Array[j] = Array[j - Increament];
			}

			Array[j] = Tmp;
		}
	}
}

static void AdjustHeap(ElementType Array[], int i, int Length)
{
	ElementType Tmp;
	int Child = 0;
	for (Tmp = Array[i]; LeftChild(i) < Length; i = Child) {
		Child = LeftChild(i);
		if (Child + 1 < Length && Array[Child + 1] > Array[Child]) {
			/* Right Child is Bigger */
			Child ++;
		}

		if (Array[Child] > Tmp) {
			Array[i] = Array[Child];
		} else {
			break;
		}
	}

	Array[i] = Tmp;
}

static void HeapSort(ElementType Array[], int Length)
{
	int i;
	if (NULL == Array || Length <= 1) {
		return;
	}

	for (i = Length / 2; i >= 0; -- i) {
		/* Build Heap */
		AdjustHeap(Array, i, Length);
	}

	for (i = Length - 1; i > 0; -- i) {
		/* Swap Max */
		SwapElement(&Array[0], &Array[i]);
		AdjustHeap(Array, 0, i);
	}
}

static void Merge(ElementType Array[], ElementType *TmpArray, int Left, int Right, int RightEnd)
{
	int i;
	int LeftEnd = Right - 1;
	int ElementNumber = RightEnd - Left + 1;
	int TmpPos = Left;

	while (Left <= LeftEnd && Right <= RightEnd) {
		if (Array[Left] < Array[Right]) {
			TmpArray[TmpPos ++] = Array[Left ++];
		} else {
			TmpArray[TmpPos ++] = Array[Right ++];
		}
	}

	while (Left <= LeftEnd) {
		TmpArray[TmpPos ++] = Array[Left ++];
	}

	while (Right <= RightEnd) {
		TmpArray[TmpPos ++] = Array[Right ++];
	}

	for (i = 0; i < ElementNumber; ++ i, -- RightEnd) {
		Array[RightEnd] = TmpArray[RightEnd];
	}
}

static void Msort(ElementType Array[], ElementType *TmpArray, int Left, int Right)
{
	int Center = 0;
	if (Left < Right) {
		Center = (Left + Right) / 2;
		Msort(Array, TmpArray, Left, Center);
		Msort(Array, TmpArray, Center + 1, Right);
		Merge(Array, TmpArray, Left, Center + 1, Right);
	}
}

static void MergeSort(ElementType Array[], int Length)
{
	ElementType *TmpArray = NULL;
	if (NULL == Array || Length <= 1) {
		return;
	}

	TmpArray = (ElementType *)malloc(Length * sizeof(ElementType));
	if (TmpArray) {
		Msort(Array, TmpArray, 0, Length - 1);
		free(TmpArray);
	} else {
		DEBUG_ERROR("malloc %m");
	}
}

ElementType Median3(ElementType Array[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (Array[Left] > Array[Center]) {
		SwapElement(&Array[Left], &Array[Center]);
	}

	if (Array[Left] > Array[Right]) {
		SwapElement(&Array[Left], &Array[Right]);
	}

	if (Array[Center] > Array[Right]) {
		SwapElement(&Array[Center], &Array[Right]);
	}

	SwapElement(&Array[Center], &Array[Right - 1]);
	return Array[Right - 1];
}

static void Qsort(ElementType Array[], int Left, int Right)
{
	int i;
	int j;
	int Pivot = 0;

	if (Left + THRESHOLD <= Right) {
		Pivot = Median3(Array, Left, Right);
		i = Left;
		j = Right - 1;
		while (1) {
			while (Array[++ i] < Pivot) {}
			while (Array[-- j] > Pivot) {}

			if (i < j) {
				SwapElement(&Array[i], &Array[j]);
			} else {
				break;
			}
		}

		/* Restore Pivot */
		SwapElement(&Array[i], &Array[Right - 1]);

		Qsort(Array, Left, i - 1);
		Qsort(Array, i + 1, Right);
	} else {
		InsertSort(Array + Left, Right - Left + 1);
	}
}

static void QuickSort(ElementType Array[], int Length)
{
	if (NULL == Array || Length <= 1) {
		return;
	}

	Qsort(Array, 0, Length - 1);
}

static void RadixSort(ElementType Array[], int Length)
{
	if (NULL == Array || Length <= 1) {
		return;
	}
}

int main(int argc, char const *argv[])
{
	int i;
	int size = sizeof(SortFuncList) / sizeof(SortFuncList[0]);
	ElementType Array[ARRAY_LENGTH] = {0};

	for (i = 0; i < size; ++ i) {
		if (NULL == SortFuncList[i])
		{
			continue;
		}

		DEBUG_INFO("Before Sort:");
		InitArray(Array, ARRAY_LENGTH);
		SortFuncList[i](Array, ARRAY_LENGTH);

		DEBUG_INFO("After Sort:");
		ShowArray(Array, ARRAY_LENGTH);
	}

	return 0;
}
