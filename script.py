
import subprocess

with open("log.csv", "w") as log_file:
    log_file.write("N,P_N,Success\n")

for pat_num in range(1, 25):
    print(f"Running for pattern number: {pat_num}")
    for i in range(1000):
        print(f"\rIteration: {i + 1}", end=" ")
        subprocess.run(["./build/hopfield", "25", str(pat_num)])
