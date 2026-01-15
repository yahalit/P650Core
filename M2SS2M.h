#ifndef M2SS2M_H_DEFINED
#define M2SS2M_H_DEFINED

#include "SystemDefs.h"
/*
 * S2MM2S.h
 *
 *  Created on: 25 June 2025
 *      Author: Yahali
 */


#ifdef INTFC_OWNER
#define INTFC_EXTERN_TAG
#else
#define INTFC_EXTERN_TAG extern
#endif


struct CLimitsBitField
{
    int unsigned CurrentLimit   : 1 ;
    int unsigned I2tCurrentLimit: 1 ;
    int unsigned VoltageLimit   : 1 ;
    int unsigned SpeedCommandLimit : 1 ;
    int unsigned HighPosLimit : 1  ;
    int unsigned LowPosLimit  : 1  ;
    int unsigned Spare : 10 ;
};


union CUserMultiType
{
    short unsigned us[4] ;
    long unsigned ul[2] ;
    float f[2] ;
    long l[2] ;
    long long ll ;
    unsigned long long ull ;
    short s[4] ;
};

struct CUserMessage
{
    long unsigned CobId ;
    short unsigned Index ;
    short unsigned SubIndex ;
    short unsigned Dlc ;
    short unsigned Spare ;
    long  unsigned TimeStamp ;
    union
    {
        short unsigned us[16] ;
        long unsigned ul[8] ;
        float f[8] ;
        long l[8] ;
        long long ll[4] ;
        unsigned long long ull[4] ;
        short s[16] ;
    };
};


struct CObjectResponse
{
    long unsigned index ;
    short unsigned SubIndex ;
    short unsigned ResponseType ; // Type of interpreter response
    short unsigned ResponseCounter ; // Increments every new interpreter response
    short unsigned RequestStamp ; // A copy of the request stamp for which this is response
    union CUserMultiType Payload  ;
};

struct CCommString
{
    short unsigned PutCounter  ;
    short unsigned FetchCounterCopy ;
    unsigned short Status ;
    unsigned short AppHasComm  ; // 1 if the string communication is routed to the app.
    short unsigned Buffer[256] ;
};

struct CAppLimits
{
    double UpperPosLimit ;
    double LowerPosLimit ;
    float  SpeedLimit    ;
    float  CurrentLimit  ;
    long   Spare[8] ;
};

typedef struct {
  /* Time counted from process start */
  real_T SystemTime;

  /* The main encoder sensor */
  int32_T EncoderMain;

  /* The secondary encoder sensor */
  int32_T EncoderSecondary;

  /* Speed of main encoder sensor */
  real32_T EncoderMainSpeed;

  /* Speed of secondary encoder sensor */
  real32_T EncoderSecondarySpeed;

  /* Q-channel current Amp */
  real32_T Iq;

  /* Q-channel current Amp */
  real32_T Id;

  /* SpareElement8 */
  uint32_T SpareElement8;

  /* DC bus voltage V */
  real32_T DcBusVoltage;

  /* Power stage temperature C */
  real32_T PowerStageTemperature;

  /* Motor electrical field angle */
  real32_T FieldAngle;

  /* Motor failure report */
  uint32_T ErrorCode;

  /* Control loop configuration */
  int16_T LoopConfiguration;

  /* ReferenceMode */
  int16_T ReferenceMode;

  /* Motor on report */
  int16_T MotorOn;

  /* Code of Hall sensors */
  int16_T HallCode;

  /* 1 if disabled by STO */
  int16_T STODisable;

  /* Status bit field */
  int16_T StatusBitField;

  /* Confirm Release the drive from SEAL control */
  int16_T ConfirmRelinquishControl;

  /* Drive-sourecd Command to position controller */
  real_T ProfiledPositionCommand;

  /* Drive sources Command to speed controller */
  real_T ProfiledSpeedCommand;

  /* Drive sources Command to current controller */
  real_T ProfiledTorqueCommand;

  /* SpareElement23 */
  uint32_T SpareElement23;

  /* SpareElement24 */
  uint32_T SpareElement24;
} M2SFeedbackBuf_T;



typedef struct {
  /* Maximum position referece */
  real_T MaximumPositionReference;

  /* Minimum position reference */
  real_T MinimumPositionReference;

  /* High position value that causes an exception  */
  real_T HighPositionException;

  /* Low position value that causes an exception  */
  real_T LowPositionException;

  /* Absolute speed limit */
  real32_T AbsoluteSpeedLimit;

  /* Modulo count for position sensor #1 */
  real_T PositionModulo1;

  /* Modulo count for position sensor #2 */
  real_T PositionModulo2;

  /* Speed for overspeed exception */
  real32_T OverSpeed;

  /* Absolute acceleration limit */
  real32_T AbsoluteAccelerationLimit;

  /* Continuous current limit */
  real32_T ContinuousCurrentLimit;

  /* Peak current limit */
  real32_T PeakCurrentLimit;

  /* Peak current duration */
  real32_T PeakCurrentDuration;

  /* Over current that causes an exception */
  real32_T OverCurrent;

  /* Is Sensor modulo: 1 */
  uint16_T IsPosSensorModulo1;

  /* Is Sensor modulo: 2 */
  uint16_T IsPosSensorModulo2;

  /* Profiler sampling time  */
  real32_T Ts;

  /* SpareElement17 */
  uint32_T SpareElement17;

  /* SpareElement18 */
  uint32_T SpareElement18;

  /* SpareElement19 */
  uint32_T SpareElement19;

  /* SpareElement20 */
  uint32_T SpareElement20;

  /* SpareElement21 */
  uint32_T SpareElement21;

  /* SpareElement22 */
  uint32_T SpareElement22;

  /* SpareElement23 */
  uint32_T SpareElement23;

  /* SpareElement24 */
  uint32_T SpareElement24;
} M2SSetupReportBuf_T;


