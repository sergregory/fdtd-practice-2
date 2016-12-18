def get_wave_freq(wave_len):
    from scipy.constants import pi, c
    # we need speed of light in nm/fs, so multiply by 1E-6
    return 2 * pi * c * 1E-6 / wave_len


def get_sigma(wave_len):
    return 2 * get_wave_freq(wave_len)


def run_simulation(param):
    from subprocess import call
    sigma, N = param[:]
    tag = "e1E0_s{:E}_N{:d}".format(sigma, N)
    call("/home/grigory/dev/fdtd-practice/_build/fdtd_1d " + str(sigma) + " " + str(N) + " " + tag, shell=True)


def main():
    from multiprocessing import Pool
    from itertools import product
    import numpy as np

    np.random.seed(0)

    n_values = np.arange(10, 700, 100)
    sigma_values = np.arange(0.01, 0.1, 0.01)

    # sigma_values = np.random.uniform(sigma_range[0], sigma_range[1], 10)
    # n_values = np.random.randint(N_range[0], N_range[1], 10)

    print(sigma_values)
    print(n_values)

    params = product(sigma_values, n_values)
    with Pool() as pool:
        pool.map(run_simulation, params)


if __name__ == '__main__':
    main()
