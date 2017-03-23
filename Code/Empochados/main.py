import cv2
import numpy as np
import comparadorColores as cc
import InputImages as ii
path='/home/miguel/PycharmProjects/Empochados-master/cartas/'
cargar= ii.InputImages(path)
images=cargar.images()
for i in images:
    image = cv2.imread(path+i)
    imageStandard=cv2.resize(image,(493,755))
    image2= image[40:120,40:120]
    image3= cv2.cvtColor(image2,cv2.COLOR_BGR2GRAY)
    mini= image3.copy()
    mini2= cv2.resize(mini,(250,250))
    mser = cv2.MSER_create(_delta=8  )
    regions= mser.detectRegions(mini2,None)
    rect = [cv2.boundingRect(p) for p in regions]
    rectbuenos=[]
    for r in rect:
        if((r[2])<0.66*(r[3])):
            if(r[2]<1.4*image2.shape[0] and r[2]>0.5*image2.shape[0]):
                if (r[3]<1.4*image2.shape[1] and r[3]>0.5*image2.shape[1]):
                    rectbuenos.append(r)
    rectbuenos.sort()
    print(rectbuenos)
    rectOptimos=[]
    rectOptimos.append(rectbuenos[0])

    for rb in rectbuenos:
        changed = False
        posicionOptimos=0
        print("rb",rb)
        for rt in rectOptimos:
            if(rb[1]>=rt[1]+(rt[3]/5)):
                changed=True
                break
            if((rt[0]<=rb[0]<=rt[2]+rt[0])and(rt[1]<=rb[1]<=rt[3]+rt[1])):
                rectOptimos[posicionOptimos]=rb
                changed=True
                break
            posicionOptimos+=1
        if(not changed):
            rectOptimos.append(rb)
    print(len(rectOptimos))
    for r in rectOptimos:
        cv2.rectangle(mini2, (r[0], r[1]), (r[0] + r[2], r[1] + r[3]), (0, 255, 0))
    cv2.imshow('img', mini2)
    cv2.waitKey(0)

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
           
        #cv2.imshow("Colores", np.hstack([image,output]))
        #cv2.waitKey(0)
        i+=1
comparador = cc.comparadorColores(colorsPercentaje)
print (colorsPercentaje)
print (comparador.palo())

        

        
