import matplotlib.pyplot as plt
import numpy as np

# LOFにより、生成した出力ファイルのパス
file_path = "two_islandlof.csv"
data = np.loadtxt(file_path, delimiter=',')

# データから x、y、LOF スコアを抽出
x = data[:, 0]
y = data[:, 1]
lof_scores = data[:, 2]

# 外れ値検出の閾値を設定
threshold = 1.3

# 外れ値でないデータの色
inlier_color = 'blue'

# 外れ値でないデータを青で表示
inliers = np.where(lof_scores <= threshold)[0]
plt.scatter(x[inliers], y[inliers], c=inlier_color, s=40, edgecolors='k')

# 閾値を超える外れ値を赤でハイライト
outliers = np.where(lof_scores > threshold)[0]
plt.scatter(x[outliers], y[outliers], c='red', s=40, edgecolors='k')

plt.title('Local Outlier Factor')
plt.xlabel('X')
plt.ylabel('Y')

# ラベルを非表示にする
plt.legend().set_visible(False)

plt.show()


