import cv2
import numpy as np
import comparadorColores as cc
image = cv2.imread('/home/dropelega/Empotrados/Empochados/Test/rey-de-oros.jpg')
#cv2.imshow('P',image)
#cv2.waitKey()
 
# define the list of range colors
rcolors = [
    ([0, 0, 100], [110 , 110, 255]), #red
    ([86, 31, 4], [255, 180, 180]), #blue
    ([25, 120, 150], [90, 255, 255]), #yellow
    ([5, 73, 0], [80, 255,150]) #green
]
i=0
colorsPercentaje = [0,0,0,0]
for (lower, upper) in rcolors:
        lower = np.array(lower, dtype = "uint8")
        upper = np.array(upper, dtype= "uint8")
        
        mask = cv2.inRange(image, lower, upper)
        output = cv2.bitwise_and(image, image, mask=mask)
        for column in output:
            for color in column:
             
                if color[0]!=0 or color[1]!=0 or color[2]!=0:
                    colorsPercentaje[i]+=1
           
        cv2.imshow("Colores", np.hstack([image,output]))
        cv2.waitKey(0) 
        i+=1
comparador = cc.comparadorColores(colorsPercentaje)
print colorsPercentaje
print comparador.palo()
        

        