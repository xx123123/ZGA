/*
 * ICONS Constants - Generic Constants for Device Driver Interface Functions
 *
 * Author: ICO
 * Date: 2015/04
 */
#ifndef _ICONS_CONST_h
#define _ICONS_CONST_h

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN64
#define _EXPORT_CALL	__declspec(dllexport) __stdcall
#else
#define _EXPORT_CALL	__declspec(dllexport)
#define	CALLBACK
#endif

#define	ICONS_TRUE	1
#define ICONS_FALSE	0
#define	ICONS_NOT_DETERMINED	-1
#define	ICONS_ON	1
#define ICONS_OFF	0

#define ICONS_DEV_ENABLE	1
#define ICONS_DEV_DISABLE	0

#define ICONS_DEV_ERROR	-1
#define ICONS_DEV_NOT_AVAILABLE	-9
#define ICONS_DEV_NOT_CONNECTED -8



#define ICONS_SUCCESS	0
#define	ICONS_NO_ERROR	0

#define	ICONS_FUNCTION_NOT_SUPPORTED	-99
#define	ICONS_PARAMETER_NOT_SUPPORTED	-98
#define ICONS_OPTION_NOT_SUPPORTED	-97
#define ICONS_FILE_OPENING_FAIL		-96
#define ICONS_FILE_WRITE_ERROR		-95
#define ICONS_BUFFER_NOT_LARGE_ENOUGH	-94

#define ICONS_OPERATION_TIMEOUT		-90
#define	ICONS_OPERATION_USER_STOPPED	-91
#define	ICONS_OPERATION_FAIL		-92

// Error log levels
#define ICONS_LOG_ERROR		10
#define ICONS_LOG_WARNING	20
#define ICONS_LOG_INTERFACE	30
#define ICONS_LOG_INFORMATION	40
#define ICONS_LOG_TRACE		50
#define ICONS_LOG_MASKEDDATA	60
#define ICONS_LOG_DEBUG		200

#ifdef __cplusplus
}
#endif

#endif
