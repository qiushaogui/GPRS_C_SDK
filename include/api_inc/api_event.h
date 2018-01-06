

#ifndef __API_EVENT_H_
#define __API_EVENT_H_

#include <cs_types.h>

typedef enum{
    //system
    API_EVENT_ID_POWER_ON = 0                      ,   //param1: shows power on cause:
    API_EVENT_ID_SYSTEM_READY                      ,

    //SIM card
    API_EVENT_ID_NO_SIMCARD                        ,   //param1: card id
    API_EVENT_ID_SIMCARD_DROP                      ,   //param1: card id
    //signal
    API_EVENT_ID_SINGNAL_QUALITY                   ,   //param1: CSQ(0~31,99(unknown)), param2:RXQUAL(0~7,99(unknown))  (RSSI = CSQ*2-113)
    //network
    API_EVENT_ID_NETWORK_REGISTERED_HOME           ,
    API_EVENT_ID_NETWORK_REGISTERED_ROAMING        ,
    API_EVENT_ID_NETWORK_REGISTER_SEARCHING        ,
    API_EVENT_ID_NETWORK_REGISTER_DENIED           ,
    API_EVENT_ID_NETWORK_REGISTER_NO               ,
    API_EVENT_ID_NETWORK_DETACHED                  ,
    API_EVENT_ID_NETWORK_ATTACH_FAILED             ,
    API_EVENT_ID_NETWORK_ATTACHED                  ,
    API_EVENT_ID_NETWORK_DEACTIVED                 ,
    API_EVENT_ID_NETWORK_ACTIVATE_FAILED           ,
    API_EVENT_ID_NETWORK_ACTIVATED                 ,
    API_EVENT_ID_NETWORK_GOT_TIME                  ,  //pParam1: RTC_Time_t*

    //DNS
    API_EVENT_ID_DNS_SUCCESS                       ,   //param1:IP address(uint32_t), pPram1:domain(uint8_t*)
    API_EVENT_ID_DNS_ERROR                         ,


    //socket
    API_EVENT_ID_SOCKET_CONNECTED                  ,   //param1: socketFd
    API_EVENT_ID_SOCKET_CLOSED                     ,   //param1: socketFd
    API_EVENT_ID_SOCKET_SENT                       ,   //param1: socketFd
    API_EVENT_ID_SOCKET_RECEIVED                   ,   //param1: socketFd, param2: length of data received
    API_EVENT_ID_SOCKET_ERROR                      ,   //param1: socketFd, param2: error cause(API_Socket_Error_t)

    //SMS
    API_EVENT_ID_SMS_SENT                          ,
    API_EVENT_ID_SMS_RECEIVED                      ,  //param1:SMS_Encode_Type_t, param2:message content length, pParam1:message header info, pParam2:message content
    API_EVENT_ID_SMS_ERROR                         ,  //param1:SMS_Error_t cause

    //uart
    API_EVENT_ID_UART_RECEIVED                     ,   //param1: uart number, param2: length, pParam1: data

    //GPS
    API_EVENT_ID_GPS_UART_RECEIVED                 ,   //param1: length, pParam1: data

    //CALL
    API_EVENT_ID_CALL_DIAL                         ,   //param1: isSuccess, param2:error code(CALL_Error_t)
    API_EVENT_ID_CALL_HANGUP                       ,   //param1: is remote release call, param2:error code(CALL_Error_t)
    API_EVENT_ID_CALL_INCOMING                     ,   //param1: number type, pParam1:number
    API_EVENT_ID_CALL_ANSWER                       ,  
    API_EVENT_ID_CALL_DTMF                         ,  //param1: key
    
    //error
    API_EVENT_ID_MALLOC_FAILED                     ,
    API_EVENT_ID_MAX
}API_Event_ID_t;

typedef struct {
    API_Event_ID_t id;
    uint32_t       param1 ;
    uint32_t       param2 ;
    uint8_t*       pParam1;
    uint8_t*       pParam2;
}API_Event_t;



#endif


