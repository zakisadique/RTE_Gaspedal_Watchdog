setlocal
python ..\gui\run.py car6.xml
python run.py car6.xml

set OUTDIR=%CD%\out
set PATH=%PATH%;C:\Program Files (x86)\Cypress\PSoC Creator\4.3\PSoC Creator\bin
cd /D Y:\Uni\Master_VL\EAA\Workspace01
del /Q /S Realtime_RTOS.cydsn\source\rte\*
xcopy /Y /S %OUTDIR%\* Realtime_RTOS.cydsn\source\rte
cyprjmgr.exe -wrk Workspace01.cywrk -prj Realtime_RTOS -clean
cyprjmgr.exe -wrk Workspace01.cywrk -prj Realtime_RTOS -build