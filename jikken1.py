import subprocess
with open("log.csv", "w") as log_file:
    log_file.write("N,P_N,Success\n")

for pat_num in range(1, 200):
    print(f"Running for pattern number: {pat_num}")
    subprocess.run(["./build/hopfield", "25", str(pat_num), "1000", "0.2"])