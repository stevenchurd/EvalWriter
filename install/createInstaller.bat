xcopy /S dlls\* packages\com.vendor.product\data\ /Y
copy ..\build-EvalWriter-Desktop_Qt_5_0_2_MSVC2010_32bit-Release\release\EvalWriter.exe packages\com.vendor.product\data\ /Y
copy ..\build-EvalWriter-Desktop_Qt_5_0_2_MSVC2010_32bit-Release\release\EvalWriter.exe.embed.manifest packages\com.vendor.product\data\ /Y
C:\Qt\QtIFW-1.3.0\bin\binarycreator.exe --offline-only -c config\config.xml -p packages EvalWriterInstaller.exe
