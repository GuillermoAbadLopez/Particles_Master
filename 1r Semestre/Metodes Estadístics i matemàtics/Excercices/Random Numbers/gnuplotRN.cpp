reset
cd 'C:\CARRERAS\MASTER UB\1r Semestre\Metodes Estadístics i matemàtics\Excercices\Random Numbers'

set yrange [0:10000]
binwidth=0.05
bin(x,width)=width*floor(x/width)

plot 'Random_numbers0.txt' using (bin($1,binwidth))+binwidth/2:(1.0) smooth freq with boxes t "Using the Minimal standard generator"
