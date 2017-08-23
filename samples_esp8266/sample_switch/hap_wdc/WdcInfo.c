/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2017-8-5
*
* @file   WdcInfo.c
*
* @remark
*
*/

#include "hap/wdc/WdcInfo.h"
#include "esp_common.h"

// 1024k + 1024k, irom0text.bin = 512k, start sector = (1024k + 512k) / 4k
#define PRIV_PARAM_START_SEC        0x180
#define PRIV_PARAM_SAVE             0

ICACHE_FLASH_ATTR
static uint32_t compute_checksum(WdcInfo *thiz)
{
    uint32_t checksum = 0;
    int i = 0;

    for (i = 0; i < 32; ++i)
    {
        checksum += (uint32_t) (thiz->ssid[i]);
    }

    for (i = 0; i < 32; ++i)
    {
        checksum += (uint32_t) (thiz->password[i]);
    }

    printf("checksum = 0x%x\n", checksum);

    return checksum;
}

ICACHE_FLASH_ATTR
bool WdcInfo_Read(WdcInfo *thiz)
{
    SpiFlashOpResult ret = SPI_FLASH_RESULT_OK;

    memset(thiz, 0, sizeof(WdcInfo));

    ret = spi_flash_read((PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE, (uint32_t *)thiz, sizeof(WdcInfo));
    if (ret != SPI_FLASH_RESULT_OK)
    {
        return false;
    }

    if (thiz->checksum == 0)
    {
        return false;
    }

    return (compute_checksum(thiz) == thiz->checksum);
}

ICACHE_FLASH_ATTR
bool WdcInfo_Write(WdcInfo *thiz)
{
    SpiFlashOpResult ret = SPI_FLASH_RESULT_OK;

    printf("ssid: %s\n", thiz->ssid);
    printf("password: %s\n", thiz->password);

    thiz->checksum = compute_checksum(thiz);

    ret = spi_flash_erase_sector(PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE);
    if (ret != SPI_FLASH_RESULT_OK)
    {
        return false;
    }

    ret = spi_flash_write((PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE, (uint32_t *) thiz, sizeof(WdcInfo));
    if (ret != SPI_FLASH_RESULT_OK)
    {
        return false;
    }

    return true;
}
