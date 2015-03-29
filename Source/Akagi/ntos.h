/************************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2015, translated from Microsoft sources/debugger
*
*  TITLE:       NTOS.H
*
*  VERSION:     1.12
*
*  DATE:        16 Mar 2015
*
*  Common header file for the ntos API functions and definitions.
*
*  ONLY program required types and definitions listed.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
************************************************************************************/

#pragma comment(lib, "ntdll.lib")

#pragma warning(disable: 4214) // nonstandard extension used : bit field types other than int

#define IN_REGION(x, Base, Size) (((ULONG_PTR)x >= (ULONG_PTR)Base) && ((ULONG_PTR)x <= (ULONG_PTR)Base + (ULONG_PTR)Size))

#define ALIGN_DOWN(count,size) \
            ((ULONG_PTR)(count) & ~((ULONG_PTR)(size) - 1))

#define ALIGN_UP(count,size) \
            (ALIGN_DOWN( (ULONG_PTR)(count)+(ULONG_PTR)(size)-1, (ULONG_PTR)(size) ))

//Access Rights

#define CALLBACK_MODIFY_STATE    0x0001
#define CALLBACK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|CALLBACK_MODIFY_STATE )

#define DEBUG_READ_EVENT        (0x0001)
#define DEBUG_PROCESS_ASSIGN    (0x0002)
#define DEBUG_SET_INFORMATION   (0x0004)
#define DEBUG_QUERY_INFORMATION (0x0008)
#define DEBUG_ALL_ACCESS     (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|DEBUG_READ_EVENT|DEBUG_PROCESS_ASSIGN|\
                              DEBUG_SET_INFORMATION|DEBUG_QUERY_INFORMATION)

#define DIRECTORY_QUERY                 (0x0001)
#define DIRECTORY_TRAVERSE              (0x0002)
#define DIRECTORY_CREATE_OBJECT         (0x0004)
#define DIRECTORY_CREATE_SUBDIRECTORY   (0x0008)
#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)

#define EVENT_QUERY_STATE       0x0001
#define EVENT_MODIFY_STATE      0x0002  
#define EVENT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3) 

#define EVENT_PAIR_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE)

#define IO_COMPLETION_QUERY_STATE   0x0001
#define IO_COMPLETION_MODIFY_STATE  0x0002  
#define IO_COMPLETION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3) 

#define KEYEDEVENT_WAIT 0x0001
#define KEYEDEVENT_WAKE 0x0002
#define KEYEDEVENT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | KEYEDEVENT_WAIT | KEYEDEVENT_WAKE)

#define MUTANT_QUERY_STATE      0x0001
#define MUTANT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|MUTANT_QUERY_STATE)

#define PORT_CONNECT (0x0001)
#define PORT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1)

#define PROFILE_CONTROL (0x0001)
#define PROFILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | PROFILE_CONTROL)

#define SEMAPHORE_QUERY_STATE       0x0001
#define SEMAPHORE_MODIFY_STATE      0x0002 
#define SEMAPHORE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

#define SYMBOLIC_LINK_QUERY (0x0001)
#define SYMBOLIC_LINK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

#define THREAD_ALERT	(0x0004)

#define WORKER_FACTORY_RELEASE_WORKER 0x0001
#define WORKER_FACTORY_WAIT 0x0002
#define WORKER_FACTORY_SET_INFORMATION 0x0004
#define WORKER_FACTORY_QUERY_INFORMATION 0x0008
#define WORKER_FACTORY_READY_WORKER 0x0010
#define WORKER_FACTORY_SHUTDOWN 0x0020

#define OBJECT_TYPE_CREATE (0x0001)
#define OBJECT_TYPE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

#define WMIGUID_QUERY                 0x0001
#define WMIGUID_SET                   0x0002
#define WMIGUID_NOTIFICATION          0x0004
#define WMIGUID_READ_DESCRIPTION      0x0008
#define WMIGUID_EXECUTE               0x0010
#define TRACELOG_CREATE_REALTIME      0x0020
#define TRACELOG_CREATE_ONDISK        0x0040
#define TRACELOG_GUID_ENABLE          0x0080
#define TRACELOG_ACCESS_KERNEL_LOGGER 0x0100
#define TRACELOG_CREATE_INPROC        0x0200
#define TRACELOG_ACCESS_REALTIME      0x0400
#define TRACELOG_REGISTER_GUIDS       0x0800

//
// This is the maximum MaximumLength for a UNICODE_STRING.
//

#define MAXUSHORT   0xffff     
#define MAX_USTRING ( sizeof(WCHAR) * (MAXUSHORT/sizeof(WCHAR)) )

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;
	PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID Pointer;
	} DUMMYUNIONNAME;

	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

/*
** Semaphore START
*/

#ifndef _SEMAPHORE_INFORMATION_CLASS
typedef enum _SEMAPHORE_INFORMATION_CLASS {
	SemaphoreBasicInformation
} SEMAPHORE_INFORMATION_CLASS;
#endif

#ifndef _SEMAPHORE_BASIC_INFORMATION
typedef struct _SEMAPHORE_BASIC_INFORMATION {
	LONG CurrentCount;
	LONG MaximumCount;
} SEMAPHORE_BASIC_INFORMATION, *PSEMAPHORE_BASIC_INFORMATION;
#endif

/*
** Semaphore END
*/

/*
** Processes START
*/

#ifndef KPRIORITY
typedef LONG KPRIORITY;
#endif

typedef enum _THREAD_STATE {
	StateInitialized,
	StateReady,
	StateRunning,
	StateStandby,
	StateTerminated,
	StateWait,
	StateTransition,
	StateUnknown
} THREAD_STATE;

typedef enum _KWAIT_REASON {
	Executive,
	FreePage,
	PageIn,
	PoolAllocation,
	DelayExecution,
	Suspended,
	UserRequest,
	WrExecutive,
	WrFreePage,
	WrPageIn,
	WrPoolAllocation,
	WrDelayExecution,
	WrSuspended,
	WrUserRequest,
	WrEventPair,
	WrQueue,
	WrLpcReceive,
	WrLpcReply,
	WrVirtualMemory,
	WrPageOut,
	WrRendezvous,
	WrKeyedEvent,
	WrTerminated,
	WrProcessInSwap,
	WrCpuRateControl,
	WrCalloutStack,
	WrKernel,
	WrResource,
	WrPushLock,
	WrMutex,
	WrQuantumEnd,
	WrDispatchInt,
	WrPreempted,
	WrYieldExecution,
	WrFastMutex,
	WrGuardedMutex,
	WrRundown,
	MaximumWaitReason
} KWAIT_REASON;

