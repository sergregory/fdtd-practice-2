#! /usr/bin/python3

from matplotlib import pylab as pl
import numpy as np


def get_wave_freq(wave_len):
    from scipy.constants import pi, c
    # we need speed of light in nm/fs, so multiply by 1E-6
    return 2 * pi * c * 1E-6 / wave_len


def get_sigma(wave_len):
    return 2 * get_wave_freq(wave_len)


def get_eps_general(eps, sigma, omega):
    return eps + sigma / (1.j * omega)


def get_mu():
    return 1


def create_slab(eps_slab, sigma_slab, slab_range, domain_size):
    eps = np.ones(domain_size)
    sigma = np.zeros(domain_size)

    eps[slab_range] = eps_slab
    sigma[slab_range] = sigma_slab
    return eps, sigma


def get_eta(mu, eps):
    return np.sqrt(mu / eps)


def get_reflection_ratio(eta_from, eta_to):
    return (eta_to - eta_from) / (eta_to + eta_from)


def plot_theory():
    from pprint import PrettyPrinter

    printer = PrettyPrinter()

    freq0 = 600
    freq_range = np.linspace(0.8 * freq0, 1.2 * freq0)
    slab_eps = get_eps_general(2, get_sigma(freq0), freq_range)
    printer.pprint(slab_eps)
    printer.pprint(np.ones(len(slab_eps)))

    slab_impedance = get_eta(np.ones(len(slab_eps)), slab_eps)
    reflection = get_reflection_ratio(np.ones(len(slab_impedance)),
                                      slab_impedance)
    printer.pprint(np.square(np.abs(reflection)))
    pl.plot(freq_range, np.square(np.abs(reflection)))
    pl.show()


if __name__ == "__main__":
    plot_theory()
