# %% [markdown]
# #Importing Required Libraries

# %%
import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import math

# %% [markdown]
# #Setting Image Path and Loading the Image

# %%
path = "./images/download.jpg"
input_img = cv.imread(path, cv.IMREAD_GRAYSCALE)
plt.imshow(input_img,"gray")

# %% [markdown]
# #Convolution

# %%
def conv(kernel_size,filter):
    output = np.zeros((input_img.shape[0], input_img.shape[1]), np.float32)
    mimg = cv.copyMakeBorder(input_img,kernel_size, kernel_size, kernel_size, kernel_size, cv.BORDER_REPLICATE)
    for i in range(2*kernel_size, mimg.shape[0]):
        for j in range(2*kernel_size,mimg.shape[1]):
            sum = 0
            for p in range(-kernel_size, kernel_size+1):
                for q in range(-kernel_size, kernel_size+1):
                    sum+=mimg[i-(p+kernel_size)][j-(q+kernel_size)]*filter[p+kernel_size][q+kernel_size]
            output[i-(2*kernel_size)][j-(2*kernel_size)] = sum
    
    return output
    

# %% [markdown]
# #GAUSSIAN KERNEL

# %%
def gaussian_kernel():
    kernel_size = int(input("Enter kernel Size: "))
    kernel_size = kernel_size//2
    sigma = 0.3*((kernel_size-1)*0.5-1)+0.8
    sigma = sigma*3 
    gf = np.zeros((2*kernel_size+1, 2*kernel_size+1), np.float32)

    for i in range(-kernel_size, kernel_size+1):
        for j in range (-kernel_size, kernel_size+1):
            gf[i+kernel_size][j+kernel_size]=np.exp(-(pow(i,2)+pow(j,2))/(2*pow(sigma,2)))
    return gf, kernel_size

# %% [markdown]
# #Laplacian Kernel with positive center

# %%
def laplacian_kernelp():
    lf = [[0,-1,0],[-1,4,-1],[0,-1,0]]
    return lf


# %% [markdown]
# #Laplacian Kernel with negative center

# %%
def laplacian_kerneln():
    lf = [[0,1,0],[1,-4,1],[0,1,0]]
    return lf

# %% [markdown]
# #Horizontal Sobel Kernel

# %%
def horizontal_sobel_kernel(kernel_size: int):
    
    row_value = [[0 for i in range(kernel_size)] for j in range(1)]
    col_value = [[1 for i in range(1)] for j in range(kernel_size)]
    center = kernel_size//2
    col_value[center][0] = 2
    for i in range(1):
        for j in range(kernel_size):
            row_value[i][j]=center
            center-=1
    horizontal_sobel_kernel = [[0 for i in range(kernel_size)] for j in range(kernel_size)]
    horizontal_sobel_kernel = np.matmul(col_value, row_value)
    return horizontal_sobel_kernel


# %% [markdown]
# #Vertical Sobel Kernel

# %%
def vertical_sobel_kernel(kernel_size: int):
    
    col_value = [[0 for i in range(1)] for j in range(kernel_size)]
    row_value = [[1 for i in range(kernel_size)] for j in range(1)]
    center = kernel_size//2
    row_value[0][center]=2
    for i in range(kernel_size):
        for j in range(1):
            col_value[i][j]=center
            center-=1
    vertical_sobel_kernel = [[0 for i in range(kernel_size)] for j in range(kernel_size)]
    vertical_sobel_kernel = np.matmul(col_value, row_value)
    return vertical_sobel_kernel


# %% [markdown]
# #Horizontal Schar Kernel

# %%
def horizontal_scharr_kernel():
    horizontal_schar_kernel = [[3,0,-3],[10,0,-10],[3,0,-3]]
    return horizontal_schar_kernel

# %% [markdown]
# #Vertical Schar Kernel

# %%
def vertical_scharr_kernel():
    vertical_schar_kernel = [[3,10,3],[0,0,0],[-3,-10,-3]]
    return vertical_schar_kernel

# %% [markdown]
# #Horizontal Prewitt Kernel

