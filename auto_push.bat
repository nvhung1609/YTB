@echo off
set "today=%date:~7,2%-%date:~4,2%-%date:~10,4%"
git add .
git commit -m "%today%"
git push origin main