typedef struct _CLIENT_ID {
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _VM_COUNTERS {
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
} VM_COUNTERS;

typedef struct _SYSTEM_THREAD_INFORMATION {
	LARGE_INTEGER   KernelTime;
	LARGE_INTEGER   UserTime;
	LARGE_INTEGER   CreateTime;
	ULONG           WaitTime;
	PVOID           StartAddress;
	CLIENT_ID       ClientId;
	KPRIORITY       Priority;
	KPRIORITY       BasePriority;
	ULONG           ContextSwitchCount;
	THREAD_STATE    State;
	KWAIT_REASON    WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _SYSTEM_PROCESSES_INFORMATION {
	ULONG NextEntryDelta;
	ULONG ThreadCount;
	LARGE_INTEGER SpareLi1;
	LARGE_INTEGER SpareLi2;
	LARGE_INTEGER SpareLi3;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR PageDirectoryBase;
	VM_COUNTERS VmCounters;
	IO_COUNTERS IoCounters;
	SYSTEM_THREAD_INFORMATION Threads[1];
} SYSTEM_PROCESSES_INFORMATION, *PSYSTEM_PROCESSES_INFORMATION;

typedef enum _PROCESSINFOCLASS {
	ProcessBasicInformation = 0,
	ProcessQuotaLimits = 1,
	ProcessIoCounters = 2,
	ProcessVmCounters = 3,
	ProcessTimes = 4,
	ProcessBasePriority = 5,
	ProcessRaisePriority = 6,
	ProcessDebugPort = 7,
	ProcessExceptionPort = 8,
	ProcessAccessToken = 9,
	ProcessLdtInformation = 10,
	ProcessLdtSize = 11,
	ProcessDefaultHardErrorMode = 12,
	ProcessIoPortHandlers = 13,
	ProcessPooledUsageAndLimits = 14,
	ProcessWorkingSetWatch = 15,
	ProcessUserModeIOPL = 16,
	ProcessEnableAlignmentFaultFixup = 17,
	ProcessPriorityClass = 18,
	ProcessWx86Information = 19,
	ProcessHandleCount = 20,
	ProcessAffinityMask = 21,
	ProcessPriorityBoost = 22,
	ProcessDeviceMap = 23,
	ProcessSessionInformation = 24,
	ProcessForegroundInformation = 25,
	ProcessWow64Information = 26,
	ProcessImageFileName = 27,
	ProcessLUIDDeviceMapsEnabled = 28,
	ProcessBreakOnTermination = 29,
	ProcessDebugObjectHandle = 30,
	ProcessDebugFlags = 31,
	ProcessHandleTracing = 32,
	ProcessIoPriority = 33,
	ProcessExecuteFlags = 34,
	ProcessTlsInformation = 35,
	ProcessCookie = 36,
	ProcessImageInformation = 37,
	ProcessCycleTime = 38,
	ProcessPagePriority = 39,
	ProcessInstrumentationCallback = 40,
	ProcessThreadStackAllocation = 41,
	ProcessWorkingSetWatchEx = 42,
	ProcessImageFileNameWin32 = 43,
	ProcessImageFileMapping = 44,
	ProcessAffinityUpdateMode = 45,
	ProcessMemoryAllocationMode = 46,
	ProcessGroupInformation = 47,
	ProcessTokenVirtualizationEnabled = 48,
	ProcessOwnerInformation = 49,
	ProcessWindowInformation = 50,
	ProcessHandleInformation = 51,
	ProcessMitigationPolicy = 52,
	ProcessDynamicFunctionTableInformation = 53,
	ProcessHandleCheckingMode = 54,
	ProcessKeepAliveCount = 55,
	ProcessRevokeFileHandles = 56,
	ProcessWorkingSetControl = 57,
	ProcessHandleTable = 58,
	ProcessCheckStackExtentsMode = 59,
	ProcessCommandLineInformation = 60,
	ProcessProtectionInformation = 61,
	MaxProcessInfoClass = 62
} PROCESSINFOCLASS;

typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus;
	PVOID PebBaseAddress;
	ULONG_PTR AffinityMask;
	KPRIORITY BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;
typedef PROCESS_BASIC_INFORMATION *PPROCESS_BASIC_INFORMATION;

typedef struct _PROCESS_EXTENDED_BASIC_INFORMATION {
	SIZE_T Size;  
	PROCESS_BASIC_INFORMATION BasicInfo;
	union
	{
		ULONG Flags;
		struct
		{
			ULONG IsProtectedProcess : 1; 
			ULONG IsWow64Process : 1; 
			ULONG IsProcessDeleting : 1; 
			ULONG IsCrossSessionCreate : 1; 
			ULONG IsFrozen : 1; 
			ULONG IsBackground : 1; 
			ULONG IsStronglyNamed : 1;
			ULONG SpareBits : 25; 
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;
} PROCESS_EXTENDED_BASIC_INFORMATION, *PPROCESS_EXTENDED_BASIC_INFORMATION;

/*
** Processes END
*/

#ifndef _SYSTEM_INFORMATION_CLASS
typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemBasicInformation = 0,
	SystemProcessorInformation = 1,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3,
	SystemPathInformation = 4,
	SystemProcessInformation = 5,
	SystemCallCountInformation = 6,
	SystemDeviceInformation = 7,
	SystemProcessorPerformanceInformation = 8,
	SystemFlagsInformation = 9,
	SystemCallTimeInformation = 10,
	SystemModuleInformation = 11,
	SystemLocksInformation = 12,
	SystemStackTraceInformation = 13,
	SystemPagedPoolInformation = 14,
	SystemNonPagedPoolInformation = 15,
	SystemHandleInformation = 16,
	SystemObjectInformation = 17,
	SystemPageFileInformation = 18,
	SystemVdmInstemulInformation = 19,
	SystemVdmBopInformation = 20,
	SystemFileCacheInformation = 21,
	SystemPoolTagInformation = 22,
	SystemInterruptInformation = 23,
	SystemDpcBehaviorInformation = 24,
	SystemFullMemoryInformation = 25,
	SystemLoadGdiDriverInformation = 26,
	SystemUnloadGdiDriverInformation = 27,
	SystemTimeAdjustmentInformation = 28,
	SystemSummaryMemoryInformation = 29,
	SystemMirrorMemoryInformation = 30,
	SystemPerformanceTraceInformation = 31,
	SystemObsolete0 = 32,
	SystemExceptionInformation = 33,
	SystemCrashDumpStateInformation = 34,
	SystemKernelDebuggerInformation = 35,
	SystemContextSwitchInformation = 36,
	SystemRegistryQuotaInformation = 37,
	SystemExtendServiceTableInformation = 38,
	SystemPrioritySeperation = 39,
	SystemVerifierAddDriverInformation = 40,
	SystemVerifierRemoveDriverInformation = 41,
	SystemProcessorIdleInformation = 42,
	SystemLegacyDriverInformation = 43,
	SystemCurrentTimeZoneInformation = 44,
	SystemLookasideInformation = 45,
	SystemTimeSlipNotification = 46,
	SystemSessionCreate = 47,
	SystemSessionDetach = 48,
	SystemSessionInformation = 49,
	SystemRangeStartInformation = 50,
	SystemVerifierInformation = 51,
	SystemVerifierThunkExtend = 52,
	SystemSessionProcessInformation = 53,
	SystemLoadGdiDriverInSystemSpace = 54,
	SystemNumaProcessorMap = 55,
	SystemPrefetcherInformation = 56,
	SystemExtendedProcessInformation = 57,
	SystemRecommendedSharedDataAlignment = 58,
	SystemComPlusPackage = 59,
	SystemNumaAvailableMemory = 60,
	SystemProcessorPowerInformation = 61,
	SystemEmulationBasicInformation = 62,
	SystemEmulationProcessorInformation = 63,
	SystemExtendedHandleInformation = 64,
	SystemLostDelayedWriteInformation = 65,
	SystemBigPoolInformation = 66,
	SystemSessionPoolTagInformation = 67,
	SystemSessionMappedViewInformation = 68,
	SystemHotpatchInformation = 69,
	SystemObjectSecurityMode = 70,
	SystemWatchdogTimerHandler = 71,
	SystemWatchdogTimerInformation = 72,
	SystemLogicalProcessorInformation = 73,
	SystemWow64SharedInformationObsolete = 74,
	SystemRegisterFirmwareTableInformationHandler = 75,
	SystemFirmwareTableInformation = 76,
	SystemModuleInformationEx = 77,
	SystemVerifierTriageInformation = 78,
	SystemSuperfetchInformation = 79,
	SystemMemoryListInformation = 80,
	SystemFileCacheInformationEx = 81,
	SystemThreadPriorityClientIdInformation = 82,
	SystemProcessorIdleCycleTimeInformation = 83,
	SystemVerifierCancellationInformation = 84,
	SystemProcessorPowerInformationEx = 85,
	SystemRefTraceInformation = 86,
	SystemSpecialPoolInformation = 87,
	SystemProcessIdInformation = 88,
	SystemErrorPortInformation = 89,
	SystemBootEnvironmentInformation = 90,
	SystemHypervisorInformation = 91,
	SystemVerifierInformationEx = 92,
	SystemTimeZoneInformation = 93,
	SystemImageFileExecutionOptionsInformation = 94,
	SystemCoverageInformation = 95,
	SystemPrefetchPatchInformation = 96,
	SystemVerifierFaultsInformation = 97,
	SystemSystemPartitionInformation = 98,
	SystemSystemDiskInformation = 99,
	SystemProcessorPerformanceDistribution = 100,
	SystemNumaProximityNodeInformation = 101,
	SystemDynamicTimeZoneInformation = 102,
	SystemCodeIntegrityInformation = 103,
	SystemProcessorMicrocodeUpdateInformation = 104,
	SystemProcessorBrandString = 105,
	SystemVirtualAddressInformation = 106,
	SystemLogicalProcessorAndGroupInformation = 107,
	SystemProcessorCycleTimeInformation = 108,
	SystemStoreInformation = 109,
	SystemRegistryAppendString = 110,
	SystemAitSamplingValue = 111,
	SystemVhdBootInformation = 112,
	SystemCpuQuotaInformation = 113,
	SystemNativeBasicInformation = 114,
	SystemErrorPortTimeouts = 115,
	SystemLowPriorityIoInformation = 116,
	SystemBootEntropyInformation = 117,
	SystemVerifierCountersInformation = 118,
	SystemPagedPoolInformationEx = 119,
	SystemSystemPtesInformationEx = 120,
	SystemNodeDistanceInformation = 121,
	SystemAcpiAuditInformation = 122,
	SystemBasicPerformanceInformation = 123,
	SystemQueryPerformanceCounterInformation = 124,
	SystemSessionBigPoolInformation = 125,
	SystemBootGraphicsInformation = 126,
	SystemScrubPhysicalMemoryInformation = 127,
	SystemBadPageInformation = 128,
	SystemProcessorProfileControlArea = 129,
	SystemCombinePhysicalMemoryInformation = 130,
	SystemEntropyInterruptTimingInformation = 131,
	SystemConsoleInformation = 132,
	SystemPlatformBinaryInformation = 133,
	SystemPolicyInformation = 134,
	SystemHypervisorProcessorCountInformation = 135,
	SystemDeviceDataInformation = 136,
	SystemDeviceDataEnumerationInformation = 137,
	SystemMemoryTopologyInformation = 138,
	SystemMemoryChannelInformation = 139,
	SystemBootLogoInformation = 140,
	SystemProcessorPerformanceInformationEx = 141,
	SystemSpare0 = 142,
	SystemSecureBootPolicyInformation = 143,
	SystemPageFileInformationEx = 144,
	SystemSecureBootInformation = 145,
	SystemEntropyInterruptTimingRawInformation = 146,
	SystemPortableWorkspaceEfiLauncherInformation = 147,
	SystemFullProcessInformation = 148,
	SystemKernelDebuggerInformationEx = 149,
	SystemBootMetadataInformation = 150,
	SystemSoftRebootInformation = 151,
	SystemElamCertificateInformation = 152,
	SystemOfflineDumpConfigInformation = 153,
	SystemProcessorFeaturesInformation = 154,
	SystemRegistryReconciliationInformation = 155,
	SystemEdidInformation = 156,
	MaxSystemInfoClass = 157
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;
#endif

/*
** Timer START
*/

//
// Timer APC routine definition.
//

typedef VOID(*PTIMER_APC_ROUTINE) (
	_In_ PVOID TimerContext,
	_In_ ULONG TimerLowValue,
	_In_ LONG TimerHighValue
	);

typedef enum _TIMER_TYPE {
	NotificationTimer,
	SynchronizationTimer
} TIMER_TYPE;

#ifndef _TIMER_INFORMATION_CLASS
typedef enum _TIMER_INFORMATION_CLASS {
	TimerBasicInformation
} TIMER_INFORMATION_CLASS;
#endif

#ifndef _TIMER_BASIC_INFORMATION
typedef struct _TIMER_BASIC_INFORMATION {
	LARGE_INTEGER RemainingTime;
	BOOLEAN TimerState;
} TIMER_BASIC_INFORMATION, *PTIMER_BASIC_INFORMATION;
#endif

/*
** Timer END
*/

typedef VOID(NTAPI *PIO_APC_ROUTINE)(
	_In_ PVOID ApcContext,
	_In_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ ULONG Reserved
	);

typedef struct _OBJECT_DIRECTORY_INFORMATION {
	UNICODE_STRING Name;
	UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

#ifndef InitializeObjectAttributes
#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }

//
// Valid values for the Attributes field
//

#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_KERNEL_HANDLE       0x00000200L
#define OBJ_FORCE_ACCESS_CHECK  0x00000400L
#define OBJ_VALID_ATTRIBUTES    0x000007F2L

#endif


/*
** Objects START
*/

#ifndef _OBJECT_INFORMATION_CLASS
typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectTypesInformation,
	ObjectHandleFlagInformation,
	ObjectSessionInformation,
	MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;
#endif

#ifndef _OBJECT_BASIC_INFORMATION
typedef struct _OBJECT_BASIC_INFORMATION {
	ULONG Attributes;
	ACCESS_MASK GrantedAccess;
	ULONG HandleCount;
	ULONG PointerCount;
	ULONG PagedPoolCharge;
	ULONG NonPagedPoolCharge;
	ULONG Reserved[3];
	ULONG NameInfoSize;
	ULONG TypeInfoSize;
	ULONG SecurityDescriptorSize;
	LARGE_INTEGER CreationTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;
#endif

#ifndef _OBJECT_NAME_INFORMATION
typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;
#endif

#ifndef _OBJECT_TYPE_INFORMATION
typedef struct _OBJECT_TYPE_INFORMATION {
    UNICODE_STRING TypeName;
    ULONG TotalNumberOfObjects;
    ULONG TotalNumberOfHandles;
    ULONG TotalPagedPoolUsage;
    ULONG TotalNonPagedPoolUsage;
    ULONG TotalNamePoolUsage;
    ULONG TotalHandleTableUsage;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    ULONG HighWaterPagedPoolUsage;
    ULONG HighWaterNonPagedPoolUsage;
    ULONG HighWaterNamePoolUsage;
    ULONG HighWaterHandleTableUsage;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    BOOLEAN SecurityRequired;
    BOOLEAN MaintainHandleCount;
    ULONG PoolType;
    ULONG DefaultPagedPoolCharge;
    ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;
#endif

#ifndef _OBJECT_TYPES_INFORMATION
typedef struct _OBJECT_TYPES_INFORMATION
{
	ULONG NumberOfTypes;
	OBJECT_TYPE_INFORMATION TypeInformation;
} OBJECT_TYPES_INFORMATION, *POBJECT_TYPES_INFORMATION;
#endif

#ifndef _OBJECT_HANDLE_FLAG_INFORMATION
typedef struct _OBJECT_HANDLE_FLAG_INFORMATION
{
	BOOLEAN Inherit;
	BOOLEAN ProtectFromClose;
} OBJECT_HANDLE_FLAG_INFORMATION, *POBJECT_HANDLE_FLAG_INFORMATION;
#endif
/*
** Objects END
*/

/*
** File start
*/

#define FILE_SUPERSEDE                  0x00000000
#define FILE_OPEN                       0x00000001
#define FILE_CREATE                     0x00000002
#define FILE_OPEN_IF                    0x00000003
#define FILE_OVERWRITE                  0x00000004
#define FILE_OVERWRITE_IF               0x00000005
#define FILE_MAXIMUM_DISPOSITION        0x00000005

#define FILE_DIRECTORY_FILE                     0x00000001
#define FILE_WRITE_THROUGH                      0x00000002
#define FILE_SEQUENTIAL_ONLY                    0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING          0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT               0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040
#define FILE_CREATE_TREE_CONNECTION             0x00000080

#define FILE_COMPLETE_IF_OPLOCKED               0x00000100
#define FILE_NO_EA_KNOWLEDGE                    0x00000200
#define FILE_OPEN_FOR_RECOVERY                  0x00000400
#define FILE_RANDOM_ACCESS                      0x00000800

#define FILE_DELETE_ON_CLOSE                    0x00001000
#define FILE_OPEN_BY_FILE_ID                    0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
#define FILE_NO_COMPRESSION                     0x00008000

#define FILE_RESERVE_OPFILTER                   0x00100000
#define FILE_OPEN_REPARSE_POINT                 0x00200000
#define FILE_OPEN_NO_RECALL                     0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY          0x00800000


#define FILE_COPY_STRUCTURED_STORAGE            0x00000041
#define FILE_STRUCTURED_STORAGE                 0x00000441

#define FILE_VALID_OPTION_FLAGS                 0x00ffffff
#define FILE_VALID_PIPE_OPTION_FLAGS            0x00000032
#define FILE_VALID_MAILSLOT_OPTION_FLAGS        0x00000032
#define FILE_VALID_SET_FLAGS                    0x00000036

#ifndef _FILE_INFORMATION_CLASS
typedef enum _FILE_INFORMATION_CLASS
{
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation,
	FileBothDirectoryInformation,
	FileBasicInformation,
	FileStandardInformation,
	FileInternalInformation,
	FileEaInformation,
	FileAccessInformation,
	FileNameInformation,
	FileRenameInformation,
	FileLinkInformation,
	FileNamesInformation,
	FileDispositionInformation,
	FilePositionInformation,
	FileFullEaInformation,
	FileModeInformation,
	FileAlignmentInformation,
	FileAllInformation,
	FileAllocationInformation,
	FileEndOfFileInformation,
	FileAlternateNameInformation,
	FileStreamInformation,
	FilePipeInformation,
	FilePipeLocalInformation,
	FilePipeRemoteInformation,
	FileMailslotQueryInformation,
	FileMailslotSetInformation,
	FileCompressionInformation,
	FileObjectIdInformation,
	FileCompletionInformation,
	FileMoveClusterInformation,
	FileQuotaInformation,
	FileReparsePointInformation,
	FileNetworkOpenInformation,
	FileAttributeTagInformation,
	FileTrackingInformation,
	FileIdBothDirectoryInformation,
	FileIdFullDirectoryInformation,
	FileValidDataLengthInformation,
	FileShortNameInformation,
	FileIoCompletionNotificationInformation,
	FileIoStatusBlockRangeInformation,
	FileIoPriorityHintInformation,
	FileSfioReserveInformation,
	FileSfioVolumeInformation,
	FileHardLinkInformation,
	FileProcessIdsUsingFileInformation,
	FileNormalizedNameInformation,
	FileNetworkPhysicalNameInformation,
	FileIdGlobalTxDirectoryInformation,
	FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;
#endif

typedef struct _FILE_BASIC_INFORMATION {
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	ULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef struct _FILE_STANDARD_INFORMATION
{
	LARGE_INTEGER AllocationSize;
	LARGE_INTEGER EndOfFile;
	ULONG NumberOfLinks;
	UCHAR DeletePending;
	UCHAR Directory;
} FILE_STANDARD_INFORMATION;

typedef struct _FILE_INTERNAL_INFORMATION {
	LARGE_INTEGER IndexNumber;
} FILE_INTERNAL_INFORMATION, *PFILE_INTERNAL_INFORMATION;

typedef struct _FILE_EA_INFORMATION {
	ULONG EaSize;
} FILE_EA_INFORMATION, *PFILE_EA_INFORMATION;

typedef struct _FILE_ACCESS_INFORMATION {
	ACCESS_MASK AccessFlags;
} FILE_ACCESS_INFORMATION, *PFILE_ACCESS_INFORMATION;

typedef struct _FILE_POSITION_INFORMATION {                 
	LARGE_INTEGER CurrentByteOffset;                        
} FILE_POSITION_INFORMATION, *PFILE_POSITION_INFORMATION;   

typedef struct _FILE_MODE_INFORMATION {
	ULONG Mode;
} FILE_MODE_INFORMATION, *PFILE_MODE_INFORMATION;

typedef struct _FILE_ALIGNMENT_INFORMATION {               
	ULONG AlignmentRequirement;                             
} FILE_ALIGNMENT_INFORMATION, *PFILE_ALIGNMENT_INFORMATION;

typedef struct _FILE_NAME_INFORMATION {                    
	ULONG FileNameLength;                                   
	WCHAR FileName[1];                                      
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;          

typedef struct _FILE_ALL_INFORMATION {
	FILE_BASIC_INFORMATION BasicInformation;
	FILE_STANDARD_INFORMATION StandardInformation;
	FILE_INTERNAL_INFORMATION InternalInformation;
	FILE_EA_INFORMATION EaInformation;
	FILE_ACCESS_INFORMATION AccessInformation;
	FILE_POSITION_INFORMATION PositionInformation;
	FILE_MODE_INFORMATION ModeInformation;
	FILE_ALIGNMENT_INFORMATION AlignmentInformation;
	FILE_NAME_INFORMATION NameInformation;
} FILE_ALL_INFORMATION, *PFILE_ALL_INFORMATION;

typedef struct _FILE_NETWORK_OPEN_INFORMATION {                 
	LARGE_INTEGER CreationTime;                                 
	LARGE_INTEGER LastAccessTime;                             
	LARGE_INTEGER LastWriteTime;                              
	LARGE_INTEGER ChangeTime;                                   
	LARGE_INTEGER AllocationSize;                            
	LARGE_INTEGER EndOfFile;                                  
	ULONG FileAttributes;                                    
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;   

typedef struct _FILE_ATTRIBUTE_TAG_INFORMATION {             
	ULONG FileAttributes;                                     
	ULONG ReparseTag;                                         
} FILE_ATTRIBUTE_TAG_INFORMATION, *PFILE_ATTRIBUTE_TAG_INFORMATION; 

typedef struct _FILE_ALLOCATION_INFORMATION {
	LARGE_INTEGER AllocationSize;
} FILE_ALLOCATION_INFORMATION, *PFILE_ALLOCATION_INFORMATION;

typedef struct _FILE_COMPRESSION_INFORMATION {
	LARGE_INTEGER CompressedFileSize;
	USHORT CompressionFormat;
	UCHAR CompressionUnitShift;
	UCHAR ChunkShift;
	UCHAR ClusterShift;
	UCHAR Reserved[3];
} FILE_COMPRESSION_INFORMATION, *PFILE_COMPRESSION_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION {                  
	BOOLEAN DeleteFile;                                         
} FILE_DISPOSITION_INFORMATION, *PFILE_DISPOSITION_INFORMATION; 

typedef struct _FILE_END_OF_FILE_INFORMATION {                  
	LARGE_INTEGER EndOfFile;                                    
} FILE_END_OF_FILE_INFORMATION, *PFILE_END_OF_FILE_INFORMATION; 

typedef struct _FILE_VALID_DATA_LENGTH_INFORMATION {                                    
	LARGE_INTEGER ValidDataLength;                                                      
} FILE_VALID_DATA_LENGTH_INFORMATION, *PFILE_VALID_DATA_LENGTH_INFORMATION;             

typedef struct _FILE_LINK_INFORMATION {
	BOOLEAN ReplaceIfExists;
	HANDLE RootDirectory;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_LINK_INFORMATION, *PFILE_LINK_INFORMATION;

typedef struct _FILE_MOVE_CLUSTER_INFORMATION {
	ULONG ClusterCount;
	HANDLE RootDirectory;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_MOVE_CLUSTER_INFORMATION, *PFILE_MOVE_CLUSTER_INFORMATION;

typedef struct _FILE_RENAME_INFORMATION {
	BOOLEAN ReplaceIfExists;
	HANDLE RootDirectory;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

typedef struct _FILE_STREAM_INFORMATION {
	ULONG NextEntryOffset;
	ULONG StreamNameLength;
	LARGE_INTEGER StreamSize;
	LARGE_INTEGER StreamAllocationSize;
	WCHAR StreamName[1];
} FILE_STREAM_INFORMATION, *PFILE_STREAM_INFORMATION;

typedef struct _FILE_TRACKING_INFORMATION {
	HANDLE DestinationFile;
	ULONG ObjectInformationLength;
	CHAR ObjectInformation[1];
} FILE_TRACKING_INFORMATION, *PFILE_TRACKING_INFORMATION;

typedef struct _FILE_COMPLETION_INFORMATION {
	HANDLE Port;
	PVOID Key;
} FILE_COMPLETION_INFORMATION, *PFILE_COMPLETION_INFORMATION;

//
// Define the NamedPipeType flags for NtCreateNamedPipeFile
//

#define FILE_PIPE_BYTE_STREAM_TYPE      0x00000000
#define FILE_PIPE_MESSAGE_TYPE          0x00000001

//
// Define the CompletionMode flags for NtCreateNamedPipeFile
//

#define FILE_PIPE_QUEUE_OPERATION       0x00000000
#define FILE_PIPE_COMPLETE_OPERATION    0x00000001

//
// Define the ReadMode flags for NtCreateNamedPipeFile
//

#define FILE_PIPE_BYTE_STREAM_MODE      0x00000000
#define FILE_PIPE_MESSAGE_MODE          0x00000001

//
// Define the NamedPipeConfiguration flags for NtQueryInformation
//

#define FILE_PIPE_INBOUND               0x00000000
#define FILE_PIPE_OUTBOUND              0x00000001
#define FILE_PIPE_FULL_DUPLEX           0x00000002

//
// Define the NamedPipeState flags for NtQueryInformation
//

#define FILE_PIPE_DISCONNECTED_STATE    0x00000001
#define FILE_PIPE_LISTENING_STATE       0x00000002
#define FILE_PIPE_CONNECTED_STATE       0x00000003
#define FILE_PIPE_CLOSING_STATE         0x00000004

//
// Define the NamedPipeEnd flags for NtQueryInformation
//

#define FILE_PIPE_CLIENT_END            0x00000000
#define FILE_PIPE_SERVER_END            0x00000001


typedef struct _FILE_PIPE_INFORMATION {
	ULONG ReadMode;
	ULONG CompletionMode;
} FILE_PIPE_INFORMATION, *PFILE_PIPE_INFORMATION;

typedef struct _FILE_PIPE_LOCAL_INFORMATION {
	ULONG NamedPipeType;
	ULONG NamedPipeConfiguration;
	ULONG MaximumInstances;
	ULONG CurrentInstances;
	ULONG InboundQuota;
	ULONG ReadDataAvailable;
	ULONG OutboundQuota;
	ULONG WriteQuotaAvailable;
	ULONG NamedPipeState;
	ULONG NamedPipeEnd;
} FILE_PIPE_LOCAL_INFORMATION, *PFILE_PIPE_LOCAL_INFORMATION;

typedef struct _FILE_PIPE_REMOTE_INFORMATION {
	LARGE_INTEGER CollectDataTime;
	ULONG MaximumCollectionCount;
} FILE_PIPE_REMOTE_INFORMATION, *PFILE_PIPE_REMOTE_INFORMATION;

typedef struct _FILE_MAILSLOT_QUERY_INFORMATION {
	ULONG MaximumMessageSize;
	ULONG MailslotQuota;
	ULONG NextMessageSize;
	ULONG MessagesAvailable;
	LARGE_INTEGER ReadTimeout;
} FILE_MAILSLOT_QUERY_INFORMATION, *PFILE_MAILSLOT_QUERY_INFORMATION;

typedef struct _FILE_MAILSLOT_SET_INFORMATION {
	PLARGE_INTEGER ReadTimeout;
} FILE_MAILSLOT_SET_INFORMATION, *PFILE_MAILSLOT_SET_INFORMATION;

typedef struct _FILE_REPARSE_POINT_INFORMATION {
	LONGLONG FileReference;
	ULONG Tag;
} FILE_REPARSE_POINT_INFORMATION, *PFILE_REPARSE_POINT_INFORMATION;

typedef struct _FILE_FULL_EA_INFORMATION {
	ULONG NextEntryOffset;
	UCHAR Flags;
	UCHAR EaNameLength;
	USHORT EaValueLength;
	CHAR EaName[1];
} FILE_FULL_EA_INFORMATION, *PFILE_FULL_EA_INFORMATION;

typedef struct _FILE_GET_EA_INFORMATION {
	ULONG NextEntryOffset;
	UCHAR EaNameLength;
	CHAR EaName[1];
} FILE_GET_EA_INFORMATION, *PFILE_GET_EA_INFORMATION;

typedef struct _FILE_GET_QUOTA_INFORMATION {
	ULONG NextEntryOffset;
	ULONG SidLength;
	SID Sid;
} FILE_GET_QUOTA_INFORMATION, *PFILE_GET_QUOTA_INFORMATION;

typedef struct _FILE_QUOTA_INFORMATION {
	ULONG NextEntryOffset;
	ULONG SidLength;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER QuotaUsed;
	LARGE_INTEGER QuotaThreshold;
	LARGE_INTEGER QuotaLimit;
	SID Sid;
} FILE_QUOTA_INFORMATION, *PFILE_QUOTA_INFORMATION;

typedef struct _FILE_DIRECTORY_INFORMATION {
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

typedef struct _FILE_FULL_DIR_INFORMATION {
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	WCHAR FileName[1];
} FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

typedef struct _FILE_ID_FULL_DIR_INFORMATION {
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	LARGE_INTEGER FileId;
	WCHAR FileName[1];
} FILE_ID_FULL_DIR_INFORMATION, *PFILE_ID_FULL_DIR_INFORMATION;

typedef struct _FILE_BOTH_DIR_INFORMATION {
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	CCHAR ShortNameLength;
	WCHAR ShortName[12];
	WCHAR FileName[1];
} FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

typedef struct _FILE_ID_BOTH_DIR_INFORMATION {
	ULONG NextEntryOffset;
	ULONG FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG FileAttributes;
	ULONG FileNameLength;
	ULONG EaSize;
	CCHAR ShortNameLength;
	WCHAR ShortName[12];
	LARGE_INTEGER FileId;
	WCHAR FileName[1];
} FILE_ID_BOTH_DIR_INFORMATION, *PFILE_ID_BOTH_DIR_INFORMATION;

typedef struct _FILE_NAMES_INFORMATION {
	ULONG NextEntryOffset;
	ULONG FileIndex;
	ULONG FileNameLength;
	WCHAR FileName[1];
} FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;

typedef struct _FILE_OBJECTID_INFORMATION {
	LONGLONG FileReference;
	UCHAR ObjectId[16];
	union {
		struct {
			UCHAR BirthVolumeId[16];
			UCHAR BirthObjectId[16];
			UCHAR DomainId[16];
		};
		UCHAR ExtendedInfo[48];
	};
} FILE_OBJECTID_INFORMATION, *PFILE_OBJECTID_INFORMATION;
/*
** File END
*/

/*
** Section START
*/

#ifndef _SECTION_INFORMATION_CLASS
typedef enum _SECTION_INFORMATION_CLASS {
	SectionBasicInformation,
	SectionImageInformation,
	SectionRelocationInformation,
	MaxSectionInfoClass
} SECTION_INFORMATION_CLASS;
#endif

typedef struct _SECTIONBASICINFO {
	PVOID BaseAddress;
	ULONG AllocationAttributes;
	LARGE_INTEGER MaximumSize;
} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

typedef struct _SECTION_IMAGE_INFORMATION {
	PVOID TransferAddress;
	ULONG ZeroBits;
	SIZE_T MaximumStackSize;
	SIZE_T CommittedStackSize;
	ULONG SubSystemType;
	union {
		struct {
			USHORT SubSystemMinorVersion;
			USHORT SubSystemMajorVersion;
		};
		ULONG SubSystemVersion;
	};
	ULONG GpValue;
	USHORT ImageCharacteristics;
	USHORT DllCharacteristics;
	USHORT Machine;
	BOOLEAN ImageContainsCode;
	BOOLEAN Spare1;
	ULONG LoaderFlags;
	ULONG ImageFileSize;
	ULONG Reserved[1];
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _SECTION_IMAGE_INFORMATION64 {
	ULONGLONG TransferAddress;
	ULONG ZeroBits;
	ULONGLONG MaximumStackSize;
	ULONGLONG CommittedStackSize;
	ULONG SubSystemType;
	union {
		struct {
			USHORT SubSystemMinorVersion;
			USHORT SubSystemMajorVersion;
		};
		ULONG SubSystemVersion;
	};
	ULONG GpValue;
	USHORT ImageCharacteristics;
	USHORT DllCharacteristics;
	USHORT Machine;
	BOOLEAN ImageContainsCode;
	BOOLEAN Spare1;
	ULONG LoaderFlags;
	ULONG ImageFileSize;
	ULONG Reserved[1];
} SECTION_IMAGE_INFORMATION64, *PSECTION_IMAGE_INFORMATION64;

typedef enum _SECTION_INHERIT {
	ViewShare = 1,
	ViewUnmap = 2
} SECTION_INHERIT;

#define SEC_BASED          0x200000
#define SEC_NO_CHANGE      0x400000
#define SEC_FILE           0x800000     
#define SEC_IMAGE         0x1000000     
#define SEC_RESERVE       0x4000000     
#define SEC_COMMIT        0x8000000     
#define SEC_NOCACHE      0x10000000     
#define SEC_GLOBAL       0x20000000
#define SEC_LARGE_PAGES  0x80000000    

/*
** Section END
*/

/*
** Kernel Debugger START 
*/

#ifndef _SYSDBG_COMMAND
typedef enum _SYSDBG_COMMAND {
	SysDbgQueryModuleInformation,
	SysDbgQueryTraceInformation,
	SysDbgSetTracepoint,
	SysDbgSetSpecialCall,
	SysDbgClearSpecialCalls,
	SysDbgQuerySpecialCalls,
	SysDbgBreakPoint,
	SysDbgQueryVersion,
	SysDbgReadVirtual,
	SysDbgWriteVirtual,
	SysDbgReadPhysical,
	SysDbgWritePhysical,
	SysDbgReadControlSpace,
	SysDbgWriteControlSpace,
	SysDbgReadIoSpace,
	SysDbgWriteIoSpace,
	SysDbgReadMsr,
	SysDbgWriteMsr,
	SysDbgReadBusData,
	SysDbgWriteBusData,
	SysDbgCheckLowMemory,
	SysDbgEnableKernelDebugger,
	SysDbgDisableKernelDebugger,
	SysDbgGetAutoKdEnable,
	SysDbgSetAutoKdEnable,
	SysDbgGetPrintBufferSize,
	SysDbgSetPrintBufferSize,
	SysDbgGetKdUmExceptionEnable,
	SysDbgSetKdUmExceptionEnable,
	SysDbgGetTriageDump,
	SysDbgGetKdBlockEnable,
	SysDbgSetKdBlockEnable,
	SysDbgRegisterForUmBreakInfo,
	SysDbgGetUmBreakPid,
	SysDbgClearUmBreakPid,
	SysDbgGetUmAttachPid,
	SysDbgClearUmAttachPid
} SYSDBG_COMMAND, *PSYSDBG_COMMAND;
#endif

#ifndef _SYSDBG_VIRTUAL
typedef struct _SYSDBG_VIRTUAL
{
	PVOID Address;
	PVOID Buffer;
	ULONG Request;
} SYSDBG_VIRTUAL, *PSYSDBG_VIRTUAL;
#endif

/*
** Kernel Debugger END
*/

/*
** System Boot Environment START
*/

typedef struct _SYSTEM_BOOT_ENVIRONMENT_INFORMATION_V1 // Size=20
{
	struct _GUID BootIdentifier;
	enum _FIRMWARE_TYPE FirmwareType;
} SYSTEM_BOOT_ENVIRONMENT_INFORMATION_V1, *PSYSTEM_BOOT_ENVIRONMENT_INFORMATION_V1;

typedef struct _SYSTEM_BOOT_ENVIRONMENT_INFORMATION // Size=32
{
	struct _GUID BootIdentifier; 
	enum _FIRMWARE_TYPE FirmwareType; 
	unsigned __int64 BootFlags; 
} SYSTEM_BOOT_ENVIRONMENT_INFORMATION, *PSYSTEM_BOOT_ENVIRONMENT_INFORMATION;

/*
** System Boot Environment END
*/

/*
** Mutant START
*/

#ifndef _MUTANT_INFORMATION_CLASS
typedef enum _MUTANT_INFORMATION_CLASS {
	MutantBasicInformation
} MUTANT_INFORMATION_CLASS;
#endif

#ifndef _MUTANT_BASIC_INFORMATION
typedef struct _MUTANT_BASIC_INFORMATION {
	LONG CurrentCount;
	BOOLEAN OwnedByCaller;
	BOOLEAN AbandonedState;
} MUTANT_BASIC_INFORMATION, *PMUTANT_BASIC_INFORMATION;
#endif

/*
** Mutant END
*/

/*
** Key START
*/

#ifndef _KEY_INFORMATION_CLASS 
typedef enum _KEY_INFORMATION_CLASS {
	KeyBasicInformation,
	KeyNodeInformation,
	KeyFullInformation,
	KeyNameInformation,
	KeyCachedInformation,
	KeyFlagsInformation,
	MaxKeyInfoClass
} KEY_INFORMATION_CLASS;
#endif

#ifndef _KEY_FULL_INFORMATION
typedef struct _KEY_FULL_INFORMATION {
	LARGE_INTEGER LastWriteTime;
	ULONG   TitleIndex;
	ULONG   ClassOffset;
	ULONG   ClassLength;
	ULONG   SubKeys;
	ULONG   MaxNameLen;
	ULONG   MaxClassLen;
	ULONG   Values;
	ULONG   MaxValueNameLen;
	ULONG   MaxValueDataLen;
	WCHAR   Class[1];           
} KEY_FULL_INFORMATION, *PKEY_FULL_INFORMATION;
#endif

#ifndef _KEY_BASIC_INFORMATION
typedef struct _KEY_BASIC_INFORMATION {
	LARGE_INTEGER LastWriteTime;
	ULONG TitleIndex;
	ULONG NameLength;
	WCHAR Name[1];
} KEY_BASIC_INFORMATION, *PKEY_BASIC_INFORMATION;
#endif

#ifndef _KEY_VALUE_INFORMATION_CLASS
typedef enum _KEY_VALUE_INFORMATION_CLASS {
	KeyValueBasicInformation,
	KeyValueFullInformation,
	KeyValuePartialInformation,
	KeyValueFullInformationAlign64,
	KeyValuePartialInformationAlign64,
	MaxKeyValueInfoClass
} KEY_VALUE_INFORMATION_CLASS;
#endif

#ifndef _KEY_VALUE_BASIC_INFORMATION
typedef struct _KEY_VALUE_BASIC_INFORMATION {
	ULONG   TitleIndex;
	ULONG   Type;
	ULONG   NameLength;
	WCHAR   Name[1];            // Variable size
} KEY_VALUE_BASIC_INFORMATION, *PKEY_VALUE_BASIC_INFORMATION;
#endif

#ifndef _KEY_VALUE_FULL_INFORMATION
typedef struct _KEY_VALUE_FULL_INFORMATION {
	ULONG   TitleIndex;
	ULONG   Type;
	ULONG   DataOffset;
	ULONG   DataLength;
	ULONG   NameLength;
	WCHAR   Name[1];            // Variable size
	//          Data[1];            // Variable size data not declared
} KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;
#endif

#ifndef _KEY_VALUE_PARTIAL_INFORMATION
typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
	ULONG   TitleIndex;
	ULONG   Type;
	ULONG   DataLength;
	UCHAR   Data[1];            // Variable size
} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;
#endif

#ifndef _KEY_VALUE_PARTIAL_INFORMATION_ALIGN64
typedef struct _KEY_VALUE_PARTIAL_INFORMATION_ALIGN64 {
	ULONG   Type;
	ULONG   DataLength;
	UCHAR   Data[1];            // Variable size
} KEY_VALUE_PARTIAL_INFORMATION_ALIGN64, *PKEY_VALUE_PARTIAL_INFORMATION_ALIGN64;
#endif

#ifndef _KEY_VALUE_ENTRY
typedef struct _KEY_VALUE_ENTRY {
	PUNICODE_STRING ValueName;
	ULONG           DataLength;
	ULONG           DataOffset;
	ULONG           Type;
} KEY_VALUE_ENTRY, *PKEY_VALUE_ENTRY;
#endif

/*
** Key END
*/

/*
** IoCompletion START
*/

#ifndef _IO_COMPLETION_INFORMATION_CLASS
typedef enum _IO_COMPLETION_INFORMATION_CLASS {
	IoCompletionBasicInformation
} IO_COMPLETION_INFORMATION_CLASS;
#endif

#ifndef _IO_COMPLETION_BASIC_INFORMATION
typedef struct _IO_COMPLETION_BASIC_INFORMATION {
	LONG Depth;
} IO_COMPLETION_BASIC_INFORMATION, *PIO_COMPLETION_BASIC_INFORMATION;
#endif

/*
** IoCompletion END
*/

/*
** Event START
*/

//
// Event Specific Access Rights.
//

typedef enum _EVENT_INFORMATION_CLASS {
	EventBasicInformation
} EVENT_INFORMATION_CLASS;

typedef enum _EVENT_TYPE {
	NotificationEvent,
	SynchronizationEvent
} EVENT_TYPE;

typedef struct _EVENT_BASIC_INFORMATION {
	EVENT_TYPE EventType;
	LONG EventState;
} EVENT_BASIC_INFORMATION, *PEVENT_BASIC_INFORMATION;

/*
** Event END
*/

/*
** TIME_FIELDS START
*/

#ifndef CSHORT
typedef short CSHORT;
#endif
typedef struct _TIME_FIELDS {
	CSHORT Year;        // range [1601...]
	CSHORT Month;       // range [1..12]
	CSHORT Day;         // range [1..31]
	CSHORT Hour;        // range [0..23]
	CSHORT Minute;      // range [0..59]
	CSHORT Second;      // range [0..59]
	CSHORT Milliseconds;// range [0..999]
	CSHORT Weekday;     // range [0..6] == [Sunday..Saturday]
} TIME_FIELDS;
typedef TIME_FIELDS *PTIME_FIELDS;

/*
** TIME_FIELDS END
*/

/*
** HANDLE START
*/

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

/*
** HANDLE END
*/

// Privileges

#define SE_MIN_WELL_KNOWN_PRIVILEGE (2L)
#define SE_CREATE_TOKEN_PRIVILEGE (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE (3L)
#define SE_LOCK_MEMORY_PRIVILEGE (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE (5L)
#define SE_MACHINE_ACCOUNT_PRIVILEGE (6L)
#define SE_TCB_PRIVILEGE (7L)
#define SE_SECURITY_PRIVILEGE (8L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE (9L)
#define SE_LOAD_DRIVER_PRIVILEGE (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE (11L)
#define SE_SYSTEMTIME_PRIVILEGE (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE (16L)
#define SE_BACKUP_PRIVILEGE (17L)
#define SE_RESTORE_PRIVILEGE (18L)
#define SE_SHUTDOWN_PRIVILEGE (19L)
#define SE_DEBUG_PRIVILEGE (20L)
#define SE_AUDIT_PRIVILEGE (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE (24L)
#define SE_UNDOCK_PRIVILEGE (25L)
#define SE_SYNC_AGENT_PRIVILEGE (26L)
#define SE_ENABLE_DELEGATION_PRIVILEGE (27L)
#define SE_MANAGE_VOLUME_PRIVILEGE (28L)
#define SE_IMPERSONATE_PRIVILEGE (29L)
#define SE_CREATE_GLOBAL_PRIVILEGE (30L)
#define SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE (31L)
#define SE_RELABEL_PRIVILEGE (32L)
#define SE_INC_WORKING_SET_PRIVILEGE (33L)
#define SE_TIME_ZONE_PRIVILEGE (34L)
#define SE_CREATE_SYMBOLIC_LINK_PRIVILEGE (35L)
#define SE_MAX_WELL_KNOWN_PRIVILEGE SE_CREATE_SYMBOLIC_LINK_PRIVILEGE

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

/*
** OBJECT MANAGER START
*/

//
// Header flags
//

#define OB_FLAG_NEW_OBJECT              0x01
#define OB_FLAG_KERNEL_OBJECT           0x02
#define OB_FLAG_CREATOR_INFO            0x04
#define OB_FLAG_EXCLUSIVE_OBJECT        0x08
#define OB_FLAG_PERMANENT_OBJECT        0x10
#define OB_FLAG_DEFAULT_SECURITY_QUOTA  0x20
#define OB_FLAG_SINGLE_HANDLE_ENTRY     0x40
#define OB_FLAG_DELETED_INLINE          0x80

//
// InfoMask values
//

#define OB_INFOMASK_PROCESS_INFO	0x10
#define OB_INFOMASK_QUOTA			0x08
#define OB_INFOMASK_HANDLE			0x04
#define OB_INFOMASK_NAME			0x02
#define OB_INFOMASK_CREATOR_INFO	0x01

typedef PVOID *PDEVICE_MAP;

typedef struct _OBJECT_DIRECTORY_ENTRY {
	PVOID ChainLink;
	PVOID Object;
	ULONG HashValue;
} OBJECT_DIRECTORY_ENTRY, *POBJECT_DIRECTORY_ENTRY;

typedef struct _EX_PUSH_LOCK {
	union
	{
		ULONG Locked : 1;
		ULONG Waiting : 1;
		ULONG Waking : 1;
		ULONG MultipleShared : 1;
		ULONG Shared : 28;
		ULONG Value;
		PVOID Ptr;
	};
} EX_PUSH_LOCK, *PEX_PUSH_LOCK;

typedef struct _OBJECT_DIRECTORY {
	POBJECT_DIRECTORY_ENTRY HashBuckets[37];
	EX_PUSH_LOCK Lock;
	PDEVICE_MAP DeviceMap;
	ULONG SessionId;
	PVOID NamespaceEntry;
	ULONG Flags;
} OBJECT_DIRECTORY, *POBJECT_DIRECTORY;

typedef struct _OBJECT_HEADER_NAME_INFO {
	POBJECT_DIRECTORY Directory;
	UNICODE_STRING Name;
	ULONG QueryReferences;
} OBJECT_HEADER_NAME_INFO, *POBJECT_HEADER_NAME_INFO;

typedef struct _OBJECT_HEADER_CREATOR_INFO {// Size=32
	LIST_ENTRY TypeList; // Size=16 Offset=0
	PVOID CreatorUniqueProcess; // Size=8 Offset=16
	USHORT CreatorBackTraceIndex; // Size=2 Offset=24
	USHORT Reserved; // Size=2 Offset=26
} OBJECT_HEADER_CREATOR_INFO, *POBJECT_HEADER_CREATOR_INFO;

typedef struct _OBJECT_HANDLE_COUNT_ENTRY {// Size=16
	PVOID Process; // Size=8 Offset=0
	struct
	{
		unsigned long HandleCount : 24; // Size=4 Offset=8 BitOffset=0 BitCount=24
		unsigned long LockCount : 8; // Size=4 Offset=8 BitOffset=24 BitCount=8
	};
} OBJECT_HANDLE_COUNT_ENTRY, *POBJECT_HANDLE_COUNT_ENTRY;

typedef struct _OBJECT_HEADER_HANDLE_INFO // Size=16
{
	union
	{
		PVOID HandleCountDataBase; // Size=8 Offset=0
		struct _OBJECT_HANDLE_COUNT_ENTRY SingleEntry; // Size=16 Offset=0
	};
} OBJECT_HEADER_HANDLE_INFO, *POBJECT_HEADER_HANDLE_INFO;

typedef struct _OBJECT_HEADER_PROCESS_INFO { // Size=16
	PVOID ExclusiveProcess; // Size=8 Offset=0
	unsigned __int64 Reserved; // Size=8 Offset=8
} OBJECT_HEADER_PROCESS_INFO, *POBJECT_HEADER_PROCESS_INFO;

typedef struct _OBJECT_HEADER_QUOTA_INFO {
	ULONG PagedPoolCharge; //4
	ULONG NonPagedPoolCharge; //4 
	ULONG SecurityDescriptorCharge; //4
	PVOID SecurityDescriptorQuotaBlock; //sizeof(pointer)
	unsigned __int64 Reserved; //sizeof(uint64)
} OBJECT_HEADER_QUOTA_INFO, *POBJECT_HEADER_QUOTA_INFO;

typedef struct _QUAD {
	union
	{
		INT64 UseThisFieldToCopy;
		float DoNotUseThisField;
	};
} QUAD, *PQUAD;

typedef struct _OBJECT_CREATE_INFORMATION {
	ULONG Attributes;
	PVOID RootDirectory;
	CHAR ProbeMode;
	ULONG PagedPoolCharge;
	ULONG NonPagedPoolCharge;
	ULONG SecurityDescriptorCharge;
	PVOID SecurityDescriptor;
	PSECURITY_QUALITY_OF_SERVICE SecurityQos;
	SECURITY_QUALITY_OF_SERVICE SecurityQualityOfService;
} OBJECT_CREATE_INFORMATION, *POBJECT_CREATE_INFORMATION;

typedef enum _POOL_TYPE {
	NonPagedPool = 0,
	NonPagedPoolExecute = 0,
	PagedPool = 1,
	NonPagedPoolMustSucceed = 2,
	DontUseThisType = 3,
	NonPagedPoolCacheAligned = 4,
	PagedPoolCacheAligned = 5,
	NonPagedPoolCacheAlignedMustS = 6,
	MaxPoolType = 7,
	NonPagedPoolBase = 0,
	NonPagedPoolBaseMustSucceed = 2,
	NonPagedPoolBaseCacheAligned = 4,
	NonPagedPoolBaseCacheAlignedMustS = 6,
	NonPagedPoolSession = 32,
	PagedPoolSession = 33,
	NonPagedPoolMustSucceedSession = 34,
	DontUseThisTypeSession = 35,
	NonPagedPoolCacheAlignedSession = 36,
	PagedPoolCacheAlignedSession = 37,
	NonPagedPoolCacheAlignedMustSSession = 38,
	NonPagedPoolNx = 512,
	NonPagedPoolNxCacheAligned = 516,
	NonPagedPoolSessionNx = 544
} POOL_TYPE;

typedef struct _OBJECT_TYPE_INITIALIZER_V1 {
	USHORT          Length;
	BOOLEAN         UseDefaultObject;
	BOOLEAN         Reserved1;
	ULONG           InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ACCESS_MASK     ValidAccessMask;
	BOOLEAN         SecurityRequired;
	BOOLEAN         MaintainHandleCount; 
	BOOLEAN         MaintainTypeList;    
	UCHAR           Reserved2;
	BOOLEAN         PagedPool;
	ULONG           DefaultPagedPoolCharge;
	ULONG           DefaultNonPagedPoolCharge;
	PVOID           DumpProcedure;
	PVOID           OpenProcedure;
	PVOID           CloseProcedure;
	PVOID           DeleteProcedure;
	PVOID           ParseProcedure;
	PVOID           SecurityProcedure;    
	PVOID           QueryNameProcedure;
	PVOID           OkayToCloseProcedure;
} OBJECT_TYPE_INITIALIZER_V1, *POBJECT_TYPE_INITIALIZER_V1;

typedef struct _OBJECT_TYPE_INITIALIZER_V2 {// Size=120
	USHORT Length; // Size=2 Offset=0
	UCHAR ObjectTypeFlags; // Size=1 Offset=2
	ULONG ObjectTypeCode; // Size=4 Offset=4
	ULONG InvalidAttributes; // Size=4 Offset=8
	GENERIC_MAPPING GenericMapping; // Size=16 Offset=12
	ULONG ValidAccessMask; // Size=4 Offset=28
	ULONG RetainAccess; // Size=4 Offset=32
	POOL_TYPE PoolType; // Size=4 Offset=36
	ULONG DefaultPagedPoolCharge; // Size=4 Offset=40
	ULONG DefaultNonPagedPoolCharge; // Size=4 Offset=44
	PVOID DumpProcedure; // Size=8 Offset=48
	PVOID OpenProcedure; // Size=8 Offset=56
	PVOID CloseProcedure; // Size=8 Offset=64
	PVOID DeleteProcedure; // Size=8 Offset=72
	PVOID ParseProcedure; // Size=8 Offset=80
	PVOID SecurityProcedure; // Size=8 Offset=88
	PVOID QueryNameProcedure; // Size=8 Offset=96
	PVOID OkayToCloseProcedure; // Size=8 Offset=104
} OBJECT_TYPE_INITIALIZER_V2, *POBJECT_TYPE_INITIALIZER_V2;

typedef struct _OBJECT_TYPE_INITIALIZER_V3 {// Size=120
	USHORT Length; // Size=2 Offset=0
	UCHAR ObjectTypeFlags; // Size=1 Offset=2
	ULONG ObjectTypeCode; // Size=4 Offset=4
	ULONG InvalidAttributes; // Size=4 Offset=8
	GENERIC_MAPPING GenericMapping; // Size=16 Offset=12
	ULONG ValidAccessMask; // Size=4 Offset=28
	ULONG RetainAccess; // Size=4 Offset=32
	POOL_TYPE PoolType; // Size=4 Offset=36
	ULONG DefaultPagedPoolCharge; // Size=4 Offset=40
	ULONG DefaultNonPagedPoolCharge; // Size=4 Offset=44
	PVOID DumpProcedure; // Size=8 Offset=48
	PVOID OpenProcedure; // Size=8 Offset=56
	PVOID CloseProcedure; // Size=8 Offset=64
	PVOID DeleteProcedure; // Size=8 Offset=72
	PVOID ParseProcedure; // Size=8 Offset=80
	PVOID SecurityProcedure; // Size=8 Offset=88
	PVOID QueryNameProcedure; // Size=8 Offset=96
	PVOID OkayToCloseProcedure; // Size=8 Offset=104
	ULONG WaitObjectFlagMask; // Size=4 Offset=112
	USHORT WaitObjectFlagOffset; // Size=2 Offset=116
	USHORT WaitObjectPointerOffset; // Size=2 Offset=118
} OBJECT_TYPE_INITIALIZER_V3, *POBJECT_TYPE_INITIALIZER_V3;

typedef struct _OBJECT_TYPE_INITIALIZER {// Size=120
	USHORT Length; // Size=2 Offset=0
	UCHAR ObjectTypeFlags; // Size=1 Offset=2
	ULONG ObjectTypeCode; // Size=4 Offset=4
	ULONG InvalidAttributes; // Size=4 Offset=8
	GENERIC_MAPPING GenericMapping; // Size=16 Offset=12
	ULONG ValidAccessMask; // Size=4 Offset=28
	ULONG RetainAccess; // Size=4 Offset=32
	POOL_TYPE PoolType; // Size=4 Offset=36
	ULONG DefaultPagedPoolCharge; // Size=4 Offset=40
	ULONG DefaultNonPagedPoolCharge; // Size=4 Offset=44
	PVOID DumpProcedure; // Size=8 Offset=48
	PVOID OpenProcedure; // Size=8 Offset=56
	PVOID CloseProcedure; // Size=8 Offset=64
	PVOID DeleteProcedure; // Size=8 Offset=72
	PVOID ParseProcedure; // Size=8 Offset=80
	PVOID SecurityProcedure; // Size=8 Offset=88
	PVOID QueryNameProcedure; // Size=8 Offset=96
	PVOID OkayToCloseProcedure; // Size=8 Offset=104
} OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;

typedef struct _OBJECT_TYPE_V2 {// Size=216
	LIST_ENTRY TypeList; // Size=16 Offset=0
	UNICODE_STRING Name; // Size=16 Offset=16
	PVOID DefaultObject; // Size=8 Offset=32
	UCHAR Index; // Size=1 Offset=40
	ULONG TotalNumberOfObjects; // Size=4 Offset=44
	ULONG TotalNumberOfHandles; // Size=4 Offset=48
	ULONG HighWaterNumberOfObjects; // Size=4 Offset=52
	ULONG HighWaterNumberOfHandles; // Size=4 Offset=56
	OBJECT_TYPE_INITIALIZER_V2 TypeInfo; 
	EX_PUSH_LOCK TypeLock; 
	ULONG Key; 
	LIST_ENTRY CallbackList; 
} OBJECT_TYPE_V2, *POBJECT_TYPE_V2;

typedef struct _OBJECT_TYPE_V3 {// Size=216
	LIST_ENTRY TypeList; // Size=16 Offset=0
	UNICODE_STRING Name; // Size=16 Offset=16
	PVOID DefaultObject; // Size=8 Offset=32
	UCHAR Index; // Size=1 Offset=40
	ULONG TotalNumberOfObjects; // Size=4 Offset=44
	ULONG TotalNumberOfHandles; // Size=4 Offset=48
	ULONG HighWaterNumberOfObjects; // Size=4 Offset=52
	ULONG HighWaterNumberOfHandles; // Size=4 Offset=56
	OBJECT_TYPE_INITIALIZER_V3 TypeInfo;
	EX_PUSH_LOCK TypeLock; 
	ULONG Key; 
	LIST_ENTRY CallbackList;
} OBJECT_TYPE_V3, *POBJECT_TYPE_V3;

typedef struct _OBJECT_TYPE_COMPATIBLE {
	LIST_ENTRY TypeList; 
	UNICODE_STRING Name; 
	PVOID DefaultObject; 
	UCHAR Index; 
	ULONG TotalNumberOfObjects; 
	ULONG TotalNumberOfHandles; 
	ULONG HighWaterNumberOfObjects; 
	ULONG HighWaterNumberOfHandles; 
	OBJECT_TYPE_INITIALIZER_V2 TypeInfo;
} OBJECT_TYPE_COMPATIBLE, *POBJECT_TYPE_COMPATIBLE;

/*
** brand new header starting from 6.1
*/

typedef struct _OBJECT_HEADER {
	LONG PointerCount;
	union
	{
		LONG HandleCount;
		PVOID NextToFree;
	};
	EX_PUSH_LOCK Lock;
	UCHAR TypeIndex;
	UCHAR TraceFlags;
	UCHAR InfoMask;
	UCHAR Flags;
	union
	{
		POBJECT_CREATE_INFORMATION ObjectCreateInfo;
		PVOID QuotaBlockCharged;
	};
	PVOID SecurityDescriptor;
	QUAD Body;
} OBJECT_HEADER, *POBJECT_HEADER;

#define OBJECT_TO_OBJECT_HEADER(obj) \
    CONTAINING_RECORD( (obj), OBJECT_HEADER, Body )

/*
** OBJECT MANAGER END
*/

/*
* WDM START
*/
#define TIMER_TOLERABLE_DELAY_BITS      6
#define TIMER_EXPIRED_INDEX_BITS        6
#define TIMER_PROCESSOR_INDEX_BITS      5

typedef struct _DISPATCHER_HEADER {
	union {
		union {
			volatile LONG Lock;
			LONG LockNV;
		} DUMMYUNIONNAME;

		struct {                            // Events, Semaphores, Gates, etc.
			UCHAR Type;                     // All (accessible via KOBJECT_TYPE)
			UCHAR Signalling;
			UCHAR Size;
			UCHAR Reserved1;
		} DUMMYSTRUCTNAME;

		struct {                            // Timer
			UCHAR TimerType;
			union {
				UCHAR TimerControlFlags;
				struct {
					UCHAR Absolute : 1;
					UCHAR Wake : 1;
					UCHAR EncodedTolerableDelay : TIMER_TOLERABLE_DELAY_BITS;
				} DUMMYSTRUCTNAME;
			};

			UCHAR Hand;
			union {
				UCHAR TimerMiscFlags;
				struct {

#if !defined(KENCODED_TIMER_PROCESSOR)

					UCHAR Index : TIMER_EXPIRED_INDEX_BITS;

#else

					UCHAR Index : 1;
					UCHAR Processor : TIMER_PROCESSOR_INDEX_BITS;

#endif

					UCHAR Inserted : 1;
					volatile UCHAR Expired : 1;
				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;
		} DUMMYSTRUCTNAME2;

		struct {                            // Timer2
			UCHAR Timer2Type;
			union {
				UCHAR Timer2Flags;
				struct {
					UCHAR Timer2Inserted : 1;
					UCHAR Timer2Expiring : 1;
					UCHAR Timer2CancelPending : 1;
					UCHAR Timer2SetPending : 1;
					UCHAR Timer2Running : 1;
					UCHAR Timer2Disabled : 1;
					UCHAR Timer2ReservedFlags : 2;
				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;

			UCHAR Timer2Reserved1;
			UCHAR Timer2Reserved2;
		} DUMMYSTRUCTNAME3;

		struct {                            // Queue
			UCHAR QueueType;
			union {
				UCHAR QueueControlFlags;
				struct {
					UCHAR Abandoned : 1;
					UCHAR DisableIncrement : 1;
					UCHAR QueueReservedControlFlags : 6;
				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;

			UCHAR QueueSize;
			UCHAR QueueReserved;
		} DUMMYSTRUCTNAME4;

		struct {                            // Thread
			UCHAR ThreadType;
			UCHAR ThreadReserved;
			union {
				UCHAR ThreadControlFlags;
				struct {
					UCHAR CycleProfiling : 1;
					UCHAR CounterProfiling : 1;
					UCHAR GroupScheduling : 1;
					UCHAR AffinitySet : 1;
					UCHAR ThreadReservedControlFlags : 4;
				} DUMMYSTRUCTNAME;
			} DUMMYUNIONNAME;

			union {
				UCHAR DebugActive;

#if !defined(_X86_)

				struct {
					BOOLEAN ActiveDR7 : 1;
					BOOLEAN Instrumented : 1;
					BOOLEAN Minimal : 1;
					BOOLEAN Reserved4 : 3;
					BOOLEAN UmsScheduled : 1;
					BOOLEAN UmsPrimary : 1;
				} DUMMYSTRUCTNAME;

#endif

			} DUMMYUNIONNAME2;
		} DUMMYSTRUCTNAME5;

		struct {                         // Mutant
			UCHAR MutantType;
			UCHAR MutantSize;
			BOOLEAN DpcActive;
			UCHAR MutantReserved;
		} DUMMYSTRUCTNAME6;
	} DUMMYUNIONNAME;

	LONG SignalState;                   // Object lock
	LIST_ENTRY WaitListHead;            // Object lock
} DISPATCHER_HEADER, *PDISPATCHER_HEADER;

typedef struct _KEVENT {
	DISPATCHER_HEADER Header;
} KEVENT, *PKEVENT, *PRKEVENT;

typedef struct _KMUTANT {
	DISPATCHER_HEADER Header;
	LIST_ENTRY MutantListEntry;
	struct _KTHREAD *OwnerThread;
	BOOLEAN Abandoned;
	UCHAR ApcDisable;
} KMUTANT, *PKMUTANT, *PRKMUTANT, KMUTEX, *PKMUTEX, *PRKMUTEX;

typedef struct _KSEMAPHORE {
	DISPATCHER_HEADER Header;
	LONG Limit;
} KSEMAPHORE, *PKSEMAPHORE, *PRKSEMAPHORE;

typedef struct _KTIMER {
	DISPATCHER_HEADER Header;
	ULARGE_INTEGER DueTime;
	LIST_ENTRY TimerListEntry;
	struct _KDPC *Dpc;
	ULONG Processor;
	LONG Period;
} KTIMER, *PKTIMER, *PRKTIMER;

typedef struct _KDEVICE_QUEUE_ENTRY {
	LIST_ENTRY DeviceListEntry;
	ULONG SortKey;
	BOOLEAN Inserted;
} KDEVICE_QUEUE_ENTRY, *PKDEVICE_QUEUE_ENTRY, *PRKDEVICE_QUEUE_ENTRY;

typedef enum _KDPC_IMPORTANCE {
	LowImportance,
	MediumImportance,
	HighImportance
} KDPC_IMPORTANCE;

typedef struct _KDPC {
	union {
		ULONG TargetInfoAsUlong;
		struct {
			UCHAR Type;
			UCHAR Importance;
			volatile USHORT Number;
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;

	SINGLE_LIST_ENTRY DpcListEntry;
	KAFFINITY ProcessorHistory;
	PVOID DeferredRoutine;
	PVOID DeferredContext;
	PVOID SystemArgument1;
	PVOID SystemArgument2;
	__volatile PVOID DpcData;
} KDPC, *PKDPC, *PRKDPC;

typedef struct _WAIT_CONTEXT_BLOCK {
	union {
		KDEVICE_QUEUE_ENTRY WaitQueueEntry;
		struct {
			LIST_ENTRY DmaWaitEntry;
			ULONG NumberOfChannels;
			ULONG SyncCallback : 1;
			ULONG DmaContext : 1;
			ULONG Reserved : 30;
		};
	};
	PVOID DeviceRoutine;
	PVOID DeviceContext;
	ULONG NumberOfMapRegisters;
	PVOID DeviceObject;
	PVOID CurrentIrp;
	PKDPC BufferChainingDpc;
} WAIT_CONTEXT_BLOCK, *PWAIT_CONTEXT_BLOCK;

#define MAXIMUM_VOLUME_LABEL_LENGTH  (32 * sizeof(WCHAR)) // 32 characters

typedef struct _VPB {
	CSHORT Type;
	CSHORT Size;
	USHORT Flags;
	USHORT VolumeLabelLength; // in bytes
	struct _DEVICE_OBJECT *DeviceObject;
	struct _DEVICE_OBJECT *RealDevice;
	ULONG SerialNumber;
	ULONG ReferenceCount;
	WCHAR VolumeLabel[MAXIMUM_VOLUME_LABEL_LENGTH / sizeof(WCHAR)];
} VPB, *PVPB;

typedef struct _KQUEUE {
	DISPATCHER_HEADER Header;
	LIST_ENTRY EntryListHead;
	ULONG CurrentCount;
	ULONG MaximumCount;
	LIST_ENTRY ThreadListHead;
} KQUEUE, *PKQUEUE;

typedef struct _KDEVICE_QUEUE {
	CSHORT Type;
	CSHORT Size;
	LIST_ENTRY DeviceListHead;
	KSPIN_LOCK Lock;

#if defined(_AMD64_)

	union {
		BOOLEAN Busy;
		struct {
			LONG64 Reserved : 8;
			LONG64 Hint : 56;
		};
	};

#else

	BOOLEAN Busy;

#endif

} KDEVICE_QUEUE, *PKDEVICE_QUEUE, *PRKDEVICE_QUEUE;

enum _KOBJECTS {
	EventNotificationObject = 0x0,
	EventSynchronizationObject = 0x1,
	MutantObject = 0x2,
	ProcessObject = 0x3,
	QueueObject = 0x4,
	SemaphoreObject = 0x5,
	ThreadObject = 0x6,
	GateObject = 0x7,
	TimerNotificationObject = 0x8,
	TimerSynchronizationObject = 0x9,
	Spare2Object = 0xa,
	Spare3Object = 0xb,
	Spare4Object = 0xc,
	Spare5Object = 0xd,
	Spare6Object = 0xe,
	Spare7Object = 0xf,
	Spare8Object = 0x10,
	Spare9Object = 0x11,
	ApcObject = 0x12,
	DpcObject = 0x13,
	DeviceQueueObject = 0x14,
	EventPairObject = 0x15,
	InterruptObject = 0x16,
	ProfileObject = 0x17,
	ThreadedDpcObject = 0x18,
	MaximumKernelObject = 0x19,
};

#define DO_VERIFY_VOLUME                0x00000002      // ntddk nthal ntifs wdm
#define DO_BUFFERED_IO                  0x00000004      // ntddk nthal ntifs wdm
#define DO_EXCLUSIVE                    0x00000008      // ntddk nthal ntifs wdm
#define DO_DIRECT_IO                    0x00000010      // ntddk nthal ntifs wdm
#define DO_MAP_IO_BUFFER                0x00000020      // ntddk nthal ntifs wdm
#define DO_DEVICE_HAS_NAME              0x00000040      // ntddk nthal ntifs
#define DO_DEVICE_INITIALIZING          0x00000080      // ntddk nthal ntifs wdm
#define DO_SYSTEM_BOOT_PARTITION        0x00000100      // ntddk nthal ntifs
#define DO_LONG_TERM_REQUESTS           0x00000200      // ntddk nthal ntifs
#define DO_NEVER_LAST_DEVICE            0x00000400      // ntddk nthal ntifs
#define DO_SHUTDOWN_REGISTERED          0x00000800      // ntddk nthal ntifs wdm
#define DO_BUS_ENUMERATED_DEVICE        0x00001000      // ntddk nthal ntifs wdm
#define DO_POWER_PAGABLE                0x00002000      // ntddk nthal ntifs wdm
#define DO_POWER_INRUSH                 0x00004000      // ntddk nthal ntifs wdm
#define DO_POWER_NOOP                   0x00008000
#define DO_LOW_PRIORITY_FILESYSTEM      0x00010000      // ntddk nthal ntifs
#define DO_XIP                          0x00020000

#define FILE_REMOVABLE_MEDIA                        0x00000001
#define FILE_READ_ONLY_DEVICE                       0x00000002
#define FILE_FLOPPY_DISKETTE                        0x00000004
#define FILE_WRITE_ONCE_MEDIA                       0x00000008
#define FILE_REMOTE_DEVICE                          0x00000010
#define FILE_DEVICE_IS_MOUNTED                      0x00000020
#define FILE_VIRTUAL_VOLUME                         0x00000040
#define FILE_AUTOGENERATED_DEVICE_NAME              0x00000080
#define FILE_DEVICE_SECURE_OPEN                     0x00000100
#define FILE_CHARACTERISTIC_PNP_DEVICE              0x00000800
#define FILE_CHARACTERISTIC_TS_DEVICE               0x00001000
#define FILE_CHARACTERISTIC_WEBDAV_DEVICE           0x00002000
#define FILE_CHARACTERISTIC_CSV                     0x00010000
#define FILE_DEVICE_ALLOW_APPCONTAINER_TRAVERSAL    0x00020000
#define FILE_PORTABLE_DEVICE                        0x00040000

#define FILE_DEVICE_BEEP                0x00000001
#define FILE_DEVICE_CD_ROM              0x00000002
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003
#define FILE_DEVICE_CONTROLLER          0x00000004
#define FILE_DEVICE_DATALINK            0x00000005
#define FILE_DEVICE_DFS                 0x00000006
#define FILE_DEVICE_DISK                0x00000007
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008
#define FILE_DEVICE_FILE_SYSTEM         0x00000009
#define FILE_DEVICE_INPORT_PORT         0x0000000a
#define FILE_DEVICE_KEYBOARD            0x0000000b
#define FILE_DEVICE_MAILSLOT            0x0000000c
#define FILE_DEVICE_MIDI_IN             0x0000000d
#define FILE_DEVICE_MIDI_OUT            0x0000000e
#define FILE_DEVICE_MOUSE               0x0000000f
#define FILE_DEVICE_MULTI_UNC_PROVIDER  0x00000010
#define FILE_DEVICE_NAMED_PIPE          0x00000011
#define FILE_DEVICE_NETWORK             0x00000012
#define FILE_DEVICE_NETWORK_BROWSER     0x00000013
#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014
#define FILE_DEVICE_NULL                0x00000015
#define FILE_DEVICE_PARALLEL_PORT       0x00000016
#define FILE_DEVICE_PHYSICAL_NETCARD    0x00000017
#define FILE_DEVICE_PRINTER             0x00000018
#define FILE_DEVICE_SCANNER             0x00000019
#define FILE_DEVICE_SERIAL_MOUSE_PORT   0x0000001a
#define FILE_DEVICE_SERIAL_PORT         0x0000001b
#define FILE_DEVICE_SCREEN              0x0000001c
#define FILE_DEVICE_SOUND               0x0000001d
#define FILE_DEVICE_STREAMS             0x0000001e
#define FILE_DEVICE_TAPE                0x0000001f
#define FILE_DEVICE_TAPE_FILE_SYSTEM    0x00000020
#define FILE_DEVICE_TRANSPORT           0x00000021
#define FILE_DEVICE_UNKNOWN             0x00000022
#define FILE_DEVICE_VIDEO               0x00000023
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_WAVE_IN             0x00000025
#define FILE_DEVICE_WAVE_OUT            0x00000026
#define FILE_DEVICE_8042_PORT           0x00000027
#define FILE_DEVICE_NETWORK_REDIRECTOR  0x00000028
#define FILE_DEVICE_BATTERY             0x00000029
#define FILE_DEVICE_BUS_EXTENDER        0x0000002a
#define FILE_DEVICE_MODEM               0x0000002b
#define FILE_DEVICE_VDM                 0x0000002c
#define FILE_DEVICE_MASS_STORAGE        0x0000002d
#define FILE_DEVICE_SMB                 0x0000002e
#define FILE_DEVICE_KS                  0x0000002f
#define FILE_DEVICE_CHANGER             0x00000030
#define FILE_DEVICE_SMARTCARD           0x00000031
#define FILE_DEVICE_ACPI                0x00000032
#define FILE_DEVICE_DVD                 0x00000033
#define FILE_DEVICE_FULLSCREEN_VIDEO    0x00000034
#define FILE_DEVICE_DFS_FILE_SYSTEM     0x00000035
#define FILE_DEVICE_DFS_VOLUME          0x00000036
#define FILE_DEVICE_SERENUM             0x00000037
#define FILE_DEVICE_TERMSRV             0x00000038
#define FILE_DEVICE_KSEC                0x00000039
#define FILE_DEVICE_FIPS                0x0000003A
#define FILE_DEVICE_INFINIBAND          0x0000003B
#define FILE_DEVICE_VMBUS               0x0000003E
#define FILE_DEVICE_CRYPT_PROVIDER      0x0000003F
#define FILE_DEVICE_WPD                 0x00000040
#define FILE_DEVICE_BLUETOOTH           0x00000041
#define FILE_DEVICE_MT_COMPOSITE        0x00000042
#define FILE_DEVICE_MT_TRANSPORT        0x00000043
#define FILE_DEVICE_BIOMETRIC           0x00000044
#define FILE_DEVICE_PMI                 0x00000045
#define FILE_DEVICE_EHSTOR              0x00000046
#define FILE_DEVICE_DEVAPI              0x00000047
#define FILE_DEVICE_GPIO                0x00000048
#define FILE_DEVICE_USBEX               0x00000049
#define FILE_DEVICE_CONSOLE             0x00000050
#define FILE_DEVICE_NFP                 0x00000051
#define FILE_DEVICE_SYSENV              0x00000052
#define FILE_DEVICE_VIRTUAL_BLOCK       0x00000053
#define FILE_DEVICE_POINT_OF_SERVICE    0x00000054

#define FILE_BYTE_ALIGNMENT             0x00000000
#define FILE_WORD_ALIGNMENT             0x00000001
#define FILE_LONG_ALIGNMENT             0x00000003
#define FILE_QUAD_ALIGNMENT             0x00000007
#define FILE_OCTA_ALIGNMENT             0x0000000f
#define FILE_32_BYTE_ALIGNMENT          0x0000001f
#define FILE_64_BYTE_ALIGNMENT          0x0000003f
#define FILE_128_BYTE_ALIGNMENT         0x0000007f
#define FILE_256_BYTE_ALIGNMENT         0x000000ff
#define FILE_512_BYTE_ALIGNMENT         0x000001ff

#define DPC_NORMAL 0
#define DPC_THREADED 1

typedef struct _DEVICE_OBJECT {
	CSHORT                      Type;
	USHORT                      Size;
	LONG                        ReferenceCount;
	struct _DRIVER_OBJECT  *DriverObject;
	struct _DEVICE_OBJECT  *NextDevice;
	struct _DEVICE_OBJECT  *AttachedDevice;
	struct _IRP  *CurrentIrp;
	PVOID		                Timer;
	ULONG                       Flags;
	ULONG                       Characteristics;
	__volatile PVPB             Vpb;
	PVOID                       DeviceExtension;
	DEVICE_TYPE                 DeviceType;
	CCHAR                       StackSize;
	union {
		LIST_ENTRY         ListEntry;
		WAIT_CONTEXT_BLOCK Wcb;
	} Queue;
	ULONG                       AlignmentRequirement;
	KDEVICE_QUEUE               DeviceQueue;
	KDPC                        Dpc;
	ULONG                       ActiveThreadCount;
	PSECURITY_DESCRIPTOR        SecurityDescriptor;
	KEVENT                      DeviceLock;
	USHORT                      SectorSize;
	USHORT                      Spare1;
	struct _DEVOBJ_EXTENSION  *  DeviceObjectExtension;
	PVOID                       Reserved;
} DEVICE_OBJECT, *PDEVICE_OBJECT;

typedef struct _DEVOBJ_EXTENSION {

	CSHORT          Type;
	USHORT          Size;

	//
	// Public part of the DeviceObjectExtension structure
	//

	PDEVICE_OBJECT  DeviceObject;               // owning device object

	// end_ntddk end_nthal end_ntifs end_wdm end_ntosp

	//
	// Universal Power Data - all device objects must have this
	//

	ULONG           PowerFlags;             // see ntos\po\pop.h
	// WARNING: Access via PO macros
	// and with PO locking rules ONLY.

	//
	// Pointer to the non-universal power data
	//  Power data that only some device objects need is stored in the
	//  device object power extension -> DOPE
	//  see po.h
	//

	struct          _DEVICE_OBJECT_POWER_EXTENSION  *Dope;

	//
	// power state information
	//

	//
	// Device object extension flags.  Protected by the IopDatabaseLock.
	//

	ULONG ExtensionFlags;

	//
	// PnP manager fields
	//

	PVOID           DeviceNode;

	//
	// AttachedTo is a pointer to the device object that this device
	// object is attached to.  The attachment chain is now doubly
	// linked: this pointer and DeviceObject->AttachedDevice provide the
	// linkage.
	//

	PDEVICE_OBJECT  AttachedTo;

	//
	// The next two fields are used to prevent recursion in IoStartNextPacket
	// interfaces.
	//

	LONG           StartIoCount;       // Used to keep track of number of pending start ios.
	LONG           StartIoKey;         // Next startio key
	ULONG          StartIoFlags;       // Start Io Flags. Need a separate flag so that it can be accessed without locks
	PVPB           Vpb;                // If not NULL contains the VPB of the mounted volume.
	// Set in the filesystem's volume device object.
	// This is a reverse VPB pointer.

	// begin_ntddk begin_wdm begin_nthal begin_ntifs begin_ntosp

} DEVOBJ_EXTENSION, *PDEVOBJ_EXTENSION;

typedef struct _FAST_IO_DISPATCH {
	ULONG SizeOfFastIoDispatch;
	PVOID FastIoCheckIfPossible;
	PVOID FastIoRead;
	PVOID FastIoWrite;
	PVOID FastIoQueryBasicInfo;
	PVOID FastIoQueryStandardInfo;
	PVOID FastIoLock;
	PVOID FastIoUnlockSingle;
	PVOID FastIoUnlockAll;
	PVOID FastIoUnlockAllByKey;
	PVOID FastIoDeviceControl;
	PVOID AcquireFileForNtCreateSection;
	PVOID ReleaseFileForNtCreateSection;
	PVOID FastIoDetachDevice;
	PVOID FastIoQueryNetworkOpenInfo;
	PVOID AcquireForModWrite;
	PVOID MdlRead;
	PVOID MdlReadComplete;
	PVOID PrepareMdlWrite;
	PVOID MdlWriteComplete;
	PVOID FastIoReadCompressed;
	PVOID FastIoWriteCompressed;
	PVOID MdlReadCompleteCompressed;
	PVOID MdlWriteCompleteCompressed;
	PVOID FastIoQueryOpen;
	PVOID ReleaseForModWrite;
	PVOID AcquireForCcFlush;
	PVOID ReleaseForCcFlush;
} FAST_IO_DISPATCH, *PFAST_IO_DISPATCH;

#define IO_TYPE_ADAPTER                 0x00000001
#define IO_TYPE_CONTROLLER              0x00000002
#define IO_TYPE_DEVICE                  0x00000003
#define IO_TYPE_DRIVER                  0x00000004
#define IO_TYPE_FILE                    0x00000005
#define IO_TYPE_IRP                     0x00000006
#define IO_TYPE_MASTER_ADAPTER          0x00000007
#define IO_TYPE_OPEN_PACKET             0x00000008
#define IO_TYPE_TIMER                   0x00000009
#define IO_TYPE_VPB                     0x0000000a
#define IO_TYPE_ERROR_LOG               0x0000000b
#define IO_TYPE_ERROR_MESSAGE           0x0000000c
#define IO_TYPE_DEVICE_OBJECT_EXTENSION 0x0000000d

#define IRP_MJ_CREATE                   0x00
#define IRP_MJ_CREATE_NAMED_PIPE        0x01
#define IRP_MJ_CLOSE                    0x02
#define IRP_MJ_READ                     0x03
#define IRP_MJ_WRITE                    0x04
#define IRP_MJ_QUERY_INFORMATION        0x05
#define IRP_MJ_SET_INFORMATION          0x06
#define IRP_MJ_QUERY_EA                 0x07
#define IRP_MJ_SET_EA                   0x08
#define IRP_MJ_FLUSH_BUFFERS            0x09
#define IRP_MJ_QUERY_VOLUME_INFORMATION 0x0a
#define IRP_MJ_SET_VOLUME_INFORMATION   0x0b
#define IRP_MJ_DIRECTORY_CONTROL        0x0c
#define IRP_MJ_FILE_SYSTEM_CONTROL      0x0d
#define IRP_MJ_DEVICE_CONTROL           0x0e
#define IRP_MJ_INTERNAL_DEVICE_CONTROL  0x0f
#define IRP_MJ_SHUTDOWN                 0x10
#define IRP_MJ_LOCK_CONTROL             0x11
#define IRP_MJ_CLEANUP                  0x12
#define IRP_MJ_CREATE_MAILSLOT          0x13
#define IRP_MJ_QUERY_SECURITY           0x14
#define IRP_MJ_SET_SECURITY             0x15
#define IRP_MJ_POWER                    0x16
#define IRP_MJ_SYSTEM_CONTROL           0x17
#define IRP_MJ_DEVICE_CHANGE            0x18
#define IRP_MJ_QUERY_QUOTA              0x19
#define IRP_MJ_SET_QUOTA                0x1a
#define IRP_MJ_PNP                      0x1b
#define IRP_MJ_PNP_POWER                IRP_MJ_PNP      
#define IRP_MJ_MAXIMUM_FUNCTION         0x1b

typedef struct _DRIVER_EXTENSION {

	//
	// Back pointer to Driver Object
	//

	struct _DRIVER_OBJECT *DriverObject;

	//
	// The AddDevice entry point is called by the Plug & Play manager
	// to inform the driver when a new device instance arrives that this
	// driver must control.
	//

	PVOID AddDevice;

	//
	// The count field is used to count the number of times the driver has
	// had its registered reinitialization routine invoked.
	//

	ULONG Count;

	//
	// The service name field is used by the pnp manager to determine
	// where the driver related info is stored in the registry.
	//

	UNICODE_STRING ServiceKeyName;

} DRIVER_EXTENSION, *PDRIVER_EXTENSION;

#define DRVO_UNLOAD_INVOKED             0x00000001
#define DRVO_LEGACY_DRIVER              0x00000002
#define DRVO_BUILTIN_DRIVER             0x00000004    // Driver objects for Hal, PnP Mgr
#define DRVO_REINIT_REGISTERED          0x00000008
#define DRVO_INITIALIZED                0x00000010
#define DRVO_BOOTREINIT_REGISTERED      0x00000020
#define DRVO_LEGACY_RESOURCES           0x00000040
// end_ntddk end_nthal end_ntifs end_ntosp
#define DRVO_BASE_FILESYSTEM_DRIVER     0x00000080   // A driver that is at the bottom of the filesystem stack.
// begin_ntddk begin_nthal begin_ntifs begin_ntosp

typedef struct _DRIVER_OBJECT {
	CSHORT Type;
	CSHORT Size;

	//
	// The following links all of the devices created by a single driver
	// together on a list, and the Flags word provides an extensible flag
	// location for driver objects.
	//

	PDEVICE_OBJECT DeviceObject;
	ULONG Flags;

	//
	// The following section describes where the driver is loaded.  The count
	// field is used to count the number of times the driver has had its
	// registered reinitialization routine invoked.
	//

	PVOID DriverStart;
	ULONG DriverSize;
	PVOID DriverSection; //PLDR_DATA_TABLE_ENTRY
	PDRIVER_EXTENSION DriverExtension;

	//
	// The driver name field is used by the error log thread
	// determine the name of the driver that an I/O request is/was bound.
	//

	UNICODE_STRING DriverName;

	//
	// The following section is for registry support.  Thise is a pointer
	// to the path to the hardware information in the registry
	//

	PUNICODE_STRING HardwareDatabase;

	//
	// The following section contains the optional pointer to an array of
	// alternate entry points to a driver for "fast I/O" support.  Fast I/O
	// is performed by invoking the driver routine directly with separate
	// parameters, rather than using the standard IRP call mechanism.  Note
	// that these functions may only be used for synchronous I/O, and when
	// the file is cached.
	//

	PFAST_IO_DISPATCH FastIoDispatch;

	//
	// The following section describes the entry points to this particular
	// driver.  Note that the major function dispatch table must be the last
	// field in the object so that it remains extensible.
	//

	PVOID DriverInit;
	PVOID DriverStartIo;
	PVOID DriverUnload;
	PVOID MajorFunction[IRP_MJ_MAXIMUM_FUNCTION + 1];

} DRIVER_OBJECT;
typedef struct _DRIVER_OBJECT *PDRIVER_OBJECT;

typedef struct _LDR_DATA_TABLE_ENTRY_COMPATIBLE {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	union
	{
		LIST_ENTRY InInitializationOrderLinks;
		LIST_ENTRY InProgressLinks;
	} DUMMYUNION0;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD ObsoleteLoadCount;
	WORD TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	} DUMMYUNION1;
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	} DUMMYUNION2;
	//fields below removed for compatibility
} LDR_DATA_TABLE_ENTRY_COMPATIBLE, *PLDR_DATA_TABLE_ENTRY_COMPATIBLE;
typedef LDR_DATA_TABLE_ENTRY_COMPATIBLE LDR_DATA_TABLE_ENTRY;
/*
* WDM END
*/

/*
*  NTQSI Modules START
*/

typedef struct _RTL_PROCESS_MODULE_INFORMATION {
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES {
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

/*
*	NTQSI Modules END
*/

/*
** Virtual Memory START
*/

typedef enum _MEMORY_INFORMATION_CLASS
{
	MemoryBasicInformation,
	MemoryWorkingSetInformation,
	MemoryMappedFilenameInformation,
	MemoryRegionInformation,
	MemoryWorkingSetExInformation
} MEMORY_INFORMATION_CLASS, *PMEMORY_INFORMATION_CLASS;

typedef struct _MEMORY_REGION_INFORMATION {
	PVOID AllocationBase;
	ULONG AllocationProtect;
	ULONG RegionType;
	SIZE_T RegionSize;
} MEMORY_REGION_INFORMATION, *PMEMORY_REGION_INFORMATION;

/*
** Virtual Memory END
*/

/*
** System Firmware START
*/

typedef enum _SYSTEM_FIRMWARE_TABLE_ACTION
{
	SystemFirmwareTable_Enumerate,
	SystemFirmwareTable_Get
} SYSTEM_FIRMWARE_TABLE_ACTION, *PSYSTEM_FIRMWARE_TABLE_ACTION;

typedef struct _SYSTEM_FIRMWARE_TABLE_INFORMATION {
	ULONG ProviderSignature;
	SYSTEM_FIRMWARE_TABLE_ACTION Action;
	ULONG TableID;
	ULONG TableBufferLength;
	UCHAR TableBuffer[ANYSIZE_ARRAY];
} SYSTEM_FIRMWARE_TABLE_INFORMATION, *PSYSTEM_FIRMWARE_TABLE_INFORMATION;

/*
** System Firmware END
*/

/*
** Csr Runtime START
*/

ULONG NTAPI CsrGetProcessId(
	);

/*
** Csr Runtime END
*/

/*
** Runtime Library API START
*/

VOID NTAPI RtlInitUnicodeString(
	_Inout_	PUNICODE_STRING DestinationString,
	_In_	PCWSTR SourceString
	);

NTSTATUS NTAPI RtlGetVersion(
	_Inout_	PRTL_OSVERSIONINFOW lpVersionInformation
	);

VOID NTAPI RtlTimeToTimeFields(
	_Inout_ PLARGE_INTEGER Time,
	_Inout_ PTIME_FIELDS TimeFields
	);

ULONG NTAPI RtlNtStatusToDosError(
	_In_ NTSTATUS Status
	);

NTSTATUS NTAPI RtlGetOwnerSecurityDescriptor(
	_In_  PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PSID *Owner,
	_Out_ PBOOLEAN OwnerDefaulted
	);

NTSTATUS NTAPI RtlGetGroupSecurityDescriptor(
	_In_  PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PSID *Group,
	_Out_ PBOOLEAN GroupDefaulted
	);

NTSTATUS NTAPI RtlGetDaclSecurityDescriptor(
	_In_  PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PBOOLEAN DaclPresent,
	_Out_ PACL *Dacl,
	_Out_ PBOOLEAN DaclDefaulted
	);

NTSTATUS NTAPI RtlGetSaclSecurityDescriptor(
	_In_  PSECURITY_DESCRIPTOR SecurityDescriptor,
	_Out_ PBOOLEAN SaclPresent,
	_Out_ PACL *Sacl,
	_Out_ PBOOLEAN SaclDefaulted
	);

ULONG NTAPI RtlLengthSecurityDescriptor(
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
	);

VOID NTAPI RtlMapGenericMask(
	_In_ PACCESS_MASK AccessMask,
	_In_ PGENERIC_MAPPING GenericMapping
	);

/*
** Runtime Library API END
*/

/*
** Native API START
*/

NTSTATUS NTAPI NtClose(
	_In_ HANDLE Handle
	);

NTSTATUS NTAPI NtOpenDirectoryObject(
	_Out_  PHANDLE				DirectoryHandle,
	_In_   ACCESS_MASK			DesiredAccess,
	_In_   POBJECT_ATTRIBUTES	ObjectAttributes
	);

NTSTATUS NTAPI NtQueryDirectoryObject(
	_In_       HANDLE DirectoryHandle,
	_Out_opt_  PVOID Buffer,
	_In_       ULONG Length,
	_In_       BOOLEAN ReturnSingleEntry,
	_In_       BOOLEAN RestartScan,
	_Inout_    PULONG Context,
			   PULONG ReturnLength
	);

NTSTATUS NTAPI NtQueryObject(
	_In_opt_   HANDLE Handle,
	_In_       OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_Out_opt_  PVOID ObjectInformation,
	_In_       ULONG ObjectInformationLength,
	_Out_opt_  PULONG ReturnLength
	);

NTSTATUS WINAPI NtQuerySystemInformation(
	_In_       SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_    PVOID SystemInformation,
	_In_       ULONG SystemInformationLength,
	_Out_opt_  PULONG ReturnLength
	);

NTSTATUS NTAPI NtCreateMutant(
	_Out_		PHANDLE MutantHandle,
	_In_		ACCESS_MASK DesiredAccess,
	_In_opt_	POBJECT_ATTRIBUTES ObjectAttributes,
	_In_		BOOLEAN InitialOwner
	);

NTSTATUS NTAPI NtOpenMutant(
	_Out_	PHANDLE MutantHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtQueryMutant(
	_In_		HANDLE MutantHandle,
	_In_		MUTANT_INFORMATION_CLASS MutantInformationClass,
	_Out_		PVOID MutantInformation,
	_In_		ULONG MutantInformationLength,
	_Out_opt_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtReleaseMutant(
	_In_		HANDLE MutantHandle,
	_Out_opt_	PLONG PreviousCount
	);

NTSTATUS NTAPI NtCreateTimer(
	_In_		PHANDLE TimerHandle,
	_In_		ACCESS_MASK DesiredAccess,
	_In_opt_	POBJECT_ATTRIBUTES ObjectAttributes,
	_In_		TIMER_TYPE TimerType
	);

NTSTATUS NtSetTimer(
	_In_		HANDLE TimerHandle,
	_In_		PLARGE_INTEGER DueTime,
	_In_opt_	PTIMER_APC_ROUTINE TimerApcRoutine,
	_In_opt_	PVOID TimerContext,
	_In_		BOOLEAN WakeTimer,
	_In_opt_	LONG Period,
	_Out_opt_	PBOOLEAN PreviousState
	);

NTSTATUS NTAPI NtOpenTimer(
	_In_ PHANDLE TimerHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtQueryTimer(
	_In_       HANDLE TimerHandle,
	_In_       TIMER_INFORMATION_CLASS TimerInformationClass,
	_Out_      PVOID TimerInformation,
	_In_       ULONG TimerInformationLength,
	_Out_opt_  PULONG ReturnLength
	);

NTSTATUS WINAPI NtOpenSymbolicLinkObject(
	_Out_		PHANDLE LinkHandle,
	_In_		ACCESS_MASK DesiredAccess,
	_In_		POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtQuerySymbolicLinkObject(
	_In_		HANDLE LinkHandle,
	_Inout_		PUNICODE_STRING LinkTarget,
	_Out_opt_	PULONG  ReturnedLength
	);

NTSTATUS NTAPI NtQuerySemaphore(
	_In_		HANDLE SemaphoreHandle,
	_In_		SEMAPHORE_INFORMATION_CLASS SemaphoreInformationClass,
	_Out_		PVOID SemaphoreInformation,
	_In_		ULONG SemaphoreInformationLength,
	_Out_opt_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtQueryDirectoryFile(
	_In_		HANDLE FileHandle,
	_In_opt_	HANDLE Event,
	_In_opt_	PIO_APC_ROUTINE ApcRoutine,
	_In_opt_	PVOID ApcContext,
	_Out_		PIO_STATUS_BLOCK IoStatusBlock,
	_Out_		PVOID FileInformation,
	_In_		ULONG Length,
	_In_		FILE_INFORMATION_CLASS FileInformationClass,
	_In_		BOOLEAN ReturnSingleEntry,
	_In_opt_	PUNICODE_STRING FileName,
	_In_		BOOLEAN RestartScan
	);

NTSTATUS NTAPI NtQuerySection(
	_In_		HANDLE SectionHandle,
	_In_		SECTION_INFORMATION_CLASS SectionInformationClass,
	_Out_		PVOID SectionInformation,
	_In_		SIZE_T SectionInformationLength,
	_Out_opt_	PSIZE_T ReturnLength
	);

NTSTATUS NtOpenSection(
	_Out_		PHANDLE SectionHandle,
	_In_		ACCESS_MASK DesiredAccess,
	_In_		POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtOpenProcessToken(
	_In_	HANDLE ProcessHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_Out_	PHANDLE TokenHandle
	);

NTSTATUS NTAPI NtAdjustPrivilegesToken(
	_In_		HANDLE TokenHandle,
	_In_		BOOLEAN DisableAllPrivileges,
	_In_opt_	PTOKEN_PRIVILEGES NewState,
	_In_opt_	ULONG BufferLength,
	_Out_opt_	PTOKEN_PRIVILEGES PreviousState,
	_Out_opt_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtQueryInformationToken(
	_In_	HANDLE TokenHandle,
	_In_	TOKEN_INFORMATION_CLASS TokenInformationClass,
	_Out_	PVOID TokenInformation,
	_In_	ULONG TokenInformationLength,
	_Out_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtOpenKey(
	_Out_	PHANDLE KeyHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtQueryKey(
	_In_		HANDLE KeyHandle,
	_In_		KEY_INFORMATION_CLASS KeyInformationClass,
	_Out_opt_	PVOID KeyInformation,
	_In_		ULONG Length,
	_Out_		PULONG ResultLength
	);

NTSTATUS NTAPI NtOpenJobObject(
	_Out_	PHANDLE JobHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtQueryInformationJobObject(
	_In_opt_	HANDLE JobHandle,
	_In_		JOBOBJECTINFOCLASS JobObjectInformationClass,
	_Out_		PVOID JobObjectInformation,
	_In_		ULONG JobObjectInformationLength,
	_Out_opt_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtOpenIoCompletion(
	_Out_	PHANDLE IoCompletionHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtQueryIoCompletion(
	_In_		HANDLE IoCompletionHandle,
	_In_		IO_COMPLETION_INFORMATION_CLASS IoCompletionInformationClass,
	_Out_		PVOID IoCompletionInformation,
	_In_		ULONG IoCompletionInformationLength,
	_Out_opt_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtQueryInformationFile(
	_In_	HANDLE FileHandle,
	_Out_	PIO_STATUS_BLOCK IoStatusBlock,
	_Out_	PVOID FileInformation,
	_In_	ULONG Length,
	_In_	FILE_INFORMATION_CLASS FileInformationClass
	);

NTSTATUS NTAPI NtOpenFile(
	_Out_	PHANDLE FileHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_	PIO_STATUS_BLOCK IoStatusBlock,
	_In_	ULONG ShareAccess,
	_In_	ULONG OpenOptions
	);

NTSTATUS NTAPI NtOpenEvent(
	_Out_	PHANDLE EventHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtOpenKeyedEvent(
	_Out_	PHANDLE KeyedEventHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtOpenSemaphore(
	_Out_	PHANDLE SemaphoreHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

NTSTATUS NTAPI NtQueryEvent(
	_In_		HANDLE EventHandle,
	_In_		EVENT_INFORMATION_CLASS EventInformationClass,
	_Out_		PVOID EventInformation,
	_In_		ULONG EventInformationLength,
	_Out_opt_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtOpenEventPair(
	_Out_	PHANDLE EventPairHandle,
	_In_	ACCESS_MASK DesiredAccess,
	_In_	POBJECT_ATTRIBUTES ObjectAttributes
	);

//TmTx
NTSTATUS NTAPI NtCreateTransaction(
	_Out_     PHANDLE TransactionHandle,
	_In_      ACCESS_MASK DesiredAccess,
	_In_opt_  POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_  LPGUID Uow,
	_In_opt_  HANDLE TmHandle,
	_In_opt_  ULONG CreateOptions,
	_In_opt_  ULONG IsolationLevel,
	_In_opt_  ULONG IsolationFlags,
	_In_opt_  PLARGE_INTEGER Timeout,
	_In_opt_  PUNICODE_STRING Description
	);

//TmRm
NTSTATUS NTAPINtCreateResourceManager(
	_Out_     PHANDLE ResourceManagerHandle,
	_In_      ACCESS_MASK DesiredAccess,
	_In_      HANDLE TmHandle,
	_In_opt_  LPGUID ResourceManagerGuid,
	_In_opt_  POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_  ULONG CreateOptions,
	_In_opt_  PUNICODE_STRING Description
	);

//TmEn
NTSTATUS NTAPI NtCreateEnlistment(
	_Out_     PHANDLE EnlistmentHandle,
	_In_      ACCESS_MASK DesiredAccess,
	_In_      HANDLE ResourceManagerHandle,
	_In_      HANDLE TransactionHandle,
	_In_opt_  POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_  ULONG CreateOptions,
	_In_      NOTIFICATION_MASK NotificationMask,
	_In_opt_  PVOID EnlistmentKey
	);

//TmTm
NTSTATUS NTAPI NtCreateTransactionManager(
	_Out_     PHANDLE TmHandle,
	_In_      ACCESS_MASK DesiredAccess,
	_In_opt_  POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_  PUNICODE_STRING LogFileName,
	_In_opt_  ULONG CreateOptions,
	_In_opt_  ULONG CommitStrength
	);

NTSTATUS NTAPI NtCreateFile(
	_Out_		PHANDLE FileHandle,
	_In_		ACCESS_MASK DesiredAccess,
	_In_		POBJECT_ATTRIBUTES ObjectAttributes,
	_Out_		PIO_STATUS_BLOCK IoStatusBlock,
	_In_opt_	PLARGE_INTEGER AllocationSize,
	_In_		ULONG FileAttributes,
	_In_		ULONG ShareAccess,
	_In_		ULONG CreateDisposition,
	_In_		ULONG CreateOptions,
	_In_opt_	PVOID EaBuffer,
	_In_		ULONG EaLength
	);

NTSTATUS NTAPI NtOpenProcess(
	_Out_		PHANDLE ProcessHandle,
	_In_		ACCESS_MASK DesiredAccess,
	_In_		POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_	PCLIENT_ID ClientId
	);

NTSTATUS NTAPI NtQueryInformationProcess(
	_In_		HANDLE ProcessHandle,
	_In_		PROCESSINFOCLASS ProcessInformationClass,
	_Out_		PVOID ProcessInformation,
	_In_		ULONG ProcessInformationLength,
	_Out_opt_	PULONG ReturnLength
	);

NTSTATUS NTAPI NtDuplicateObject(
	_In_		HANDLE SourceProcessHandle,
	_In_		HANDLE SourceHandle,
	_In_opt_	HANDLE TargetProcessHandle,
	_Out_		PHANDLE TargetHandle,
	_In_		ACCESS_MASK DesiredAccess,
	_In_		ULONG HandleAttributes,
	_In_		ULONG Options
	);

NTSTATUS NTAPI NtSetSecurityObject(
	_In_ HANDLE Handle,
	_In_ SECURITY_INFORMATION SecurityInformation,
	_In_ PSECURITY_DESCRIPTOR SecurityDescriptor
	);

NTSTATUS NTAPI NtQuerySecurityObject(
	_In_ HANDLE Handle,
	__in SECURITY_INFORMATION SecurityInformation,
	_Out_ PSECURITY_DESCRIPTOR SecurityDescriptor,
	_In_ ULONG Length,
	_Out_ PULONG LengthNeeded
	);

NTSTATUS NtCreateIoCompletion(
	_Out_ PHANDLE IoCompletionHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ ULONG Count OPTIONAL
	);

NTSTATUS NTAPI NtCreateEvent(
	_Out_ PHANDLE EventHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_ EVENT_TYPE EventType,
	_In_ BOOLEAN InitialState
	);

NTSTATUS NTAPI NtQueryVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_ PVOID BaseAddress,
	_In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
	_Out_ PVOID MemoryInformation,
	_In_ SIZE_T MemoryInformationLength,
	_Out_opt_ PSIZE_T ReturnLength
	);

NTSTATUS NTAPI NtReadVirtualMemory(
	_In_ HANDLE ProcessHandle,
	_In_opt_ PVOID BaseAddress,
	_Out_ PVOID Buffer,
	_In_ SIZE_T BufferSize,
	_Out_opt_ PSIZE_T NumberOfBytesRead
	);

NTSTATUS NTAPI NtEnumerateKey(
	_In_ HANDLE KeyHandle,
	_In_ ULONG Index,
	_In_ KEY_INFORMATION_CLASS KeyInformationClass,
	_Out_opt_ PVOID KeyInformation,
	_In_ ULONG Length,
	_Out_ PULONG ResultLength
	);