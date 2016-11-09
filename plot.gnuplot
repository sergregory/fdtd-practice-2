#! /usr/bin/gnuplot -persist
set terminal pdf font "Ubuntu, 10"
set encoding utf8
set xlabel "\omega" font "Ubuntu, 10"
set ylabel "Power spetrum" font "Ubuntu, 10"
set grid
set pointsize 0.5
set key top left

c = 299.792458
epsilon = 2
dx = 10
L = 200 * dx 
n = sqrt(epsilon)
phi(omega) = n*omega/c*L
i = {0.0,1.0}
r(omega) = abs((n*n - 1)*(exp(2.*i*phi(omega))-1) / ((n+1)*(n+1) - (n-1)*(n-1)*exp(2.*i*phi(omega))))
t(omega) = abs(4 * n * exp(i*phi(omega)) / ((n+1)*(n+1) - (n-1)*(n-1)*exp(2*i*phi(omega))))
sqr(m) = m*m

set output "./img/transmission_dx_10_xi_99_2w.pdf"
plot "./_build/ft_fi=10209_dx_10_xi_99_2w.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Transmitted", \
      "./_build/ft_fi=10209_dx_10_xi_99_2w.dat" u ($1):($5)*($5)+($6)*($6) with lines title "Incident"

set output "./img/transmission_theory_dx_10_xi_99_2w.pdf"
plot "./_build/ft_fi=10209_dx_10_xi_99_2w.dat" u (phi($1)):(sqr($2) + sqr($3)) / (sqr($5) + sqr($6)) with lines title "\|t\|^2, simul.", \
     "./_build/ft_fi=10209_dx_10_xi_99_2w.dat" u (phi($1)):(sqr(t($1))) with linespoints title "\|t\|^2, theory" 

set output "./img/reflection_dx_10_xi_99_2w.pdf"
plot "./_build/ft_fi=7500_dx_10_xi_99_2w.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Reflected", \
      "./_build/ft_fi=7500_dx_10_xi_99_2w.dat" u ($1):($5)*($5)+($6)*($6) with lines title "Incident"

set output "./img/reflection_theory_dx_10_xi_99_2w.pdf"
plot "./_build/ft_fi=7500_dx_10_xi_99_2w.dat" u (phi($1)):(sqr($2) + sqr($3)) / (sqr($5) + sqr($6)) with lines title "\|r\|^2, simul.", \
     "./_build/ft_fi=7500_dx_10_xi_99_2w.dat" u (phi($1)):(sqr(r($1))) with linespoints title "\|r\|^2, theory" 
