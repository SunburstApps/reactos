#ifndef USBMPORT_H__
#define USBMPORT_H__

#define USBPORT_HCI_MN 0x10000001

/* Tranfer types */

#define USBPORT_TRANSFER_TYPE_ISOCHRONOUS 0
#define USBPORT_TRANSFER_TYPE_CONTROL     1
#define USBPORT_TRANSFER_TYPE_BULK        2
#define USBPORT_TRANSFER_TYPE_INTERRUPT   3

/* Endpoint states */

#define USBPORT_ENDPOINT_UNKNOWN 0
#define USBPORT_ENDPOINT_PAUSED 2
#define USBPORT_ENDPOINT_ACTIVE 3
#define USBPORT_ENDPOINT_CLOSED 4
#define USBPORT_ENDPOINT_NOT_HANDLED 5

/* Endpoint status */

#define USBPORT_ENDPOINT_RUN     0
#define USBPORT_ENDPOINT_HALT    1
#define USBPORT_ENDPOINT_CONTROL 4

/* Types of resources */

#define USBPORT_RESOURCES_PORT      1
#define USBPORT_RESOURCES_INTERRUPT 2
#define USBPORT_RESOURCES_MEMORY    4

typedef struct _USBPORT_RESOURCES {
  ULONG TypesResources; // 1 | 2 | 4  (Port | Interrupt | Memory)
  ULONG HcFlavor;
  ULONG InterruptVector;
  KIRQL InterruptLevel;
  UCHAR Padded1[3];
  KAFFINITY InterruptAffinity;
  BOOLEAN ShareVector;
  UCHAR Padded2[3];
  KINTERRUPT_MODE InterruptMode;
  ULONG Reserved;
  PVOID ResourceBase;
  SIZE_T IoSpaceLength;
  PVOID StartVA;
  PVOID StartPA;
  UCHAR LegacySupport;
  BOOLEAN IsChirpHandled;
  UCHAR Reserved2;
  UCHAR Reserved3;
} USBPORT_RESOURCES, *PUSBPORT_RESOURCES;

C_ASSERT(sizeof(USBPORT_RESOURCES) == 52);

typedef ULONG MPSTATUS; // Miniport status
typedef ULONG RHSTATUS; // Roothub status

#define MP_STATUS_SUCCESS       0
#define MP_STATUS_FAILURE       1
#define MP_STATUS_NO_RESOURCES  2
#define MP_STATUS_NO_BANDWIDTH  3
#define MP_STATUS_ERROR         4
#define MP_STATUS_NOT_SUPPORTED 6

#define RH_STATUS_SUCCESS 0
 
/* Miniport */

typedef MPSTATUS
(NTAPI *PHCI_OPEN_ENDPOINT)(
  PVOID,
  PVOID,
  PVOID);

typedef MPSTATUS
(NTAPI *PHCI_REOPEN_ENDPOINT)(
  PVOID,
  PVOID,
  PVOID);

typedef VOID
(NTAPI *PHCI_QUERY_ENDPOINT_REQUIREMENTS)(
  PVOID,
  PVOID,
  PULONG);

typedef VOID
(NTAPI *PHCI_CLOSE_ENDPOINT)(
  PVOID,
  PVOID,
  BOOLEAN);

typedef MPSTATUS
(NTAPI *PHCI_START_CONTROLLER)(
  PVOID,
  PUSBPORT_RESOURCES);

typedef VOID
(NTAPI *PHCI_STOP_CONTROLLER)(
  PVOID,
  BOOLEAN);

typedef VOID
(NTAPI *PHCI_SUSPEND_CONTROLLER)(PVOID);

typedef MPSTATUS
(NTAPI *PHCI_RESUME_CONTROLLER)(PVOID);

typedef BOOLEAN
(NTAPI *PHCI_INTERRUPT_SERVICE)(PVOID);

typedef VOID
(NTAPI *PHCI_INTERRUPT_DPC)(
  PVOID,
  BOOLEAN);

typedef MPSTATUS
(NTAPI *PHCI_SUBMIT_TRANSFER)(
  PVOID,
  PVOID,
  PVOID,
  PVOID,
  PVOID);

typedef MPSTATUS
(NTAPI *PHCI_SUBMIT_ISO_TRANSFER)(
  PVOID,
  PVOID,
  PVOID,
  PVOID,
  PVOID);

typedef VOID
(NTAPI *PHCI_ABORT_TRANSFER)(
  PVOID,
  PVOID,
  PVOID,
  PULONG);

