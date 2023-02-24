# -*- coding: utf-8 -*-
"""
Created on Wed Jun 29 03:46:17 2022

@author: faias Motachoda
"""
import numpy as np
import matplotlib.pyplot as plt
import cv2
path = 'C://Users//faias//Desktop//CSE 4-1//Lab//Image//Lab 4//period_input.jpg'
img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
plt.imshow(cv2.cvtColor(img,cv2.COLOR_BGR2RGB))
plt.show()
f = np.float32(img)
F = np.float32(img)
F = np.fft.fft2(img)
f=f+1
f = np.log(f)
f = np.fft.fft2(f)
f = np.fft.fftshift(f)
plt.imshow(np.log(np.abs(f)),'gray')
plt.show()
index = 0
X = np.zeros(100)
Y = np.zeros(100)
def click_event(event, x, y, flags, params):
 
    # checking for left mouse clicks
    global index
    global X
    global Y
    if event == cv2.EVENT_LBUTTONDOWN:
 
    # displaying the coordinates
    # on the Shell
    
        print(x, ' ', y)
        np.append(X, x, axis=None)
        Y[index] = y
        X[index] = x
        index=index+1
        # displaying the coordinates
        # on the image window
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(img, str(x) + ',' +
                    str(y), (x,y), font,
                    1, (255, 0, 0), 2)
        cv2.imshow('image', img)
            
 
    # checking for right mouse clicks    
    if event==cv2.EVENT_RBUTTONDOWN:
 
        # displaying the coordinates
        # on the Shell
        print(x, ' ', y)
        
 
        # displaying the coordinates
        # on the image window
        font = cv2.FONT_HERSHEY_SIMPLEX
        b = img[y, x, 0]
        g = img[y, x, 1]
        r = img[y, x, 2]
        cv2.putText(img, str(b) + ',' +
                    str(g) + ',' + str(r),
                    (x,y), font, 1,
                    (255, 255, 0), 2)
        cv2.imshow('image', img)
 


 	
img = cv2.imread(path, cv2.COLOR_RGB2BGR)
# gray = cv2.cvtColor(gray, cv2.COLOR_RGB2GRAY)

cv2.imshow('image', img)   
cv2.setMouseCallback('image', click_event)  
cv2.waitKey(0) 
cv2.destroyAllWindows()
M,N = img.shape
print(X)
filterr = np.zeros((img.shape),np.float32)
for i in range(M):
    for j in range(N):
        filterr[i][j] = 255.0
m = M//2
n = N//2     
D0 = 25
center_x = M//2
center_y = N//2
for i in range(M):
    for j in range(N):
        distance = np.zeros(index)
        distance_negative = np.zeros(index)
        final = 1
        for k in range(index):
            distance[k] = np.sqrt((i-m-(Y[k]-m))**2 + ((j-n-(X[k]-n))**2 ))
            distance_negative[k] = np.sqrt((i-m+(Y[k]-m))**2 + ((j-n+(X[k]-n))**2 ))
            value1 = 1/(1+(D0/distance[k]**2)) 
            value2 = 1/(1+(D0/distance_negative[k]**2)) 
            value = value1*value2
            final*=value
        for k in range(index):
            if(distance[k]<=D0 or distance_negative[k]<=D0):
                filterr[i][j] = final
                break
# distance = np.zeros(i)
# distance_negative = np.zeros(i)              
# for j in range (M):
#     for k in range (N):
#         final = 1
#         for l in range (index):
#             distance[l] = np.sqrt((j-center_x-(Y[l]-center_x))**2 + (k-center_y-(X[l]-center_y))**2)
#             distance_negative[l] = np.sqrt((j-center_x+(Y[l]-center_x))**2 + (k-center_y+(X[l]-center_y))**2)
#             value=(1/(1+(D0/distance[l])**(2*1)))* (1/(1+(D0/distance_negative[l])**(2*1)))
#             final *= value
#         for l in range (index):
#             if(distance[l] <= D0 or distance_negative[l]<=D0) :
#                 filterr[j][k] = 0
                
#                 break
plt.imshow(filterr,'gray')
plt.show()
img_f2 = np.zeros((img.shape),np.float64)

print('filter',f)
img_f2 = np.multiply(F,filterr)
f_show=np.fft.fftshift(np.log(np.abs(img_f2)+1))
f_show = np.fft.ifft2(f_show)
plt.imshow(f_show, "gray")

plt.title("Image magnitude")

plt.show()
print('image f2',img_f2)
img_f = np.zeros((img.shape),np.float64)
img_g = np.zeros((img.shape),np.float64)

# img_f2  = f*h
img_f = np.fft.ifftshift(img_f2)
img_f = np.fft.ifft2(img_f)
img_g = np.exp(np.abs(img_f))-1

print('output_image',img_g)
plt.imshow(np.log(np.abs(img_g)), "gray")


plt.show()
        