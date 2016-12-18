#! /usr/bin/python3

from matplotlib import pylab as pl
import numpy as np
from scipy.constants import pi, c


def get_wave_freq(wave_len):
    # we need speed of light in nm/fs, so multiply by 1E-6
    return 2 * pi * c * 1E-6 / wave_len


def get_sigma(wave_len):
    return 2 * get_wave_freq(wave_len)


def get_eps_general(eps, sigma, freq):
    return (eps + sigma * 1j * 4 * pi / freq)


def get_eta(mu, eps):
    return np.sqrt(eps / mu)


def get_reflection_ratio(eta_from, eta_to):
    return (eta_from - eta_to) / (eta_to + eta_from)


def plot_simul(suffix, style):
    incident_pulse_file = "ft_fi=10000_e_1_var" + suffix + ".dat"
    reflected_pulse_file = "ft_fi=7500_e_2_s_var" + suffix + ".dat"
    incident_data = np.loadtxt(incident_pulse_file)
    reflected_data = np.loadtxt(reflected_pulse_file)

    freq_range = incident_data[:, 0]
    incident = incident_data[:, 1] + 1j * incident_data[:, 2]
    reflected = reflected_data[:, 1] + 1j * reflected_data[:, 2]

    reflectedion_coeff = np.square(np.abs(reflected / incident))
    pl.plot(freq_range, reflectedion_coeff, label="alg 1." + suffix, color='black', linestyle=style)


def plot_theory():
    # from pprint import PrettyPrinter

    # printer = PrettyPrinter()

    wavelen = 600
    freq0 = get_wave_freq(wavelen)
    freq_range = np.linspace(0.8 * freq0, 1.2 * freq0)
    slab_eps = get_eps_general(2. + 0. * 1j, get_sigma(wavelen), freq_range)

    slab_impedance = get_eta(np.ones(len(slab_eps)), slab_eps)
    reflection = get_reflection_ratio(np.ones(len(slab_impedance)),
                                      slab_impedance)
    # printer.pprint(np.square(np.abs(reflection)))
    pl.plot(freq_range, np.square(np.abs(reflection)), label="theory", color="black")


if __name__ == "__main__":
    plot_theory()
    plot_simul('1', 'dashed')
    plot_simul('2', 'dotted')
    pl.legend()
    pl.xlabel(r'$\omega$, rad/fs')
    pl.ylabel(r'$\|r\|^2$')
    pl.grid()
    pl.show()