typedef ULONG
(NTAPI *PHCI_GET_ENDPOINT_STATE)(
  PVOID,
  PVOID);

typedef VOID
(NTAPI *PHCI_SET_ENDPOINT_STATE)(
  PVOID,
  PVOID,
  ULONG);

typedef VOID
(NTAPI *PHCI_POLL_ENDPOINT)(
  PVOID,
  PVOID);

typedef VOID
(NTAPI *PHCI_CHECK_CONTROLLER)(PVOID);

typedef ULONG
(NTAPI *PHCI_GET_32BIT_FRAME_NUMBER)(PVOID);

typedef VOID
(NTAPI *PHCI_INTERRUPT_NEXT_SOF)(PVOID);

typedef VOID
(NTAPI *PHCI_ENABLE_INTERRUPTS)(PVOID);

typedef VOID
(NTAPI *PHCI_DISABLE_INTERRUPTS)(PVOID);

typedef VOID
(NTAPI *PHCI_POLL_CONTROLLER)(PVOID);

typedef VOID
(NTAPI *PHCI_SET_ENDPOINT_DATA_TOGGLE)(
  PVOID,
  PVOID,
  ULONG);

typedef ULONG
(NTAPI *PHCI_GET_ENDPOINT_STATUS)(
  PVOID,
  PVOID);

typedef VOID
(NTAPI *PHCI_SET_ENDPOINT_STATUS)(
  PVOID,
  PVOID,
  ULONG);

typedef VOID
(NTAPI *PHCI_RESET_CONTROLLER)(PVOID);

/* Roothub */

typedef VOID
(NTAPI *PHCI_RH_GET_ROOT_HUB_DATA)(
  PVOID,
  PVOID);

typedef MPSTATUS
(NTAPI *PHCI_RH_GET_STATUS)(
  PVOID,
  PUSHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_GET_PORT_STATUS)(
  PVOID,
  USHORT,
  PULONG);

typedef MPSTATUS
(NTAPI *PHCI_RH_GET_HUB_STATUS)(
  PVOID,
  PULONG);

typedef MPSTATUS
(NTAPI *PHCI_RH_SET_FEATURE_PORT_RESET)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_SET_FEATURE_PORT_POWER)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_SET_FEATURE_PORT_ENABLE)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_SET_FEATURE_PORT_SUSPEND)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_ENABLE)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_POWER)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_SUSPEND)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_ENABLE_CHANGE)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_CONNECT_CHANGE)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_RESET_CHANGE)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_SUSPEND_CHANGE)(
  PVOID,
  USHORT);

typedef MPSTATUS
(NTAPI *PHCI_RH_CLEAR_FEATURE_PORT_OVERCURRENT_CHANGE)(
  PVOID,
  USHORT);

typedef VOID
(NTAPI *PHCI_RH_DISABLE_IRQ)(PVOID);

typedef VOID
(NTAPI *PHCI_RH_ENABLE_IRQ)(PVOID);

/* Miniport ioctl */

typedef MPSTATUS
(NTAPI *PHCI_START_SEND_ONE_PACKET)(
  PVOID,
  PVOID,
  PVOID,
  PULONG,
  PVOID,
  PVOID,
  ULONG,
  USBD_STATUS *);

typedef MPSTATUS
(NTAPI *PHCI_END_SEND_ONE_PACKET)(
  PVOID,
  PVOID,
  PVOID,
  PULONG,
  PVOID,
  PVOID,
  ULONG,
  USBD_STATUS *);

typedef MPSTATUS
(NTAPI *PHCI_PASS_THRU)(
  PVOID,
  PVOID,
  ULONG,
  PVOID);

/* Port */

typedef ULONG
(NTAPI *PUSBPORT_DBG_PRINT)(
  PVOID,
  ULONG,
  PCH,
  ULONG,
  ULONG,
  ULONG,
  ULONG,
  ULONG,
  ULONG);

typedef ULONG
(NTAPI *PUSBPORT_TEST_DEBUG_BREAK)(PVOID);

typedef ULONG
(NTAPI *PUSBPORT_ASSERT_FAILURE)(
  PVOID,
  PVOID,
  PVOID,
  ULONG,
  PCHAR);

typedef MPSTATUS
(NTAPI *PUSBPORT_GET_MINIPORT_REGISTRY_KEY_VALUE)(
  PVOID,
  ULONG,
  PCWSTR,
  SIZE_T,
  PVOID,
  SIZE_T);

