import cv2
import numpy as np

image = cv2.imread('/home/dropelega/Empotrados/Empochados/Test/as-de-oros.jpg')
#cv2.imshow('P',image)
#cv2.waitKey()

# define the list of range colors
rcolors = [
    ([0, 0, 100], [100 , 100, 255]), #red
    ([86, 31, 4], [255, 155, 139]), #blue
    ([25, 160, 200], [63, 250, 244]), #yellow
    ([5, 73, 0], [80, 255,120]) #green
]

for (lower, upper) in rcolors:
        lower = np.array(lower, dtype = "uint8")
        upper = np.array(upper, dtype= "uint8")
        
        mask = cv2.inRange(image, lower, upper)
        output = cv2.bitwise_and(image, image, mask=mask)
        
        cv2.imshow("Colores", np.hstack([image,output]))
        cv2.waitKey(0) 
        