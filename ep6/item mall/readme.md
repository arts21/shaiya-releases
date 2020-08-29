**instructions**
1. copy ps_game, ps_dbAgent, dbconn.dll, and msado15.dll to your bin
2. execute usp_Read_User_CashPoint_UsersMaster

**ps_game**
* new item mall solution
* new console commands
```asm
/ntcn charname message
/ntcid charid message
```

**ps_dbAgent**
* calls usp_Read_User_CashPoint_UsersMaster when a user enters the game


**notes**

- the ps_game and ps_dbAgent files correct the problems with item mall points
- dbconn.dll reads the login from Db.ini and supports the pet.dll connection
- the dll has been built with runtime libraries in case your system lacks support

**build**

- properties -> linker -> additional dependencies: legacy_stdio_definitions.lib;
- properties -> c++ -> language -> conformance mode: no
- properties -> c++ -> advanced -> disable specific warnings: 4996;4838
- msado15.tlh needs to be in the Debug directory
- msado15.dll needs to be in the directory with the source files

*original code*

- https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3669922-release-ep6-itemmall-fixed.html
