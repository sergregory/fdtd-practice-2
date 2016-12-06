#! /usr/bin/gnuplot -persist
set terminal pdf font "Ubuntu, 10"
set encoding utf8
set xlabel "{/Symbol w}" font "Ubuntu, 10"
set ylabel "Power spetrum" font "Ubuntu, 10"
set grid
set pointsize 0.5
set key top left

########################################################################################################################
# dx = 10
# xi = 0.99
########################################################################################################################

c = 299.792458
lambda0 = 600
eps1 = 1.
eps2 = 2.
mu1 = 1.
mu2 = 1.
omega0 = 2 * pi * c / lambda0 
dx = 20
L = 200 * dx 
sqr(m) = m*m
i = {0.0,1.0}
sigma(lambda) = 4 * pi * c / lambda
eslab(epsilon, omega, lambda) = epsilon + i * 4 * pi * sigma(lambda) / omega 
r(epsilon1, epsilon2, mu1, mu2, omega) = (1 - sqrt(eslab(epsilon2, omega, lambda0) * mu1 / (eslab(epsilon1, omega, lambda0) * mu2))) / (1 + sqrt(eslab(epsilon2, omega, lambda0) * mu1 / (eslab(epsilon1, omega, lambda0) * mu2)))
t(epsilon1, epsilon2, mu1, mu2, omega, omega0) = 1 - r(epsilon1, epsilon2, mu1, mu2, omega, omega0)

set yrange [0 : 0.5]
set output "./img/transmission_dx_20_xi_90.pdf"
plot "./_build/ft_fi=10209_e_2_s.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Transmitted, {/Symbol e} + {/Symbol s}", \
     "./_build/ft_fi=10209_e_2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Transmitted, {/Symbol e}", \
     "./_build/ft_fi=10209_e_1.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Incident"

set output "./img/reflection_dx_20_xi_90.pdf"
plot "./_build/ft_fi=7500_e_2_s.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Reflected, {/Symbol e} + {/Symbol s}", \
     "./_build/ft_fi=7500_e_2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Reflected, {/Symbol e}", \
     "./_build/ft_fi=10209_e_1.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Incident"

set output "./img/transmission_dx_20_xi_90_var2.pdf"
plot "./_build/ft_fi=10209_e_2_s_var2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Transmitted, {/Symbol e} + {/Symbol s}", \
     "./_build/ft_fi=10209_e_2_var2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Transmitted, {/Symbol e}", \
     "./_build/ft_fi=10209_e_1_var2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Incident"

set output "./img/reflection_dx_20_xi_90_var2.pdf"
plot "./_build/ft_fi=7500_e_2_s_var2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Reflected, {/Symbol e} + {/Symbol s}", \
     "./_build/ft_fi=7500_e_2_var2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Reflected, {/Symbol e}", \
     "./_build/ft_fi=10209_e_1_var2.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Incident"

set output "./img/reflection_transmission_theory_dx_20_xi_90.pdf"
set xlabel "n{/Symbol w}L/c"
unset yrange
# set multiplot
# set size 1,0.45
# set yrange [ 0 : 0.13 ]
# set origin 0.0,0.0
# set tmargin 2
# set key outside center top maxrows 1
# set ylabel "\|r\|^2"
#plot "./_build/reflection.dat" u ($1):(sqr(abs($2)) + sqr(abs($3))) / (sqr(abs($5)) + sqr(abs($6))) with linespoints title "simul.", 
plot "./_build/reflection.dat" u ($1):(sqr(abs(r(eps1, eps2, mu1, mu2, ($1))))) with lines title "theory" 
# set size 1,0.45
# set origin 0.0,0.55
# set bmargin 1
# set yrange [ 0.88 : 1.02 ]
# set ylabel "\|t\|^2"
# set key outside center top maxrows 1
# plot "./_build/transmission.dat" u ($1):(sqr($2)) / (sqr($5)) with linespoints title "simul.", \
#      "./_build/transmission.dat" u ($1):(sqr(t(eps1, eps2, mu1, mu2, $1, omega0))) with lines title "theory" 
# set nomultiplot
# 
# ########################################################################################################################
# # dx = 20
# # xi = 0.9
# ########################################################################################################################
# c = 299.792458
# epsilon = 2
# dx = 20
# L = 200 * dx 
# n = sqrt(epsilon)
# phi(omega) = n*omega/c*L
# i = {0.0,1.0}
# r(omega) = abs((n*n - 1)*(exp(2.*i*phi(omega))-1) / ((n+1)*(n+1) - (n-1)*(n-1)*exp(2.*i*phi(omega))))
# t(omega) = abs(4 * n * exp(i*phi(omega)) / ((n+1)*(n+1) - (n-1)*(n-1)*exp(2*i*phi(omega))))
# sqr(m) = m*m
# 
# set yrange [0 : 0.5]
# unset size
# unset origin
# unset tmargin
# unset bmargin
# set xlabel "{/Symbol w}" font "Ubuntu, 10"
# set ylabel "Power spetrum" font "Ubuntu, 10"
# set grid
# set pointsize 0.5
# set key inside top right maxrows 2
# set output "./img/transmission_dx_20_xi_90.pdf"
# plot "./_build/ft_fi=10209_dx_20_xi_90.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Transmitted", \
#       "./_build/ft_fi=10209_dx_20_xi_90.dat" u ($1):($5)*($5)+($6)*($6) with linespoints title "Incident"
# 
# set output "./img/reflection_dx_20_xi_90.pdf"
# plot "./_build/ft_fi=7500_dx_20_xi_90.dat" u ($1):($2)*($2)+($3)*($3) with linespoints title "Reflected", \
#       "./_build/ft_fi=7500_dx_20_xi_90.dat" u ($1):($5)*($5)+($6)*($6) with linespoints title "Incident"
# 
# set output "./img/reflection_transmission_theory_dx_20_xi_90.pdf"
# set multiplot
# set size 1,0.45
# set yrange [ 0 : 0.13 ]
# set origin 0.0,0.0
# set bmargin 3.5
# set key outside center top maxrows 1
# set ylabel "\|r\|^2"
# set xlabel "n{/Symbol w}L/c"
# plot "./_build/ft_fi=7500_dx_20_xi_90.dat" u (phi($1)):(sqr($2) + sqr($3)) / (sqr($5) + sqr($6)) with linespoints title "simul.", \
#      "./_build/ft_fi=7500_dx_20_xi_90.dat" u (phi($1)):(sqr(r($1))) with lines title "theory" 
# set size 1,0.45
# set origin 0.0,0.5
# set yrange [ 0.88 : 1.02 ]
# set ylabel "\|t\|^2"
# set xlabel "n{/Symbol w}L/c"
# set key outside center top maxrows 1
# plot "./_build/ft_fi=10209_dx_20_xi_90.dat" u (phi($1)):(sqr($2) + sqr($3)) / (sqr($5) + sqr($6)) with linespoints title "simul.", \
#      "./_build/ft_fi=10209_dx_20_xi_90.dat" u (phi($1)):(sqr(t($1))) with lines title "theory" 
# set nomultiplot
