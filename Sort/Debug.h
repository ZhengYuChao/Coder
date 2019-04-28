/***************************************************************
 * Copyright(c) 2018-2019 Shenzhen Super Man Technologies Co. Ltd.
 * All right reserved.
 *
 * Filename		:	Debug.h
 * Version		:	1.0
 * Abstract		:	
 * Author		:	Cyril Zheng(zhengyuchao666@gmail.com)
 * Created Date	:	2019.04.20
 *
 * Modified History:
 * 1.Create file.	2019.04.20  Cyril Zheng
 ***************************************************************/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#define		DEBUG_INFO(fmt, args...) \
	printf("[DEBUG](%s) %05d: "fmt"\r\n", __FUNCTION__, __LINE__, ##args)

#define		DEBUG_ERROR(fmt, args...) \
	printf("[ERROR](%s) %05d: "fmt"\r\n", __FUNCTION__, __LINE__, ##args)

#endif
