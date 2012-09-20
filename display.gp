unset hidden3d
set pm3d
#set palette rgbformulae 22,13,-31
#set palette rgbformulae 7,5,15
set palette defined ( 0 "dark-blue", 1 "dark-yellow", 3 "dark-yellow", 9 "dark-red" ) 
splot "./out" w pm3d

pause -1
