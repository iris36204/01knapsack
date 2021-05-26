# 導入函式庫
import numpy as np  
from keras.models import Sequential
from keras.datasets import mnist
from keras.layers import Dense, Dropout, Activation, Flatten
from keras.utils import np_utils  # 用來將 label 標籤轉為 one-hot-encoding  
from matplotlib import pyplot as plt

#加載數據
# 載入 MNIST 資料庫的訓練資料，分為訓練組 及 測試組
(X_train, y_train), (X_test, y_test) = mnist.load_data()

# 將 training 的 label 進行 one-hot encoding , 代表圖片裡的數字是多少
y_TrainOneHot = np_utils.to_categorical(y_train) 
y_TestOneHot = np_utils.to_categorical(y_test) 

#reshape data to have a single channel
#將 training 的 input 資料轉為2維
X_train_2D = X_train.reshape(60000, 28*28).astype('float32')  
X_test_2D = X_test.reshape(10000, 28*28).astype('float32')  
# normalize pixel values
x_Train_norm = X_train_2D/255.0
x_Test_norm = X_test_2D/255.0

#定義模型
#建立簡單的線性執行的模型
model = Sequential()
# Add Input layer, (第一個)隱藏層(hidden layer) 有 256個輸出變數 , 784個輸入參數
model.add(Dense(256, input_dim=784, kernel_initializer='normal', activation='relu')) 
# Add output layer, 輸出層10個節點(0~9)
model.add(Dense(10, kernel_initializer='normal', activation='softmax'))

#編譯模型
# 編譯: 選擇損失函數、優化方法及成效衡量方式
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy']) 

#適合函數
#進行訓練, 訓練過程會存在 train_history 變數中
train_history = model.fit(x=x_Train_norm, y=y_TrainOneHot, validation_split=0.2, epochs=10, batch_size=800, verbose=2)  

#評估
scores = model.evaluate(x_Test_norm, y_TestOneHot)  
print()  
print("[Info] Accuracy of testing data = {:2.1f}%".format(scores[1]*100.0))  
print()

#預測
X = x_Test_norm[0:10,:]
predictions = np.argmax(model.predict(X), axis=-1)
print(predictions)
