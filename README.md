# LaunchFvApp
Launch UEFI application from firmware volume.

# How to use
`LaunchFvApp <App GUID> [UnLockAppleFwUI]`
`UnLockAppleFwUI` is optional and calls `OcUnlockAppleFirmwareUI ()` before launching the app

# How to compile
Copy `LaunchFvApp` to `OpenCorePkg/Application` and add it to `OpenCorePkg.dsc/[Components]` as `OpenCorePkg/Application/LaunchFvApp/LaunchFvApp.inf`

# For what
Just for fun