typedef ULONG
(NTAPI *PUSBPORT_INVALIDATE_ROOT_HUB)(PVOID);

typedef ULONG
(NTAPI *PUSBPORT_INVALIDATE_ENDPOINT)(
  PVOID,
  PVOID);

typedef ULONG
(NTAPI *PUSBPORT_COMPLETE_TRANSFER)(
  PVOID,
  PVOID,
  PVOID,
  USBD_STATUS,
  SIZE_T);

typedef ULONG
(NTAPI *PUSBPORT_COMPLETE_ISO_TRANSFER)(
  PVOID,
  PVOID,
  PVOID,
  ULONG);

typedef ULONG
(NTAPI *PUSBPORT_LOG_ENTRY)(
  PVOID,
  PVOID,
  PVOID,
  ULONG,
  ULONG,
  ULONG);

typedef PVOID
(NTAPI *PUSBPORT_GET_MAPPED_VIRTUAL_ADDRESS)(
  PVOID,
  PVOID,
  PVOID);

typedef ULONG
(NTAPI *PUSBPORT_REQUEST_ASYNC_CALLBACK)(
  PVOID,
  ULONG,
  PVOID,
  SIZE_T,
  ULONG);

typedef MPSTATUS
(NTAPI *PUSBPORT_READ_WRITE_CONFIG_SPACE)(
  PVOID,
  BOOLEAN,
  PVOID,
  ULONG,
  ULONG);

typedef NTSTATUS
(NTAPI *PUSBPORT_WAIT)(
  PVOID,
  ULONG); 

typedef ULONG
(NTAPI *PUSBPORT_INVALIDATE_CONTROLLER)(
  PVOID,
  ULONG); 

typedef VOID
(NTAPI *PUSBPORT_BUG_CHECK)(PVOID);

typedef ULONG
(NTAPI *PUSBPORT_NOTIFY_DOUBLE_BUFFER)(
  PVOID,
  PVOID,
  PVOID,
  SIZE_T);

/* Miniport */

typedef VOID
(NTAPI *PHCI_REBALANCE_ENDPOINT)(
  PVOID,
  PVOID,
  PVOID);

typedef VOID
(NTAPI *PHCI_FLUSH_INTERRUPTS)(PVOID);

typedef MPSTATUS
(NTAPI *PHCI_RH_CHIRP_ROOT_PORT)(
  PVOID,
  USHORT);

typedef VOID
(NTAPI *PHCI_TAKE_PORT_CONTROL)(PVOID);

#define USB_MINIPORT_VERSION_OHCI 0x01
#define USB_MINIPORT_VERSION_UHCI 0x02
#define USB_MINIPORT_VERSION_EHCI 0x03
#define USB_MINIPORT_VERSION_XHCI 0x04 //miniport version for xhci 

#define USB_MINIPORT_FLAGS_INTERRUPT    0x0001
#define USB_MINIPORT_FLAGS_PORT_IO      0x0002
#define USB_MINIPORT_FLAGS_MEMORY_IO    0x0004
#define USB_MINIPORT_FLAGS_USB2         0x0010
#define USB_MINIPORT_FLAGS_DISABLE_SS   0x0020
#define USB_MINIPORT_FLAGS_POLLING      0x0080
#define USB_MINIPORT_FLAGS_NO_DMA       0x0100
#define USB_MINIPORT_FLAGS_WAKE_SUPPORT 0x0200

