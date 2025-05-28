
import subprocess

with open("log.csv", "w") as log_file:
    log_file.write("N,P_N,Success\n")

for pat_num in range(1, 25):
    for i in range(1000):
        subprocess.run(["./build/hopfield", "25", str(pat_num)])