#ifndef LOGGING_H
#define LOGGING_H

#ifdef DEBUG

	#include <stdio.h>

	#define LOGV(TAG, STR, ...) printf("V/%s ", TAG); printf(STR, __VA_ARGS__); printf("\n")
	#define LOGD(TAG, STR, ...) printf("D/%s ", TAG); printf(STR, __VA_ARGS__); printf("\n")
	#define LOGI(TAG, STR, ...) printf("I/%s ", TAG); printf(STR, __VA_ARGS__); printf("\n")
	#define LOGW(TAG, STR, ...) printf("W/%s ", TAG); printf(STR, __VA_ARGS__); printf("\n")
	#define LOGE(TAG, STR, ...) printf("E/%s ", TAG); printf(STR, __VA_ARGS__); printf("\n")

	// use *S versions of logging for Single-arg or Simple version, simple string
	// arg with no format specifiers.
	#define LOGVS(TAG, STR) printf("V/%s ", TAG); printf(STR); printf("\n")
	#define LOGDS(TAG, STR) printf("D/%s ", TAG); printf(STR); printf("\n")
	#define LOGIS(TAG, STR) printf("I/%s ", TAG); printf(STR); printf("\n")
	#define LOGWS(TAG, STR) printf("W/%s ", TAG); printf(STR); printf("\n")
	#define LOGES(TAG, STR) printf("E/%s ", TAG); printf(STR); printf("\n")

#else

	#define LOGV(TAG,...)
	#define LOGD(TAG,...)
	#define LOGI(TAG,...)
	#define LOGW(TAG,...)
	#define LOGE(TAG,...)

	// single-string versions, preprocessor doesn't handle empty __VA_ARGS__ list
	// well for vprintf
	#define LOGVS(TAG,...)
	#define LOGDS(TAG,...)
	#define LOGIS(TAG,...)
	#define LOGWS(TAG,...)
	#define LOGES(TAG,...)

#endif

#endif