typedef struct _USBPORT_REGISTRATION_PACKET {
  ULONG MiniPortVersion;
  ULONG MiniPortFlags;
  ULONG MiniPortBusBandwidth;
  ULONG Reserved1;
  SIZE_T MiniPortExtensionSize;
  SIZE_T MiniPortEndpointSize;
  SIZE_T MiniPortTransferSize;
  ULONG Reserved2;
  ULONG Reserved3;
  SIZE_T MiniPortResourcesSize;

  /* Miniport */

  PHCI_OPEN_ENDPOINT OpenEndpoint;
  PHCI_REOPEN_ENDPOINT ReopenEndpoint;
  PHCI_QUERY_ENDPOINT_REQUIREMENTS QueryEndpointRequirements;
  PHCI_CLOSE_ENDPOINT CloseEndpoint;
  PHCI_START_CONTROLLER StartController;
  PHCI_STOP_CONTROLLER StopController;
  PHCI_SUSPEND_CONTROLLER SuspendController;
  PHCI_RESUME_CONTROLLER ResumeController;
  PHCI_INTERRUPT_SERVICE InterruptService;
  PHCI_INTERRUPT_DPC InterruptDpc;
  PHCI_SUBMIT_TRANSFER SubmitTransfer;
  PHCI_SUBMIT_ISO_TRANSFER SubmitIsoTransfer;
  PHCI_ABORT_TRANSFER AbortTransfer;
  PHCI_GET_ENDPOINT_STATE GetEndpointState;
  PHCI_SET_ENDPOINT_STATE SetEndpointState;
  PHCI_POLL_ENDPOINT PollEndpoint;
  PHCI_CHECK_CONTROLLER CheckController;
  PHCI_GET_32BIT_FRAME_NUMBER Get32BitFrameNumber;
  PHCI_INTERRUPT_NEXT_SOF InterruptNextSOF;
  PHCI_ENABLE_INTERRUPTS EnableInterrupts;
  PHCI_DISABLE_INTERRUPTS DisableInterrupts;
  PHCI_POLL_CONTROLLER PollController;
  PHCI_SET_ENDPOINT_DATA_TOGGLE SetEndpointDataToggle;
  PHCI_GET_ENDPOINT_STATUS GetEndpointStatus;
  PHCI_SET_ENDPOINT_STATUS SetEndpointStatus;
  PHCI_RESET_CONTROLLER ResetController;

  /* Roothub */

  PHCI_RH_GET_ROOT_HUB_DATA RH_GetRootHubData;
  PHCI_RH_GET_STATUS RH_GetStatus;
  PHCI_RH_GET_PORT_STATUS RH_GetPortStatus;
  PHCI_RH_GET_HUB_STATUS RH_GetHubStatus;
  PHCI_RH_SET_FEATURE_PORT_RESET RH_SetFeaturePortReset;
  PHCI_RH_SET_FEATURE_PORT_POWER RH_SetFeaturePortPower;
  PHCI_RH_SET_FEATURE_PORT_ENABLE RH_SetFeaturePortEnable;
  PHCI_RH_SET_FEATURE_PORT_SUSPEND RH_SetFeaturePortSuspend;
  PHCI_RH_CLEAR_FEATURE_PORT_ENABLE RH_ClearFeaturePortEnable;
  PHCI_RH_CLEAR_FEATURE_PORT_POWER RH_ClearFeaturePortPower;
  PHCI_RH_CLEAR_FEATURE_PORT_SUSPEND RH_ClearFeaturePortSuspend;
  PHCI_RH_CLEAR_FEATURE_PORT_ENABLE_CHANGE RH_ClearFeaturePortEnableChange;
  PHCI_RH_CLEAR_FEATURE_PORT_CONNECT_CHANGE RH_ClearFeaturePortConnectChange;
  PHCI_RH_CLEAR_FEATURE_PORT_RESET_CHANGE RH_ClearFeaturePortResetChange;
  PHCI_RH_CLEAR_FEATURE_PORT_SUSPEND_CHANGE RH_ClearFeaturePortSuspendChange;
  PHCI_RH_CLEAR_FEATURE_PORT_OVERCURRENT_CHANGE RH_ClearFeaturePortOvercurrentChange;
  PHCI_RH_DISABLE_IRQ RH_DisableIrq;
  PHCI_RH_ENABLE_IRQ RH_EnableIrq;

  /* Miniport ioctl */

  PHCI_START_SEND_ONE_PACKET StartSendOnePacket;
  PHCI_END_SEND_ONE_PACKET EndSendOnePacket;
  PHCI_PASS_THRU PassThru;

  /* Port */

  PUSBPORT_DBG_PRINT UsbPortDbgPrint;
  PUSBPORT_TEST_DEBUG_BREAK UsbPortTestDebugBreak;
  PUSBPORT_ASSERT_FAILURE UsbPortAssertFailure;
  PUSBPORT_GET_MINIPORT_REGISTRY_KEY_VALUE UsbPortGetMiniportRegistryKeyValue;
  PUSBPORT_INVALIDATE_ROOT_HUB UsbPortInvalidateRootHub;
  PUSBPORT_INVALIDATE_ENDPOINT UsbPortInvalidateEndpoint;
  PUSBPORT_COMPLETE_TRANSFER UsbPortCompleteTransfer;
  PUSBPORT_COMPLETE_ISO_TRANSFER UsbPortCompleteIsoTransfer;
  PUSBPORT_LOG_ENTRY UsbPortLogEntry;
  PUSBPORT_GET_MAPPED_VIRTUAL_ADDRESS UsbPortGetMappedVirtualAddress;
  PUSBPORT_REQUEST_ASYNC_CALLBACK UsbPortRequestAsyncCallback;
  PUSBPORT_READ_WRITE_CONFIG_SPACE UsbPortReadWriteConfigSpace;
  PUSBPORT_WAIT UsbPortWait;
  PUSBPORT_INVALIDATE_CONTROLLER UsbPortInvalidateController;
  PUSBPORT_BUG_CHECK UsbPortBugCheck;
  PUSBPORT_NOTIFY_DOUBLE_BUFFER UsbPortNotifyDoubleBuffer;

  /* Miniport */

  PHCI_REBALANCE_ENDPOINT RebalanceEndpoint;
  PHCI_FLUSH_INTERRUPTS FlushInterrupts;
  PHCI_RH_CHIRP_ROOT_PORT RH_ChirpRootPort;
  PHCI_TAKE_PORT_CONTROL TakePortControl;
  ULONG Reserved4;
  ULONG Reserved5;
} USBPORT_REGISTRATION_PACKET, *PUSBPORT_REGISTRATION_PACKET;

