import pandas as pd
import matplotlib.pyplot as plt

# CSVファイル読み込み
#k-meansにより、生成したファイル名
df = pd.read_csv('two_islandout.csv', header=None, names=['X', 'Y', 'Cluster'])

# クラスタごとにデータを分割
clusters = df.groupby('Cluster')

# プロット
plt.figure(figsize=(8, 6))

# 各クラスタごとに散布図をプロット
for name, group in clusters:
    plt.scatter(group['X'], group['Y'])

# クラスタの重心を描画
for name, group in clusters:
    plt.scatter(group['X'].mean(), group['Y'].mean(), marker='x', s=200, color='black')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('K-means Clustering')
plt.show()

