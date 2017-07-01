/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   IotCode.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IOT_CODE_H__
#define __IOT_CODE_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef enum _IotError {

    /* success */
    IOT_SUCCESS = 200,

    /* The action name doest note mactch any of the actions for this service. */
    IOT_ERR_INVALID_ACTION = 401,

    /* Not enough input arguments,
    or toomany input arguments,
    or input arguments with the wrong name,
    or input arguments with the wrong Object urn. */
    IOT_ERR_INVALID_ARGS = 402,

    /* The service doest not support the sate variable.  */
    IOT_ERR_INVALID_VAR = 404,

    /* The current state of the service prevents invoking this action. */
    IOT_ERR_ACTION_FAILED = 501,

    /* The argument value is invalid. */
    IOT_ERR_ARGUMENT_VALUE_INVALID = 600,

    /* The argument value out of range. */
    IOT_ERR_ARGUMENT_VALUE_OUT_OF_RANGE = 601,

    /* The requested action is optional and it has not been implemented .*/
    IOT_ERR_OPTIONAL_ACTION_NOT_IMPLEMENTED = 602,

    /* The action can not be completed because the device does note have enough memroy. */
    IOT_ERR_OUT_OF_MEMORY = 603,

    /* The action cannot be completed and human intervention is required. */
    IOT_ERR_HUMAN_INTERVENTION_REQUIRED = 604,

    /* The action has a string argument that is too long. */
    IOT_ERR_STRING_ARGUMENT_TOO_LONG = 605,

    /* The action requires authorization and the sender is not authorized. */
    IOT_ERR_ACTION_NOT_AUTHORIZED = 606,

    IOT_ERR_SIGNATURE_FAILURE = 607,
    IOT_ERR_SIGNATURE_MISSING = 608,
    IOT_ERR_NOT_ENCRYPTED = 609,
    IOT_ERR_INVALID_SEQUENCE = 610,
    IOT_ERR_INVALID_CONTROL_URL = 611,
    IOT_ERR_NO_SUCH_SESSION = 612,
} IotError;


TINY_END_DECLS

#endif /* __IOT_CODE_H__ */
