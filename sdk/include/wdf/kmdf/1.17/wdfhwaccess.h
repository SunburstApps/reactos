/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

_WdfVersionBuild_

Module Name:

    wdfhwaccess.h

Abstract:

    This module contains contains the Windows Driver Framework hw access
    interfaces.

Environment:

    User mode only

Revision History:


--*/

//
// NOTE: This header is generated by stubwork.  Please make any
//       modifications to the corresponding template files
//       (.x or .y) and use stubwork to regenerate the header
//

#ifndef _WDFHWACCESS_H_
#define _WDFHWACCESS_H_

#ifndef WDF_EXTERN_C
  #ifdef __cplusplus
    #define WDF_EXTERN_C       extern "C"
    #define WDF_EXTERN_C_START extern "C" {
    #define WDF_EXTERN_C_END   }
  #else
    #define WDF_EXTERN_C
    #define WDF_EXTERN_C_START
    #define WDF_EXTERN_C_END
  #endif
#endif

WDF_EXTERN_C_START



#if (NTDDI_VERSION >= NTDDI_WIN2K)



//
// Types
//


//
// Functions for HwAccess
//






#endif // (NTDDI_VERSION >= NTDDI_WIN2K)



WDF_EXTERN_C_END

#endif // _WDFHWACCESS_H_

