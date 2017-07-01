/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Timer.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


#define TIMER_ID_LEN              64

struct _Timer;
typedef struct _Timer Timer;

typedef void (* TimerHandler)(Timer *thiz, void *ctx);

struct _Timer
{
    char                    id[TIMER_ID_LEN];
    int64_t                 elapsedUS;
    void                  * ctx;
    TimerHandler            handler;
};

Timer * Timer_New(const char *id, int64_t elapsed, void *ctx, TimerHandler handler);
void Timer_Delete(Timer *thiz);


TINY_END_DECLS

#endif /* __TIMER_H__ */
