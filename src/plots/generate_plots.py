import os
import matplotlib.pyplot as plt

def read_data(directory):
    data = {}
    for type in ['openmp', 'threads']:
        type_dir = os.path.join(directory, 'time', type)
        for threads_dir in os.listdir(type_dir):
            thread_count = int(threads_dir)
            for file in os.listdir(os.path.join(type_dir, threads_dir)):
                test_name = '_'.join(file.split('_')[:-1])  # Extract test name without thread number and extension
                if test_name not in data:
                    data[test_name] = {'openmp': {}, 'threads': {}}
                with open(os.path.join(type_dir, threads_dir, file), 'r') as f:
                    for line in f:
                        if line.startswith('time spent on methods:'):
                            time = int(line.split(':')[1].strip())
                            data[test_name][type][thread_count] = time
                            break
    return data

def plot_and_save_data(data, base_directory):
    plots_directory = os.path.join(base_directory, 'plots')
    os.makedirs(plots_directory, exist_ok=True)

    for test_name in data:
        plt.figure()
        for type in ['openmp', 'threads']:
            thread_counts = sorted(data[test_name][type].keys())
            times = [data[test_name][type][tc] for tc in thread_counts]
            if type == 'threads':
                plt.plot(thread_counts, times, marker='o', label="power_opt")
            else:
                plt.plot(thread_counts, times, marker='o', label=type.title())

        plt.xlabel('Number of Threads')
        plt.ylabel('Time Consumption (ms)')
        plt.title(f'Test: {test_name}')
        plt.xticks([1, 4, 8, 16, 32, 64])
        plt.legend()
        plt.ylim(bottom=0)

        plot_file_name = f'{test_name}.png'
        plt.savefig(os.path.join(plots_directory, plot_file_name))
        plt.close()

directory = './../../tests/'
data = read_data(directory)
plot_and_save_data(data, directory)
