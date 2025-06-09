import pandas as pd
import matplotlib.pyplot as plt

# CSVファイルの読み込み
df = pd.read_csv('log.csv')

# P_Nごとにsの平均を計算
grouped = df.groupby('P_N')['s'].mean().reset_index()

# プロット
plt.figure()
plt.scatter(grouped['P_N'], grouped['s'], marker='o', s=3)
plt.xlabel('Pattern num')
plt.ylabel('Similarity')
plt.title('Average Similarity by Pattern num')
plt.show()
