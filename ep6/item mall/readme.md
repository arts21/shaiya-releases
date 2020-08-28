**instructions**
1. copy ps_game, ps_dbAgent, and dbconn.dll to your bin
2. execute usp_Read_User_CashPoint_UsersMaster and test

**ps_game**
* new item mall solution
* new console commands
```asm
/ntcn charname message
/ntcid charid message
```

**ps_dbAgent**
* calls usp_Read_User_CashPoint_UsersMaster


**notes**

- the new ps_game and ps_dbAgent solve the point loading and spending issues
- dbconn.dll reads the sql login from Db.ini and supports the pet.dll connection
- the dll has been built with runtime libraries in case your system lacks support

**build**

- properties -> linker -> additional dependencies: legacy_stdio_definitions.lib;
- properties -> c++ -> language -> conformance mode: no
- properties -> c++ -> advanced -> disable specific warnings: 4996;4838
- msado15.tlh needs to be in the Debug directory
- msado15.dll needs to be in the with the source files

*original code*

- https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3669922-release-ep6-itemmall-fixed.html