struct CM2S
{
    volatile M2SFeedbackBuf_T FeedbackBuf[NSEAL_AXES] ;
    volatile M2SSetupReportBuf_T SetupReportBuf[NSEAL_AXES] ;
    short  unsigned SensorConfig[8] ; // Sensor configuration
    struct CLimitsBitField LimitsBitField ;
    long unsigned ExceptionCode ; // Exception code
    long  unsigned ProfileStatus ; // TBD profiling status
    struct CObjectResponse InterpreterResponse  ; // Interpreter response
    short  unsigned AppCanId;
    short  unsigned UserMessagePutCounter  ;
    short  unsigned UserMessageOferflow ;
    short  unsigned CommBufferOverflow  ;
    long  long unsigned TimeStampUsec ;
    float ControlTs ;
    long  unsigned CpuClockHz ;
    struct CCommString CommString ; // Communication string, incoming
    struct CUserMessage UserMessage[8] ;
    struct CAppLimits AppLimits ;
    volatile short  unsigned SetupReportUpdateCounter[NSEAL_AXES] ; // Increments whenever any setup data updated 
    volatile short  unsigned FeedbackReportUpdateCounter[NSEAL_AXES] ; // Increments to odd whenever feeback buffer updates updated, and to even when update is done
};

union UM2S_T
{
    long ul[512] ;
    struct CM2S M2S ;
};


typedef struct {
  /* Command to position controller */
  real_T PositionCommand;

  /* Command to speed controller */
  real_T SpeedCommand;

  /* Command to current controller */
  real_T CurrentCommand;

  /* Control loop configuration: see enumerated type VarFeedbackMode */
  int16_T LoopConfiguration;

  /* ReferenceMode: see enumerated type VarReferenceModes */
  int16_T ReferenceMode;

  /* Motor on request */
  int16_T MotorOn;

  /* Failure Reset Request */
  int16_T FailureReset;

  /* Oblige the drive from SEAL control */
  int16_T bSetSealControl;

  /* Flag that the drive should enter quickstop */
  int16_T QuickStop;

  /* SpareElement10 */
  uint32_T SpareElement10;

  /* SpareElement11 */
  uint32_T SpareElement11;

  /* SpareElement12 */
  uint32_T SpareElement12;

  /* SpareElement13 */
  uint32_T SpareElement13;

  /* SpareElement14 */
  uint32_T SpareElement14;

  /* SpareElement15 */
  uint32_T SpareElement15;

  /* SpareElement16 */
  uint32_T SpareElement16;

  /* SpareElement17 */
  uint32_T SpareElement17;

  /* SpareElement18 */
  uint32_T SpareElement18;

  /* SpareElement19 */
  uint32_T SpareElement19;

  /* SpareElement20 */
  uint32_T SpareElement20;

  /* SpareElement21 */
  uint32_T SpareElement21;

  /* SpareElement22 */
  uint32_T SpareElement22;

  /* SpareElement23 */
  uint32_T SpareElement23;

  /* SpareElement24 */
  uint32_T SpareElement24;
} S2MDrvCommandBuf_T;



struct CS2M
{
    S2MDrvCommandBuf_T DrvCommandBuf[NSEAL_AXES] ;
    //SealCanMailBox_T DrvCanOutMail ;
    short unsigned SnatchedBySeal ;
    struct CUserMessage UserMessage[8] ;
    short  unsigned UserMessageFetchCounter  ;
    struct CCommString CommString ; // Communication string, incoming
    short  unsigned ComBufferFetchCounter  ;
 /* Flag that the SEAL uses the UART and the drive should not interpret UART communication */
    short  unsigned  bControlUART;
    short unsigned   bValid ;
    volatile short  unsigned DrvCmdUpdateCounter[NSEAL_AXES] ; // Increments to odd whenever feeback buffer updates updated, and to even when update is done
};


union US2M_T
{
    long ul[512] ;
    struct CS2M S2M;
};

#ifdef INTFC_OWNER
    union UM2S_T UM2S __attribute__((location(0x2014F000))) ; // Start of SRAM_CDAShared 
    union US2M_T US2M __attribute__((location(0x2014F800))) ;
#else
    extern union UM2S_T UM2S ;
    extern union US2M_T US2M ;
#endif

// Other shared definitions
struct CRecorderSig
{
    short unsigned flags ; // !< Define the properties of the number: refer CCmdMode
    long  unsigned * ptr ;
};


#endif 
