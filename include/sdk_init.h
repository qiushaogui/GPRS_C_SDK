#ifndef SDK_INIT_H
#define SDK_INIT_H

#include <string.h>
#include <cs_types.h>
#include <sdk_init.h>
#include <api_inc_fs.h>
#include <api_inc_gpio.h>
#include <api_inc_uart.h>
#include <api_inc_network.h>
#include <api_inc_socket.h>
#include <api_inc_os.h>
#include <api_inc_sim.h>
#include <api_inc_sms.h>
#include <api_inc_time.h>
#include <api_inc_pm.h>
#include <api_inc_call.h>
#include <api_inc_adc.h>
#include <api_inc_mqtt.h>
#include <api_inc_charset.h>




typedef struct T_INTERFACE_VTBL_TAG
{
    //debug
    bool                (*Trace)(uint16_t nIndex,const char* fmt, ...);
    void                (*__assert)(const char* fmt);

    //power
    bool                (*PM_PowerEnable)(Power_Type_t powerType, bool isOn);
    void                (*PM_SleepMode)(bool isSleepMode);
    uint16_t            (*PM_Voltage)(uint8_t* percent);
    void                (*PM_ShutDown)();
    void                (*PM_Restart)();

    /*api_os*/
    void                (*OS_SetUserMainHandle)(HANDLE* UserHandle);
    HANDLE              (*OS_CreateTask)(PTASK_FUNC_T pTaskEntry,PVOID pParameter,PVOID pStackAddr,UINT16 nStackSize
                                            ,UINT8 nPriority,UINT16 nCreationFlags,UINT16 nTimeSlice,PCSTR pTaskName);
    void                (*OS_StartTask)(HANDLE hTask,PVOID pParameter);
    void                (*OS_StopTask)(HANDLE hTask);
    bool                (*OS_DeleteTask)(HANDLE hTask);
    uint32_t            (*OS_SuspendTask)(HANDLE hTask);
    bool                (*OS_ResumeTask)(HANDLE hTask);
    bool                (*OS_Sleep)(uint32_t nMillisecondes);
    bool                (*OS_WaitEvent)(HANDLE hTask,PVOID *pEvent,uint32_t nTimeOut);
    bool                (*OS_SendEvent)(HANDLE hTask,PVOID pEvent,uint32_t nTimeOut,UINT16 nOption);
    bool                (*OS_ResetEventQueue)(HANDLE hTask);
    bool                (*OS_IsEventAvailable)(HANDLE hTask);
    PVOID               (*OS_Malloc)(uint32_t nSize);
    PVOID               (*OS_Realloc)(VOID *ptr,uint32_t nSize);
    bool                (*OS_Free)(PVOID pMemBlock);
    bool                (*OS_GetHeapUsageStatus)(OS_Heap_Status_t *pOsHeapStatus);
    HANDLE              (*OS_CreateSemaphore)(uint32_t nInitCount);
    bool                (*OS_DeleteSemaphore)(HANDLE hSem);
    bool                (*OS_WaitForSemaphore)(HANDLE hSem,uint32_t nTimeOut);
    bool                (*OS_ReleaseSemaphore)(HANDLE hSem);
    HANDLE              (*OS_CreateMutex)(void);
    void                (*OS_DeleteMutex)(HANDLE mutex);
    void                (*OS_LockMutex)(HANDLE mutex);
    void                (*OS_UnlockMutex)(HANDLE mutex);
    bool                (*OS_StartCallbackTimer)(HANDLE hTask, uint32_t ms, OS_CALLBACK_FUNC_T callback, void* param);
    bool                (*OS_StopCallbackTimer)(HANDLE hTask, OS_CALLBACK_FUNC_T callback, void *param);
    uint32_t            (*OS_QueryCallbackTimer)(HANDLE hTask, OS_CALLBACK_FUNC_T callback, void *param);


    /*api_hal_gpio*/
    bool                (*GPIO_Init)(GPIO_config_t config);
    void                (*GPIO_GetConfig)(GPIO_PIN pin,GPIO_config_t* config); 
    bool                (*GPIO_SetLevel)(GPIO_config_t gpioConf, GPIO_LEVEL  level);
    bool                (*GPIO_Set)(GPIO_PIN pin, GPIO_LEVEL  level);
    bool                (*GPIO_GetLevel)(GPIO_config_t gpioConf, GPIO_LEVEL* level);
    bool                (*GPIO_Get)(GPIO_PIN pin, GPIO_LEVEL* level);
    bool                (*GPIO_Close)(GPIO_PIN pin);

    /*api_hal_uart*/
    bool                (*UART_Init)(UART_Port_t uartN, UART_Config_t config);
    uint32_t            (*UART_Write)(UART_Port_t uartN, uint8_t* dataToWrite, uint32_t length);
    uint32_t            (*UART_Read)(UART_Port_t uartN, uint8_t* dataToRead, uint32_t length, uint32_t timeOutMs);
    bool                (*UART_Close)(UART_Port_t uartN);
    
    /*api_gps*/     
    bool                (*GPS_Open)(UART_Callback_t);
    bool                (*GPS_Close)(void);
    
    /*api_network*/
    void                (*Network_SetStatusChangedCallback)(Network_Callback_Func_t callback);
    bool                (*Network_StartAttach)(void);
    bool                (*Network_StartDetach)(void);
    bool                (*Network_StartActive)(Network_PDP_Context_t context);
    bool                (*Network_StartDeactive)(uint8_t contextID);
    
    /*api_socket*/
    int                 (*Socket_TcpipConnect)(TCP_UDP_t tcpOrUdp, const char* ip,uint16_t port);
    int                 (*Socket_TcpipWrite)(int socketFd, uint8_t* data, uint16_t length);
    int                 (*Socket_TcpipRead)( int socketFd, uint8_t* data, uint16_t length);
    bool                (*Socket_TcpipClose)(int socketFd);
    DNS_Status_t        (*DNS_GetHostByName)(const char* domain, char* ip);
    uint32_t            (*DNS_GetHostByNameEX)(const char *hostname, char* ip, DNS_CALLBACK_FUNC_T func, void* param);
    int32_t             (*DNS_GetHostByName2)(const uint8_t* domain, uint8_t* ip);
    
    /*time*/
    int                 (*gettimeofday)(timeval_t *tv, timezone_t *tz);
    void                (*TIME_SetIsAutoUpdateRtcTime)(bool isAutoUpdate);
    bool                (*TIME_IsAutoUpdateRtcTime)();
    bool                (*TIME_SetRtcTime)(RTC_Time_t*);
    bool                (*TIME_GetRtcTIme)(RTC_Time_t*);
    long                (*clock)(void);
    
    /*sms*/
    bool                (*SMS_SetFormat)(SMS_Format_t format, SIM_ID_t simID);
    bool                (*SMS_SetParameter)(SMS_Parameter_t* smsParameter,SIM_ID_t simID);
    bool                (*SMS_SendMessage)(const char* phoneNumber, const uint8_t* message,  uint8_t length, SIM_ID_t simID);
    const char*         (*SMS_GetCharset)(Charset_t);
    bool                (*SMS_Unicode2LocalLanguage)(uint8_t* unicodeIn, uint16_t unicodeLenIn, Charset_t localLanguage, uint8_t** localOut, uint32_t* localLenOut);
    bool                (*SMS_LocalLanguage2Unicode)(uint8_t* localIn, uint16_t localLenIn, Charset_t localLanguage, uint8_t** unicodeOut, uint32_t* unicodeLenOut);
    
    //charset
    const char*         (*GetCharset)(Charset_t index);
    bool                (*Unicode2LocalLanguage)(uint8_t* unicodeIn, uint16_t unicodeLenIn, Charset_t localLanguage, uint8_t** localOut, uint32_t* localLenOut);
    bool                (*LocalLanguage2Unicode)(uint8_t* localIn, uint16_t localLenIn, Charset_t localLanguage, uint8_t** unicodeOut, uint32_t* unicodeLenOut);
    bool                (*Unicode2LocalLanguageBigEndian)(uint8_t* unicodeIn, uint16_t unicodeLenIn, Charset_t localLanguage, uint8_t** localOut, uint32_t* localLenOut);
    bool                (*LocalLanguage2UnicodeBigEndian)(uint8_t* localIn, uint16_t localLenIn, Charset_t localLanguage, uint8_t** unicodeOut, uint32_t* unicodeLenOut);

    /*fs*/
    int32_t             (*API_FS_Open)(PCSTR    fileName,uint32_t operationFlag,uint32_t mode);
    int32_t             (*API_FS_Close)(int32_t fd);
    int32_t             (*API_FS_Read)(int32_t  fd,uint8_t* pBuffer,uint32_t length);
    int32_t             (*API_FS_Write)(int32_t  fd,uint8_t* pBuffer,uint32_t length);
    uint32_t            (*API_FS_Flush)(int32_t fd);
    int32_t             (*API_FS_Create)(PCSTR fileName,uint32_t mode);
    int32_t             (*API_FS_Delete)(PCSTR fileName);
    int64_t             (*API_FS_Seek)( int32_t  fd, int64_t  offset, uint8_t  origin);
    int32_t             (*API_FS_IsEndOfFile)(int32_t fd);
    int32_t             (*API_FS_Rename)(PCSTR oldName,PCSTR newName);
    int32_t             (*API_FS_GetFileName)(int32_t  fd, int32_t  nameBufferLen, uint8_t* fileName);
    int64_t             (*API_FS_GetFileSize)(int32_t fd);
    int64_t             (*API_FS_GetDirSize)(PCSTR fileName, uint64_t* size);
    int32_t             (*API_FS_GetCurDir)(uint32_t size,PSTR pCurDir);
    int32_t             (*API_FS_ChangeDir)(PCSTR pDirName);
    int32_t             (*API_FS_Mkdir)(PCSTR fileName,uint32_t mode);
    int32_t             (*API_FS_Rmdir)(PCSTR fileName);
    int32_t             (*API_FS_GetFSInfo)(PCSTR pDevName, API_FS_INFO* pFsInfo);

    /*info*/
    bool                (*INFO_GetIMEI)(uint8_t* pImei);

    //audio
    void                (*AUDIO_MicOpen)();
    void                (*AUDIO_MicClose)();
    bool                (*AUDIO_MicSetMute)(bool isMute);
    void                (*AUDIO_SpeakerOpen)();
    void                (*AUDIO_SpeakerClose)();
    bool                (*AUDIO_SpeakerSetVolume)(uint8_t volume);

    //call
    bool                (*CALL_Dial)(const char* number);
    bool                (*CALL_HangUp)();
    bool                (*CALL_Answer)();
    bool                (*CALL_DTMF)(char dtmf, CALL_DTMF_Gain_t attenuation, uint8_t duration, uint8_t speakerGain, bool send);

    //adc
    void                (*ADC_Init)(ADC_Config_t adcConfig);
    void                (*ADC_Close)(ADC_Channel_t channel);
    bool                (*ADC_Read)(ADC_Channel_t channel, uint16_t* value, uint16_t* mV);

    //mqtt
    MQTT_Client_t*      (*MQTT_ClientNew)();
    void                (*MQTT_ClientDestroy)(MQTT_Client_t* client);
    MQTT_Error_t        (*MQTT_Connect)(MQTT_Client_t* client, const char* domainOrIp,uint16_t port, 
                                    MQTT_Connection_Callback_t callback, void* arg, const MQTT_Connect_Info_t* connectInfo);
    MQTT_Error_t        (*MQTT_Disconnect)(MQTT_Client_t* client);
    void                (*MQTT_SetInPubCallback)(MQTT_Client_t* client, MQTT_InPub_Callback_t inpubCallback, MQTT_InPub_Data_Callback_t dataInpubCallback, void* arg);
    MQTT_Error_t        (*MQTT_Subscribe)(MQTT_Client_t* client, const char* topic, uint8_t qos, MQTT_Request_Callback_t callback, void* arg);
    MQTT_Error_t        (*MQTT_Unsubscribe)(MQTT_Client_t* client, const char* topic, MQTT_Request_Callback_t cb, void* arg);
    MQTT_Error_t        (*MQTT_Publish)(MQTT_Client_t* client, const char* topic, const void* payload, uint16_t payloadLen, uint8_t dup, uint8_t qos, uint8_t retain,
                                    MQTT_Request_Callback_t callback, void* arg);
    uint8_t             (*MQTT_IsConnected)(MQTT_Client_t* client);

    //sim
    bool                (*SIM_GetICCID)(uint8_t* iccid);


} T_INTERFACE_VTBL_TAG;
extern T_INTERFACE_VTBL_TAG *g_InterfaceVtbl;
#define CSDK_FUNC(name) (g_InterfaceVtbl->name)


#endif