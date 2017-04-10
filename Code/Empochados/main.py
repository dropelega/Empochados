import cv2
import numpy as np
import comparadorColores as cc
import InputImages as ii
import detectorNumeros as dn
import serial
path='/home/miguel/Empochados/cartas/'
cargar= ii.InputImages(path)
images=cargar.images()
pathcompleto=path+"11_de_oros.jpeg"
#cv2.imshow('P',image)
#cv2.waitKey()
# define the list of range colors

ser = serial.Serial('/dev/ttyUSB0', 9600)
detector = dn.detectorNumeros(pathcompleto)
numeroRectangulos,ratio = detector.deteccionNumero()
rcolors = [
    ([0, 0, 100], [110 , 110, 255]), #red
    ([86, 31, 31], [255, 210, 170]), #blue
    ([25, 160, 120], [140, 235, 245]), #yellow
    ([60, 110, 60], [130, 255,230]) #green
]
colorsPercentaje = [0,0,0,0]
while(1):
    i = 0
    image = cv2.imread(pathcompleto)
    if(ser.read()=="p"):
        if(numeroRectangulos>1):
            shape=image.shape
            image=image[0:int(shape[0]/4),0:int(shape[1]/2.2)]
        for (lower, upper) in rcolors:
                lower = np.array(lower, dtype = "uint8")
                upper = np.array(upper, dtype= "uint8")

                mask = cv2.inRange(image, lower, upper)
                output = cv2.bitwise_and(image, image, mask=mask)
                for column in output:
                    for color in column:

                        if color[0]!=0 or color[1]!=0 or color[2]!=0:
                            colorsPercentaje[i]+=1
                #cv2.imshow("Colores", np.hstack([image,output]))
                #cv2.waitKey(0)
                i+=1
        comparador = cc.comparadorColores(colorsPercentaje)
        if(numeroRectangulos==1):
            if(ratio<0.45):
                ser.write(comparador.paloAs())
            else:
                ser.write(comparador.paloNormales())
        else:

           ser.write(comparador.paloFiguras())


