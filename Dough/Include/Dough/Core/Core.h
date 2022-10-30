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
