@echo off
:
:Creo Starter Batch for DEVICE ENG
:
:History:
:Modified August.29.2014 by C.G. PARK
:Modified December.16.2015 by C.G. PARK
:Modified NOV.09.2016 BY ME - CREO2.0 M230, NO MAPKEY IN CONFIG.PRO, STAY IN LOCAL DRIVE, RUN & EXIT QUIET
:Modified AUG.21.2020 BY ME - CREO2.0 M240
:
:Network Connections
:
set ptc_drv=d:
set proe_dir="D:\PTC\Creo 2.0\Common Files\M240"
set pro_stds=O:\ptc\pro_stds
set pro_work_drv=d:
set pro_work_dir=PRODATA
:
:Working Directory
:
IF EXIST %proe_dir%\formats\*frm* del %proe_dir%\formats\*frm* /F
IF EXIST %proe_dir%\formats\*tbl* del %proe_dir%\formats\*tbl* /F
IF EXIST %proe_dir%\templates\start*del %proe_dir%\templates\start* /F
IF EXIST %proe_dir%\templates\*.prt*del %proe_dir%\templates\*.prt* /F
IF EXIST %proe_dir%\templates\*.asm*del %proe_dir%\templates\*.asm* /F
IF EXIST %proe_dir%\templates\*.drw*del %proe_dir%\templates\*.drw* /F
IF EXIST %proe_dir%\templates\*.mft*del %proe_dir%\templates\*.mft* /F
:
IF EXIST %pro_stds%\configs\config.pro (
		findstr /i /v "^mapkey ^! ^protkdat" %pro_stds%\configs\config.pro > %proe_dir%\text\config.pro
		)
:
cd O:\dma_f_p_5
cd /d D:\prodata
start "" /B "D:\Ptc\Creo 2.0\Parametric\bin\parametric.exe" "D:\Ptc\Creo 2.0\Parametric\bin\parametric.psf" %*