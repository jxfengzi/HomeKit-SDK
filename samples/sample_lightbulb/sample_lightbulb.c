#include <thing/ThingManager.h>
#include <HapAccessoryImpl.h>
#include "mysocket.h"
#include "persistence/HapPersistenceImpl.h"
#include "hap/AccessoryCategoryIdentifier.h"
#include "hap/AccessoryHost.h"

static void print_version_info(void)
{
    printf("HomeKit Lightbulb\n");
    printf("Version 0.1\n");
    printf("Author: ouyang\n");
    printf("Wechat: 178915185\n");
    printf("PIN-CODE: 031-45-154\n");
}

void print_value(Property *property)
{
    switch (property->data.type)
    {
        case DATATYPE_BOOL:
            printf("value: %s\n", property->data.value.boolValue.value ? "true": "false");
            break;

        case DATATYPE_UINT8:
            printf("value: %d\n", property->data.value.uint8Value.value);
            break;

        case DATATYPE_UINT16:
            printf("value: %d\n", property->data.value.uint16Value.value);
            break;

        case DATATYPE_UINT32:
            printf("value: %d\n", property->data.value.uint32Value.value);
            break;

        case DATATYPE_UINT64:
#ifdef __MAC_OSX__
            printf("value: %llu\n", property->data.value.uint64Value.value);
#else
            printf("value: %ld\n", property->data.value.uint64Value.value);
#endif
            break;

        case DATATYPE_INT:
            printf("value: %d\n", property->data.value.intValue.value);
            break;

        case DATATYPE_FLOAT:
            printf("value: %f\n", property->data.value.floatValue.value);
            break;

        case DATATYPE_STRING:
            printf("value: %s\n", property->data.value.stringValue.value);
            break;

        case DATATYPE_TLV8:
            break;

        case DATATYPE_DATA:
            break;

        default:
            break;
    }
}

static void OnIdentify(void)
{
    printf("OnIdentify\n");
}

static void OnCharacteristicGet(Property *property)
{
    printf("OnGet: characteristics.name = %s, aid=[%d] iid = [%d]\n", property->type.name, property->aiid, property->iid);

    switch (property->iid)
    {
        // on
        case 9:
            break;

        default:
            break;
    }
}

static void OnCharacteristicSet(Property *property)
{
    printf("OnSet: characteristics.name = %s, aid=[%d] iid = [%d]\n", property->type.name, property->aiid, property->iid);
    print_value(property);

    switch (property->iid)
    {
        // identify
        case 2:
            OnIdentify();
            break;

        // on
        case 9:
            // property->data.value.boolValue.value;
            break;

        default:
            break;
    }
}

static void MyConfigurationInitializer(DeviceConfig *thiz, void *ctx)
{
    char ip[512];
    int ret = 0;
    size_t length = 0;

    DeviceConfig_SetIp(thiz, "10.0.1.9");

    printf("INPUT IP [default = 10.0.1.9]: ");
    memset(ip, 0, TINY_IP_LEN);
    ret = scanf("%s", ip);
    length = strlen(ip);
    if (length < 8 || length > 32)
    {
        printf("IP = 10.0.1.8\n");
    }
    else
    {
        printf("IP = %s\n", ip);
        DeviceConfig_SetIp(thiz, ip);
    }

    DeviceConfig_SetName(thiz, "Ouyang");
    DeviceConfig_SetId(thiz, "1C:BE:EE:01:01:07");
    DeviceConfig_SetModelName(thiz, "light");
    DeviceConfig_SetConfigurationNumber(thiz, 2);
    DeviceConfig_SetCurrentStateNumber(thiz, 1);
    DeviceConfig_SetFeatureFlags(thiz, 0);
    DeviceConfig_SetCategoryIdentifier(thiz, ACCESSORY_CATEGORY_OTHER);
    DeviceConfig_SetPinCode(thiz, "031-45-154");
}

static TinyRet _start(void)
{
    TinyRet ret = TINY_RET_OK;
    DeviceConfig config;
    AccessoryHost *host = NULL;

    print_version_info();

    // 0. init socket
    ret = my_socket_init();
    if (RET_FAILED(ret))
    {
        printf("my_socket_init FAILED: %d\n", TINY_RET_CODE(ret));
        return ret;
    }

    // 1. init device configuration
    ret = DeviceConfig_Construct(&config);
    if (RET_FAILED(ret))
    {
        printf("DeviceConfig_Construct FAILED\n");
        return ret;
    }
    DeviceConfig_Initialize(&config, MyConfigurationInitializer, NULL);

    // 2. create AccessoryHost
    host = AccessoryHost_New(&config, OnCharacteristicGet, OnCharacteristicSet, OnIdentify);
    if (host == NULL)
    {
        printf("AccessoryHost_New FAILED\n");
        return TINY_RET_E_NEW;
    }

    // 3. init persistence for accessory
    ret = AccessoryHost_Initialize(host, HapPersistenceImpl_GetInstance());
    if (RET_FAILED(ret))
    {
        printf("AccessoryHost_Initialize FAILED: %d\n", TINY_RET_CODE(ret));
        return ret;
    }

    // 4. run accessory host
    ret = AccessoryHost_Run(host);
    if (RET_FAILED(ret))
    {
        printf("AccessoryHost_Initialize FAILED: %d\n", TINY_RET_CODE(ret));
        return ret;
    }

    // 5. destroy AccessoryHost
    AccessoryHost_Delete(host);

    DeviceConfig_Dispose(&config);

    return TINY_RET_OK;
}

int main(void)
{
    _start();
}
