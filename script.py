
import subprocess

for pat_num in range(1, 10):
    for i in range(1000):
        subprocess.run(["./build/hopfield", "25", str(pat_num)])