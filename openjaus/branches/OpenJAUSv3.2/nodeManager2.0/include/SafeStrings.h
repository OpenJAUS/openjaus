#ifndef SAFE_STRINGS_H
#define SAFE_STRINGS_H

#if defined(_MSC_VER)
	#define SAFE_SPRINTF sprintf_s
	#define SAFE_STRTOK strtok_s
#elif defined(__GNUC__) || defined(__MINGW32__)
	#define SAFE_SPRINTF snprintf
	#define SAFE_STRTOK strtok_r
#else
	#error "No Known Thread-Safe Strings!"
#endif 

#endif

