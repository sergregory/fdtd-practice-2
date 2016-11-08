#! /usr/bin/gnuplot -persist
set terminal pdf font "Ubuntu, 10"
set encoding utf8
set xlabel "\omega" font "Ubuntu, 10"
set ylabel "Power spetrum" font "Ubuntu, 10"
set grid
set pointsize 0.5
set key top left

c = 299.792458
epsilon = 4
L = 200 * 20 
n = sqrt(epsilon)
phi(omega) = n*omega/c*L
i = {0.0,1.0}
r(omega) = abs((n*n - 1)*(exp(2.*i*phi(omega))-1) / ((n+1)*(n+1) - (n-1)*(n-1)*exp(2.*i*phi(omega))))
t(omega) = abs(4 * n * exp(i*phi(omega)) / ((n+1)*(n+1) - (n-1)*(n-1)*exp(2*i*phi(omega))))

set output "./img/transmission.pdf"
plot "./_build/ft_fi=10209.dat" u ($1):($2)*($2)+($3)*($3) with lines title "Transmitted", \
      "./_build/ft_fi=10209.dat" u ($1):($5)*($5)+($6)*($6) with lines title "Incident"

set output "./img/transmission_theory.pdf"
plot "./_build/ft_fi=10209.dat" u ($1):(($2)*($2)+($3)*($3)) with lines title "Transmitted", \
      "./_build/ft_fi=10209.dat" u ($1):((($5)*($5)+($6)*($6))*t($1)*t($1)) with lines title "Theory"

set output "./img/reflection.pdf"
plot "./_build/ft_fi=7500.dat" u ($1):($2)*($2)+($3)*($3) with lines title "Reflected", \
      "./_build/ft_fi=7500.dat" u ($1):($5)*($5)+($6)*($6) with lines title "Incident"

set output "./img/reflection_theory.pdf"
plot "./_build/ft_fi=7500.dat" u ($1):(($2)*($2)+($3)*($3)) with lines title "Reflected", \
      "./_build/ft_fi=7500.dat" u ($1):((($5)*($5)+($6)*($6))*r($1)*r($1)) with lines title "Theory"
