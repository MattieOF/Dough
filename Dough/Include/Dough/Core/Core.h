#pragma once

//#ifdef DH_PLATFORM_WINDOWS
//	#ifdef DH_BUILD_DLL
//		#define DOUGH_API __declspec(dllexport)
//	#else
//		#define DOUGH_API __declspec(dllimport)
//	#endif
//#else
//	#error Dough currently only supports Windows.
//#endif

#define BIT(x) (1 << (x))

#ifdef DH_PLATFORM_WINDOWS
	#define UNALIGNED __unaligned
	#define FORCEINLINE __forceinline
#else
	#define UNALIGNED
	#define FORCEINLINE inline
#endif

// From winnt.h:
//
// RtlpNumberOf is a function that takes a reference to an array of N Ts.
//
// typedef T array_of_T[N];
// typedef array_of_T &reference_to_array_of_T;
//
// RtlpNumberOf returns a pointer to an array of N chars.
// We could return a reference instead of a pointer but older compilers do not accept that.
//
// typedef char array_of_char[N];
// typedef array_of_char *pointer_to_array_of_char;
//
// sizeof(array_of_char) == N
// sizeof(*pointer_to_array_of_char) == N
//
// pointer_to_array_of_char RtlpNumberOf(reference_to_array_of_T);
//
// We never even call RtlpNumberOf, we just take the size of dereferencing its return type.
// We do not even implement RtlpNumberOf, we just decare it.
//
// Attempts to pass pointers instead of arrays to this macro result in compile time errors.
// That is the point.
//
extern "C++" // templates cannot be declared to have 'C' linkage
template <typename T, size_t N>
char(*RtlpNumberOf(UNALIGNED T(&)[N]))[N];

#define DH_ARRAY_SIZE(A) (sizeof(*RtlpNumberOf(A)))

#ifdef DH_ENABLE_ASSERTS
	#define DH_ASSERT                PPK_ASSERT
	#define DH_ASSERT_WARNING        PPK_ASSERT_WARNING
	#define DH_ASSERT_DEBUG          PPK_ASSERT_DEBUG
	#define DH_ASSERT_ERROR          PPK_ASSERT_ERROR
	#define DH_ASSERT_FATAL          PPK_ASSERT_FATAL
	#define DH_ASSERT_CUSTOM         PPK_ASSERT_CUSTOM
	#define DH_ASSERT_USED           PPK_ASSERT_USED
	#define DH_ASSERT_USED_WARNING   PPK_ASSERT_USED_WARNING
	#define DH_ASSERT_USED_DEBUG     PPK_ASSERT_USED_DEBUG
	#define DH_ASSERT_USED_ERROR     PPK_ASSERT_USED_ERROR
	#define DH_ASSERT_USED_FATAL     PPK_ASSERT_USED_FATAL
	#define DH_ASSERT_USED_CUSTOM    PPK_ASSERT_USED_CUSTOM
#else
	#define DH_ASSERT                
	#define DH_ASSERT_WARNING        
	#define DH_ASSERT_DEBUG          
	#define DH_ASSERT_ERROR          
	#define DH_ASSERT_FATAL          
	#define DH_ASSERT_CUSTOM         
	#define DH_ASSERT_USED           
	#define DH_ASSERT_USED_WARNING   
	#define DH_ASSERT_USED_DEBUG     
	#define DH_ASSERT_USED_ERROR     
	#define DH_ASSERT_USED_FATAL     
	#define DH_ASSERT_USED_CUSTOM
#endif

namespace Dough
{
	void Init();
}
