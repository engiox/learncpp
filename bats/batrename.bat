::@ECHO OFF
SET _IFNAME=
SET _OFNAME=
FOR /F %%I IN ('DIR /B push*.BAT') DO (
    SET "%_IFNAME%=%%I"
    SET %_OFNAME%=%_IFNAME:push=repack%
)
