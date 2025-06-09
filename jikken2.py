import subprocess
with open("log.csv", "w") as log_file:
    log_file.write("N,P_N,Success,s,noise\n")

for noise in range(0, 100):
    print(f"Running for noise level: {noise/100:.2f}")
    subprocess.run(["./build/hopfield", "25", "2", "1000", str(noise/100)])