typedef struct _USBPORT_MINIPORT_INTERFACE {
  PDRIVER_OBJECT DriverObject;
  LIST_ENTRY DriverLink;
  PDRIVER_UNLOAD DriverUnload;
  ULONG Version;
  USBPORT_REGISTRATION_PACKET Packet;
} USBPORT_MINIPORT_INTERFACE, *PUSBPORT_MINIPORT_INTERFACE;

C_ASSERT(sizeof(USBPORT_MINIPORT_INTERFACE) == 336);

typedef struct _USBPORT_ENDPOINT_PROPERTIES {
  USHORT DeviceAddress;
  USHORT EndpointAddress;
  USHORT TotalMaxPacketSize; // TransactionPerMicroframe * MaxPacketSize
  UCHAR Period;
  UCHAR Reserved1;
  USB_DEVICE_SPEED DeviceSpeed;
  ULONG UsbBandwidth;
  ULONG ScheduleOffset;
  ULONG TransferType;
  ULONG Direction;
  ULONG BufferVA;
  ULONG BufferPA;
  ULONG BufferLength;
  ULONG Reserved3;
  ULONG MaxTransferSize;
  USHORT HubAddr;
  USHORT PortNumber;
  UCHAR InterruptScheduleMask;
  UCHAR SplitCompletionMask;
  UCHAR TransactionPerMicroframe; // 1 + additional transactions. Total: from 1 to 3)
  UCHAR Reserved4;
  ULONG MaxPacketSize;
  ULONG Reserved6;
} USBPORT_ENDPOINT_PROPERTIES, *PUSBPORT_ENDPOINT_PROPERTIES;

C_ASSERT(sizeof(USBPORT_ENDPOINT_PROPERTIES) == 64);

typedef struct _USBPORT_SCATTER_GATHER_ELEMENT {
  PHYSICAL_ADDRESS SgPhysicalAddress;
  ULONG Reserved1;
  ULONG SgTransferLength;
  ULONG SgOffset;
  ULONG Reserved2;
} USBPORT_SCATTER_GATHER_ELEMENT, *PUSBPORT_SCATTER_GATHER_ELEMENT;

C_ASSERT(sizeof(USBPORT_SCATTER_GATHER_ELEMENT) == 24);

typedef struct _USBPORT_SCATTER_GATHER_LIST {
  ULONG Flags;
  ULONG_PTR CurrentVa;
  PVOID MappedSystemVa;
  ULONG SgElementCount;
  USBPORT_SCATTER_GATHER_ELEMENT SgElement[1];
} USBPORT_SCATTER_GATHER_LIST, *PUSBPORT_SCATTER_GATHER_LIST;

C_ASSERT(sizeof(USBPORT_SCATTER_GATHER_LIST) == 40);

typedef struct _USBPORT_TRANSFER_PARAMETERS {
  ULONG TransferFlags;
  ULONG TransferBufferLength;
  ULONG TransferCounter;
  ULONG Reserved1;
  ULONG Reserved2;
  USB_DEFAULT_PIPE_SETUP_PACKET SetupPacket;
} USBPORT_TRANSFER_PARAMETERS, *PUSBPORT_TRANSFER_PARAMETERS;