# %%
def horizontal_prewitt_kernel():
    horizontal_prewitt_kernel = [[1,0,-1],[1,0,-1],[1,0,-1]]
    return horizontal_prewitt_kernel

# %% [markdown]
# #Vertical Prewitt Kernel

# %%
def vertical_prewitt_kernel():
    vertical_prewitt_kernel = [[1,1,1],[0,0,0],[-1,-1,-1]]
    return vertical_prewitt_kernel

# %% [markdown]
# #Vertical Roberts Kernel

# %%
def vertical_roberts_kernel():
    vertical_roberts_kernel = [[0,0,0],[0,0,1],[0,-1,0]]
    return vertical_roberts_kernel

# %% [markdown]
# #Horizontal Roberts Kernel

# %%
def horizontal_roberts_kernel():
    horizontal_roberts_kernel = [[0,0,0],[0,1,0],[0,0,-1]]
    return horizontal_roberts_kernel

# %% [markdown]
# #Applying Gaussian Filter 

# %%
kernel, kernel_size = gaussian_kernel()
output  = conv(kernel_size, kernel)
figure, (axis_1, axis_2) = plt.subplots(1,2, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(output, "gray")
axis_2.set_title("Output Image")

# %% [markdown]
# #Applying Laplacian Filter with positive center and negative center

# %%
kernel = laplacian_kernelp()
kernel = np.array(kernel)
outputp = conv(kernel.shape[0]//2, kernel)

kernel = laplacian_kerneln()
kernel = np.array(kernel)
outputn=conv(kernel.shape[0]//2, kernel)


figure, (axis_1, axis_2, axis_3) = plt.subplots(1,3, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(outputp, "gray")
axis_2.set_title("Output with positive center")
axis_3.imshow(outputn, "gray")
axis_3.set_title("Output with negative center")



# %% [markdown]
# #Applying Mean Filter

# %%
kernel_size = int(input("Enter Kernel Size: "))
kernel = np.ones((kernel_size, kernel_size), np.float32)
kernel_size=kernel_size//2
output = np.zeros((input_img.shape[0], input_img.shape[1]), np.float32)
norm = kernel.sum()
mimg = cv.copyMakeBorder(input_img,kernel_size, kernel_size, kernel_size, kernel_size, cv.BORDER_REPLICATE)
for i in range(2*kernel_size, mimg.shape[0]):
    for j in range(2*kernel_size,mimg.shape[1]):
        sum = 0
        for p in range(-kernel_size, kernel_size+1):
            for q in range(-kernel_size, kernel_size+1):
                sum+=mimg[i-(p+kernel_size)][j-(q+kernel_size)]*kernel[p+kernel_size][q+kernel_size]
        output[i-(2*kernel_size)][j-(2*kernel_size)] = sum
output/=norm
figure, (axis_1, axis_2) = plt.subplots(1,2, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(output, "gray")
axis_2.set_title("Output Image")

# %% [markdown]
# #Applying Median Filter

# %%
kernel_size = int(input("Enter Kernel Size: "))
kernel = np.ones((kernel_size, kernel_size), np.float32)

kernel_size=kernel_size//2
total = kernel_size*kernel_size
mimg = cv.copyMakeBorder(input_img,kernel_size, kernel_size, kernel_size, kernel_size, cv.BORDER_REPLICATE)

output = np.zeros((input_img.shape[0], input_img.shape[1]), np.float32)
for i in range(2*kernel_size, mimg.shape[0]):
    for j in range(2*kernel_size,mimg.shape[1]):
        values = []
        for p in range(-kernel_size, kernel_size+1):
            for q in range(-kernel_size, kernel_size+1):
                values.append(mimg[i-(p+kernel_size)][j-(q+kernel_size)]*kernel[p+kernel_size][q+kernel_size])
        values.sort()
        median = len(values)//2
        output[i-(2*kernel_size)][j-(2*kernel_size)] = values[median]/total


figure, (axis_1, axis_2) = plt.subplots(1,2, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(output, "gray")
axis_2.set_title("Output Image")

# %% [markdown]
# #Applying Sobel Filter

# %%
kernel_size = int(input("Enter Kernel Size"))
kernel = horizontal_sobel_kernel(kernel_size)
kernel = np.array(kernel)

h = conv(kernel_size//2, kernel)


kernel = vertical_sobel_kernel(kernel_size)
kernel = np.array(kernel)

v = conv(kernel_size//2, kernel)

output = np.zeros((v.shape[0], v.shape[1]), np.float32)
#gradient Magnitude
for i in range(v.shape[0]):
    for j in range(v.shape[1]):
        output[i][j] = np.sqrt(pow(h[i][j],2)+pow(v[i][j],2))


figure, (axis_1, axis_2, axis_3, axis_4) = plt.subplots(1,4, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(h, "gray")
axis_2.set_title("Horizontally Filtered")
axis_3.imshow(v, "gray")
axis_3.set_title("Vertically Filtered")
axis_4.imshow(output, "gray")
axis_4.set_title("Output Image(Merged)")

# %% [markdown]
# #Applying Scharr Filter

# %%
kernel = horizontal_scharr_kernel()
kernel = np.array(kernel)
h = conv(kernel.shape[0]//2, kernel)

kernel = vertical_scharr_kernel()
kernel = np.array(kernel)
v = conv(kernel.shape[0]//2, kernel)

output = np.zeros((v.shape[0], v.shape[1]), np.float32)
#gradient Magnitude
for i in range(v.shape[0]):
    for j in range(v.shape[1]):
        output[i][j] = np.sqrt(pow(h[i][j],2)+pow(v[i][j],2))

figure, (axis_1, axis_2, axis_3, axis_4) = plt.subplots(1,4, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(h, "gray")
axis_2.set_title("Horizontally Filtered")
axis_3.imshow(v, "gray")
axis_3.set_title("Vertically Filtered")
axis_4.imshow(output, "gray")
axis_4.set_title("Output Image(Merged)")

# %% [markdown]
# #Applying Prewitt Filter

# %%
kernel = horizontal_prewitt_kernel()
kernel = np.array(kernel)
h = conv(kernel.shape[0]//2, kernel)

kernel = vertical_prewitt_kernel()
kernel = np.array(kernel)
v = conv(kernel.shape[0]//2, kernel)

output = np.zeros((v.shape[0], v.shape[1]), np.float32)
#gradient Magnitude
for i in range(v.shape[0]):
    for j in range(v.shape[1]):
        output[i][j] = np.sqrt(pow(h[i][j],2)+pow(v[i][j],2))

figure, (axis_1, axis_2, axis_3, axis_4) = plt.subplots(1,4, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(h, "gray")
axis_2.set_title("Horizontally Filtered")
axis_3.imshow(v, "gray")
axis_3.set_title("Vertically Filtered")
axis_4.imshow(output, "gray")
axis_4.set_title("Output Image(Merged)")

# %% [markdown]
# #Applying Robert's Filter

# %%
kernel = horizontal_roberts_kernel()
kernel = np.array(kernel)
h = conv(kernel.shape[0]//2, kernel)

kernel = vertical_roberts_kernel()
kernel = np.array(kernel)
v = conv(kernel.shape[0]//2, kernel)

output = np.zeros((v.shape[0], v.shape[1]), np.float32)
#gradient Magnitude
for i in range(v.shape[0]):
    for j in range(v.shape[1]):
        output[i][j] = np.sqrt(pow(h[i][j],2)+pow(v[i][j],2))

figure, (axis_1, axis_2, axis_3, axis_4) = plt.subplots(1,4, figsize=(12,12))
axis_1.imshow(input_img, "gray")
axis_1.set_title("Input Image")
axis_2.imshow(h, "gray")
axis_2.set_title("Horizontally Filtered")
axis_3.imshow(v, "gray")
axis_3.set_title("Vertically Filtered")
axis_4.imshow(output, "gray")
axis_4.set_title("Output Image(Merged)")


