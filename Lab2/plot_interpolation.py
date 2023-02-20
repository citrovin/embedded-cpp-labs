import sys
import os
import matplotlib. pyplot as plt

# Handle different path notations
def preprocess_path(path):
    return os.path.abspath(os.path.expanduser(path))

# Read data from file and return x and y arrays
def read_data(file_path):
    x = []
    y = []
    with open(file_path) as f:
        for line in f:
            data = line.strip().split(',')
            x.append(float(data[0]))
            y.append(float(data[1]))
    return x, y

# Plot data from two files in two separate subplots
def plot_data(file_path1, file_path2):
    file_path1 = preprocess_path(file_path1)
    file_path2 = preprocess_path(file_path2)
    x1, y1 = read_data(file_path1)
    x2, y2 = read_data(file_path2)

    plt.plot(x1, y1, 'ro-', label="Input points")
    plt.plot(x2, y2, 'bo-', label="Interpolated")

    plt.legend()

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    # Check if correct number of arguments are given
    if len(sys.argv) != 3:
        print("Error: Invalid number of arguments")
        print("Usage: python plot_data.py <file_path1> <file_path2>")
        sys.exit(1)

    # Call with command line arguments
    plot_data(sys.argv[1], sys.argv[2])
