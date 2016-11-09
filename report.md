---
title: Компьютерное моделирование электромагнитных процессов - ДЗ 2
author: Дарья Серебрякова
---

## Задание 1

Создать в вакууме начальный импульс с длиной волны $\lambda_0 = 600$ нм
и длительностью $\tau=5$ фс. Найти численно и построить коэффициент отражения от
полупространства с $\epsilon=2$ в области частот, задаваемой начальным импульсом.
Сравнить с аналитической зависимостью.

**Ответ**

Рассмотрим спектры падающего, прошедшего и отражённого импульсов:

<!-- \begin{figure} -->
<!-- \begin{floatrow} -->
<!--  \ffigbox{\caption{Спектры падающего и прошедшего импульсов при $\lambda_0=600$ нм, -->
<!--          $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=10$ нм, $\xi=0.99$}}% -->
<!--          {\includegraphics{img/transmission_dx_10_xi_99.pdf}} -->
<!--  \ffigbox{\caption{Спектры падающего и прошедшего импульсов при $\lambda_0=600$ нм, -->
<!--          $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=20$ нм, $\xi=0.90$}}% -->
<!--          {\includegraphics{img/transmission_dx_20_xi_90.pdf}} -->         
<!-- \end{floatrow} -->
<!-- \end{figure} -->
\begin{figure}[H]
\centering
{\includegraphics{img/transmission_dx_20_xi_90.pdf}}
\caption{Спектры падающего и прошедшего импульсов при $\lambda_0=600$ нм,
         $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=20$ нм, $\xi=0.90$}
\end{figure}
<!-- \begin{figure}[H] -->
<!-- \centering -->
<!-- {\includegraphics{img/transmission_dx_20_xi_90.pdf}} -->
<!-- \caption{Спектры падающего и прошедшего импульсов при $\lambda_0=600$ нм, -->
<!--          $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=20$ нм, $\xi=0.90$} -->
<!-- \end{figure} -->

<!-- \begin{figure} -->
<!-- \begin{floatrow} -->
<!--  \ffigbox{\caption{Спектры падающего и отражённого импульсов при $\lambda_0=600$ нм, -->
<!--          $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=10$ нм, $\xi=0.99$}}% -->
<!--          {\includegraphics{img/reflection_dx_10_xi_99.pdf}} -->
<!--  \ffigbox{\caption{Спектры падающего и отражённого импульсов при $\lambda_0=600$ нм, -->
<!--          $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=20$ нм, $\xi=0.90$}}% -->
<!--          {\includegraphics{img/reflection_dx_20_xi_90.pdf}} -->         
<!-- \end{floatrow} -->
<!-- \end{figure} -->

\begin{figure}[H]
\centering
{\includegraphics{img/reflection_dx_20_xi_90.pdf}}
\caption{Спектры падающего и отражённого импульсов при $\lambda_0=600$ нм,
         $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=20$ нм, $\xi=0.90$}
\end{figure}
<!-- \begin{figure}[H] -->
<!-- \centering -->
<!-- {\includegraphics{img/reflection_dx_20_xi_90.pdf}} -->
<!-- \caption{Спектры падающего и отражённого импульсов при $\lambda_0=600$ нм, -->
<!--          $\tau=5$ фс, $\epsilon=2$, $L=4000$ нм, $dx=20$ нм, $\xi=0.90$} -->
<!-- \end{figure} -->

Найдём коэффициент отражения и сравним с теоретической зависимостью.

\begin{figure}[H]
\centering
{\includegraphics{img/reflection_transmission_theory_dx_10_xi_99.pdf}}
\caption{Коэффициенты прохождения и отражения для слоя диэлектрика, рассчитанные 
численно (simul.) и аналитически (theory), $dx=10$ нм, $\xi=0.99$}
\end{figure}
\begin{figure}[H]
\centering
{\includegraphics{img/reflection_transmission_theory_dx_20_xi_90.pdf}}
\caption{Коэффициенты прохождения и отражения для слоя диэлектрика, рассчитанные 
численно (simul.) и аналитически (theory), $dx=20$ нм, $\xi=0.90$}
\end{figure}

