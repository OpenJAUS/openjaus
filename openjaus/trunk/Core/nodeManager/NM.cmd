@echo off

rem %~dp0 is expanded pathname of the current script under NT
set DEFAULT_NM_HOME=%~dp0..

cd %DEFAULT_NM_HOME%
java -cp lib\jaus.jar;lib\nodeManager.jar openjaus.nodemanager.NodeManager
