@echo off

rem %~dp0 is expanded pathname of the current script under NT
set DEFAULT_NM_HOME=%~dp0..

cd %DEFAULT_NM_HOME%
set PATH=%PATH%;.\bin
rem only need to hit main jar, because its index refers to other libraries
java -Dlog4j.configuration=file:./log4j.properties -jar lib\nodeManager.jar
