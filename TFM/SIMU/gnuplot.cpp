reset 
set terminal gif animate delay 1 size 1000,420 
set output "output.gif"

set xlabel "x"
set ylabel "Fields(t,x)"
set xrange [0:4000]
set yrange [-30:30]

do for [i = 0:99]{
	plot "Sky".i.".txt" using 1:2 t "Psi_L" , "Sky".i.".txt" using 1:3 t "Psi_R", "Sky".i.".txt" using 1:4 t "A"
}



//($N*2) multiplica la longitud dels vectors per 2, every 2:2 plotea cada dos vectors, -1 is black and filled la punta plena

//SMOOOTHHH
set pm3d map
set pm3d interpolate 0,0 
splot "Sky".i.".txt" matrix
