/** @file
  Launch application from firmware volume.

  Copyright (c) 2026, ilikesn0w. All rights reserved.
  SPDX-License-Identifier: BSD-3-Clause
**/

#include <Uefi.h>

#include <Library/BaseLib.h>

#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Library/OcBootManagementLib.h>
#include <Library/OcMiscLib.h>
#include <Library/OcStringLib.h>

STATIC
VOID
PrintHelp (
  VOID
  )
{
  Print (L"Usage: LaunchFvApp <App GUID> [UnLockAppleFwUI]\n");
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;
  UINTN       Argc;
  CHAR16      **Argv;
  EFI_GUID    AppGuid;
  BOOLEAN     UnlockAppleFirmwareUI;

  Status = GetArguments (&Argc, &Argv);
  if (EFI_ERROR (Status) || (Argc < 2) || (Argc > 3)) {
    PrintHelp ();
    return EFI_INVALID_PARAMETER;
  }

  //
  // Convert GUID to EFI_GUID.
  //
  Status = StrToGuid (Argv[1], &AppGuid);
  if (EFI_ERROR (Status)) {
    Print (L"LaunchFvApp: Failed to convert GUID to EFI_GUID - %r\n", Status);
    return Status;
  }

  UnlockAppleFirmwareUI = FALSE;
  if (Argc > 2 ) {
    if (OcStriCmp (Argv[2], L"UnLockAppleFwUI") != 0) {
      PrintHelp ();
      return EFI_INVALID_PARAMETER;
    }

    UnlockAppleFirmwareUI = TRUE;
  }

  //
  // UnlockAppleFirmwareUI if needed.
  //
  if (UnlockAppleFirmwareUI) {
    Status = OcUnlockAppleFirmwareUI ();
    if (EFI_ERROR (Status)) {
      Print (L"LaunchFvApp: Failed to unlock Apple FW UI - %r\n", Status);
      return Status;
    }
  }

  //
  // Launch app.
  //
  Status = OcRunFirmwareApplication (&AppGuid, FALSE);
  if (EFI_ERROR (Status)) {
    Print (L"LaunchFvApp: Failed to run app - %r\n", Status);
    return Status;
  }

  return EFI_SUCCESS;
}
