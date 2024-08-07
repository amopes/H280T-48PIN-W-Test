/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_common_fifo
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.9.4
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#ifndef _common_fifo_h_
#define _common_fifo_h_

#include "stdio.h"
#include "usart.h"
#include "freertos.h"
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "string.h"
#include "stdlib.h"


#define int8	int8_t
#define int16	int16_t
#define int32	int32_t
#define int64	int64_t

#define uint8	uint8_t
#define uint16	uint16_t
#define uint32	uint32_t
#define uint64	uint64_t


typedef enum
{
    FIFO_SUCCESS,

    FIFO_WRITE_UNDO,
    FIFO_CLEAR_UNDO,
    FIFO_BUFFER_NULL,
    FIFO_SPACE_NO_ENOUGH,
    FIFO_DATA_NO_ENOUGH,
}fifo_state_enum;

typedef enum
{
    FIFO_IDLE       = 0x00,
    FIFO_CLEAR      = 0x01,
    FIFO_WRITE      = 0x02,
    FIFO_READ       = 0x04,
}fifo_execution_enum;

typedef enum
{
    FIFO_READ_AND_CLEAN,
    FIFO_READ_ONLY,
}fifo_operation_enum;

typedef enum
{
    FIFO_DATA_8BIT,
    FIFO_DATA_16BIT,
    FIFO_DATA_32BIT,
}fifo_data_type_enum;

typedef struct
{
    uint8               execution;                                              // ִ�в���
    fifo_data_type_enum type;                                                   // ��������
    void               *buffer;                                                 // ����ָ��
    uint32              head;                                                   // ����ͷָ�� ����ָ��յĻ���
    uint32              end;                                                    // ����βָ�� ����ָ��ǿջ��棨����ȫ�ճ��⣩
    uint32              size;                                                   // ����ʣ���С
    uint32              max;                                                    // �����ܴ�С
}fifo_struct;

fifo_state_enum fifo_clear              (fifo_struct *fifo);
uint32          fifo_used               (fifo_struct *fifo);

fifo_state_enum fifo_write_element      (fifo_struct *fifo, uint32 dat);
fifo_state_enum fifo_write_buffer       (fifo_struct *fifo, void *dat, uint32 length);
fifo_state_enum fifo_read_element       (fifo_struct *fifo, void *dat, fifo_operation_enum flag);
fifo_state_enum fifo_read_buffer        (fifo_struct *fifo, void *dat, uint32 *length, fifo_operation_enum flag);
fifo_state_enum fifo_read_tail_buffer   (fifo_struct *fifo, void *dat, uint32 *length, fifo_operation_enum flag);

fifo_state_enum fifo_init               (fifo_struct *fifo, fifo_data_type_enum type, void *buffer_addr, uint32 size);

#endif
