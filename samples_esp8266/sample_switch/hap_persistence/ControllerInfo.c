/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2017-8-5
*
* @file   ControllerInfo.c
*
* @remark
*
*/

#include "ControllerInfo.h"
#include "esp_common.h"

// 1024k + 1024k, irom0text.bin = 512k, start sector = (1024k + 512k) / 4k
#define PRIV_PARAM_START_SEC        0x180
#define PRIV_PARAM_SAVE             1

ICACHE_FLASH_ATTR
static uint32_t compute_checksum(ControllerInfo *thiz)
{
    uint32_t checksum = 0;
    int i = 0;

    for (i = 0; i < ENTITY_IDENTIFIER_LENGTH; ++i)
    {
        checksum += (uint32_t) (thiz->id[i]);
    }

    for (i = 0; i < ED25519_PUBLIC_KEY_LENGTH; ++i)
    {
        checksum += (uint32_t) (thiz->ltpk[i]);
    }

    printf("checksum = 0x%x\n", checksum);

    return checksum;
}

ICACHE_FLASH_ATTR
bool ControllerInfo_Read(ControllerInfo *thiz)
{
    SpiFlashOpResult ret = SPI_FLASH_RESULT_OK;

    memset(thiz, 0, sizeof(ControllerInfo));

    ret = spi_flash_read((PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE, (uint32_t *)thiz, sizeof(ControllerInfo));
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
bool ControllerInfo_Write(ControllerInfo *thiz)
{
    SpiFlashOpResult ret = SPI_FLASH_RESULT_OK;

    thiz->checksum = compute_checksum(thiz);

    ret = spi_flash_erase_sector(PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE);
    if (ret != SPI_FLASH_RESULT_OK)
    {
        return false;
    }

    ret = spi_flash_write((PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE, (uint32_t *) thiz, sizeof(ControllerInfo));
    if (ret != SPI_FLASH_RESULT_OK)
    {
        return false;
    }

    return true;
}
