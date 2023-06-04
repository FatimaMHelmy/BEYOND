# BEYOND_TASKS


## TASK_3 ||Home Made Sobel 

#**Code Explanation**

- The SobelEdgeDetector class represents the edge detection algorithm.

- The constructor takes the path to the input image and loads it using the OpenCV imread function.

- The vertical and horizontal Sobel filter matrices are manually defined.
- 
- The detectEdges method performs the edge detection process. It applies image smoothing using Gaussian blur, calculates the gradients using the Sobel filters, and computes the edge magnitude.

- The applyGaussianBlur method applies Gaussian blur to the input image using the OpenCV GaussianBlur function and Sharpening. || it's optional for high performance 

- The showEdgeImage method displays the original image and the filtered images side by side using OpenCV's imshow function.

## the result after applying bluring it is not suitable for all images 

![image](https://github.com/FatimaMHelmy/BEYOND/assets/84232181/58dbe414-2e8c-438a-bac4-d7fe3dc8645d)

![image](https://github.com/FatimaMHelmy/BEYOND/assets/84232181/1b673bb3-ee86-481e-96b2-fc4f0d710f48)

##  the result without any smoothing 

![image](https://github.com/FatimaMHelmy/BEYOND/assets/84232181/10793730-1732-4a35-8b6c-080bc2e08300)


