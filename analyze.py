import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# CSVファイルを読み込む
csv_file = 'log.csv'
data = pd.read_csv(csv_file) # ヘッダーがない場合は、名前を明示的に指定

# Successが1のデータをフィルタリング
success_data = data[data['Success'] == 1]

# P_Nで分類して行数をカウント
counts = success_data['P_N'].value_counts() # P_Nの順にソートして表示

print("Success counts by Pattern num:")
print(counts)

# --- プロット部分 ---
plt.figure(figsize=(10, 6)) # グラフのサイズを設定

# 棒グラフを作成
sns.barplot(x=counts.index, y=counts.values, palette='viridis')
# plt.scatter(counts.index.astype(int), counts.values, marker='o', s=5)

plt.title('Number of Successful Trials by Pattern num') # グラフのタイトル
plt.xlabel('Pattern num Value') # X軸のラベル
plt.ylabel('Number of Successes') # Y軸のラベル
x_labels = counts.index.astype(int)
tick_labels = [x for x in x_labels if x % 2 == 0]
plt.xticks(tick_labels)
plt.grid(axis='y', linestyle='--', alpha=0.7) # Y軸にグリッド線を追加
plt.tight_layout() # レイアウトを調整
plt.show() # グラフを表示