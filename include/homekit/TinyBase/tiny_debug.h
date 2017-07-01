/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_debug.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_DEBUG_H__
#define __TINY_DEBUG_H__


#ifdef TINY_DEBUG
    #ifdef _WIN32
        #include <crtdbg.h>
        #define RETURN_IF_FAIL(p) if(!(p)) \
                        {printf("%s:%d Warning: "#p" failed.\n", \
                        __FILE__, __LINE__); return;}
        #define RETURN_VAL_IF_FAIL(p, ret) if(!(p)) \
            	        {printf("%s:%d Warning: "#p" failed.\n", \
                        __FILE__, __LINE__); return (ret);}
    #else
        #define RETURN_IF_FAIL(p) if(!(p)) \
            	        {printf("%s:%d Warning: "#p" failed.\n", \
                        __func__, __LINE__); return;}
        #define RETURN_VAL_IF_FAIL(p, ret) if(!(p)) \
            	        {printf("%s:%d Warning: "#p" failed.\n", \
                        __func__, __LINE__); return (ret);}
    #endif /* _WIN32 */
#else
    #define RETURN_IF_FAIL(p)
    #define RETURN_VAL_IF_FAIL(p, ret)
#endif /* TINY_DEBUG */


#endif /* __TINY_TYPEDEF_H__ */