C_ASSERT(sizeof(USBPORT_TRANSFER_PARAMETERS) == 28);

typedef struct _USBPORT_ROOT_HUB_DATA {
  ULONG NumberOfPorts;
  ULONG HubCharacteristics;
  ULONG PowerOnToPowerGood;
  ULONG HubControlCurrent;
} USBPORT_ROOT_HUB_DATA, *PUSBPORT_ROOT_HUB_DATA;

C_ASSERT(sizeof(USBPORT_ROOT_HUB_DATA) == 16);

/* Hub port status and port status change bits.
   See USB 2.0 spec Table 11-19 and Table 11-20.
*/

typedef union _USB_PORT_STATUS {
  struct {
    USHORT ConnectStatus          : 1; // Current Connect Status
    USHORT EnableStatus           : 1; // Port Enabled/Disabled
    USHORT SuspendStatus          : 1;
    USHORT OverCurrent            : 1;
    USHORT ResetStatus            : 1;
    USHORT Reserved1              : 3;
    USHORT PowerStatus            : 1;
    USHORT LsDeviceAttached       : 1; // Low-Speed Device Attached
    USHORT HsDeviceAttached       : 1; // High-speed Device Attached
    USHORT TestMode               : 1; // Port Test Mode
    USHORT IndicatorControl       : 1; // Port Indicator Control
    USHORT Reserved2              : 3;
  };
  USHORT AsUSHORT;
} USB_PORT_STATUS;

typedef union _USB_PORT_STATUS_CHANGE {
  struct {
    USHORT ConnectStatusChange    : 1;
    USHORT EnableStatusChange     : 1;
    USHORT SuspendStatusChange    : 1;
    USHORT OverCurrentChange      : 1;
    USHORT ResetStatusChange      : 1;
    USHORT Reserved3              : 3;
    USHORT PowerStatusChange      : 1;
    USHORT LsDeviceAttachedChange : 1;
    USHORT HsDeviceAttachedChange : 1;
    USHORT TestModeChange         : 1;
    USHORT IndicatorControlChange : 1;
    USHORT Reserved4              : 3;
  };
  USHORT AsUSHORT;
} USB_PORT_STATUS_CHANGE;

typedef union _USBHUB_PORT_STATUS {
struct {
    USB_PORT_STATUS UsbPortStatus;
    USB_PORT_STATUS_CHANGE UsbPortStatusChange;
  };
  ULONG AsULONG;
} USBHUB_PORT_STATUS, *PUSBHUB_PORT_STATUS;

/* Hub status & hub status change bits.
   See USB 2.0 spec Table 11-19 and Table 11-20.
*/

#define HUB_STATUS_LOCAL_POWER        0x00000001
#define HUB_STATUS_OVERCURRENT        0x00000002
#define HUB_STATUS_CHANGE_LOCAL_POWER 0x00010000
#define HUB_STATUS_CHANGE_OVERCURRENT 0x00020000

/* Additional USB Class Codes from USB.org */

#define USBC_DEVICE_CLASS_CDC_DATA              0x0A
#define USBC_DEVICE_CLASS_SMART_CARD            0x0B
#define USBC_DEVICE_CLASS_CONTENT_SECURITY      0x0D
#define USBC_DEVICE_CLASS_VIDEO                 0x0E
#define USBC_DEVICE_CLASS_PERSONAL_HEALTHCARE   0x0F
#define USBC_DEVICE_CLASS_AUDIO_VIDEO           0x10
#define USBC_DEVICE_CLASS_BILLBOARD             0x11
#define USBC_DEVICE_CLASS_TYPE_C_BRIDGE         0x12
#define USBC_DEVICE_CLASS_WIRELESS_Diagnostic   0xDC
#define USBC_DEVICE_CLASS_WIRELESS_CONTROLLER   0xE0
#define USBC_DEVICE_CLASS_MISCELLANEOUS         0xEF
#define USBC_DEVICE_CLASS_APPLICATION_SPECIFIC  0xFE

ULONG
NTAPI
USBPORT_GetHciMn(VOID);

NTSTATUS
NTAPI
USBPORT_RegisterUSBPortDriver(
  IN PDRIVER_OBJECT DriverObject,
  IN ULONG Version,
  IN PUSBPORT_REGISTRATION_PACKET RegistrationPacket);

#endif /* USBMPORT_H__ */
