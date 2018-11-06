::does things

set targetDir=%1
set solutionDir=%2

echo %targetDir%
echo %solutionDir%
echo lel
mkdir "%targetDir%res"
xcopy "%solutionDir%res" "%targetDir%res" /E /Y /S