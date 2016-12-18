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


def plot():
    incident_pulse_file = "ft_fi=10000_e_1_var2.dat"
    reflected_pulse_file = "ft_fi=7500_e_2_s_var2.dat"
    incident_data = np.loadtxt(incident_pulse_file)
    reflected_data = np.loadtxt(reflected_pulse_file)

    freq_range = incident_data[:, 0]
    incident = incident_data[:, 1] + 1j * incident_data[:, 2]
    reflected = reflected_data[:, 1] + 1j * reflected_data[:, 2]

    reflectedion_coeff = np.square(np.abs(reflected / incident))
    pl.plot(freq_range, reflectedion_coeff, label="simul")
    pl.legend()
    pl.show()


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
    pl.plot(freq_range, np.square(np.abs(reflection)), label="theory")


def get_dat_files():
    import os
    import re
    extract_n_sigma_re = re.compile(
        r'(?P<type>Ey|Hz)_vs_x_T=(?P<time>0|12001)_e1E0_s(?P<sigma>[^_]+)_N(?P<width>.+).dat')

    matching_files = {
        match.group(0): match.groupdict()
        for match in map(extract_n_sigma_re.match, os.listdir('.'))
        if match is not None}
    return matching_files


def load_pulse_values(file_list):
    import numpy as np
    from tqdm import tqdm
    sigma_values = sorted(list(set([float(v['sigma']) for v in file_list.values()])))
    N_values = sorted(list(set([int(v['width']) for v in file_list.values()])))
    initial_pulse_values = np.empty((len(sigma_values), len(N_values)))
    for fname, params in tqdm(file_list.items()):
        data = np.loadtxt(fname)
        max_val = np.max(np.abs(data[:, 1]))
        max_val = max_val
        sigma_idx = sigma_values.index(float(params['sigma']))
        N_idx = N_values.index(int(params['width']))
        initial_pulse_values[sigma_idx, N_idx] = max_val
    return (initial_pulse_values, N_values, sigma_values)



def load_data(files):
    from collections import namedtuple
    from matplotlib.lines import Line2D

    initial_E_pulse_files = {k: v for k, v in files.items()
                             if v['time'] == '0' and v['type'] == 'Ey'}
    initial_H_pulse_files = {k: v for k, v in files.items()
                             if v['time'] == '0' and v['type'] == 'Hz'}
    reflected_E_pulse_files = {k: v for k, v in files.items()
                               if v['time'] == '12001' and v['type'] == 'Ey'}
    reflected_H_pulse_files = {k: v for k, v in files.items()
                               if v['time'] == '12001' and v['type'] == 'Hz'}

    PulseValues = namedtuple('PulseValues', ['values', 'width', 'sigma'])
    initial_E_pulse_values = PulseValues(*load_pulse_values(initial_E_pulse_files))
    # initial_H_pulse_values = PulseValues(*load_pulse_values(initial_H_pulse_files))

    reflected_E_pulse_values = PulseValues(*load_pulse_values(reflected_E_pulse_files))
    # reflected_H_pulse_values = PulseValues(*load_pulse_values(reflected_H_pulse_files))

    # plot reflection vs sigma
    pl.style.use('grayscale')
    linestyles = ['-', '--', ':','-.']
    markers = ('o', 'v', '^', '<', '>', '8', 's', 'p', '*', 'h', 'H', 'D', 'd')
    # for idx, slab_width in enumerate(initial_E_pulse_values.width):
    #     initial = initial_E_pulse_values.values[:, idx]
    #     reflected = reflected_E_pulse_values.values[:, idx]
    #     r_coeff = reflected / initial
    #     pl.plot(initial_E_pulse_values.sigma, r_coeff, label=r'$N='+str(slab_width)+'$')
    # pl.xlabel(r'$\sigma$')
    # pl.ylabel(r'$\max E_y^{reflected} / \max E_y^{incident}$')
    # pl.legend()
    # pl.grid()
    # pl.show()
    # plot reflection vs N
    for idx, slab_sigma in enumerate(initial_E_pulse_values.sigma):
        if idx not in [0, 1, 2, 4, len(initial_E_pulse_values.sigma)-1]:
            continue
        initial = initial_E_pulse_values.values[idx, :]
        reflected = reflected_E_pulse_values.values[idx, :]
        r_coeff = reflected / initial
        dt = 0.99999 * 5. / c / 1E-6
        slab_eta = 2 * pi * slab_sigma * dt
        pl.plot(initial_E_pulse_values.width, r_coeff,
                linestyles[idx%len(linestyles)],
                label=r'$\eta={:.3f}$'.format(slab_eta),
                marker=markers[idx%len(markers)],
                color='k')
    pl.xlabel(r'N (number of cells in slab)')
    pl.ylabel(r'$\max E_y^{reflected}/ \max E_y^{incident}$')
    pl.legend()
    pl.grid()
    pl.show()

if __name__ == "__main__":
    file_list = get_dat_files()
    # data = load_data(file_list)
    load_data(file_list)
    # r_vs_N = find_reflection_vs_slab_width(data)
    # r_vs_sigma = find_reflection_vs_consumption(data)
    # plot(r_vs_sigma, r_vs_N)
