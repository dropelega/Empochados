from __future__ import division
class comparadorColores:
    def __init__(self, colores):
            self.colores = colores
    def paloNormales(self):
        #Obtenemos el numero de pixeles del color de mayor cantidad en la imagen
        mayor = self.colores[0]
        for color in self.colores:
            if color > mayor:
                mayor = color
            
        #Sacamos "proporcion" de colores
        i=0
        proporcion = [0,0,0,0]
        for color in self.colores:
            proporcion[i] = color / mayor
            i+=1
        print (proporcion)
        #Decidimos a que palo pertenece la carta en caso de las "proporciones"
        if proporcion[1] ==1:
            return "Espadas"
        if proporcion[2] == 1 and proporcion[0]>0.2 and proporcion[3]<0.56:
            return "Oros" 
        if proporcion[0]==1 and proporcion[2]>0.2 and proporcion[3]<0.56:
            return "Copas"
        return "Bastos"

    def paloFiguras(self):
        #Obtenemos el numero de pixeles del color de mayor cantidad en la imagen
        mayor = self.colores[0]
        for color in self.colores:
            if color > mayor:
                mayor = color
        i = 0
        proporcion = [0, 0, 0, 0]
        for color in self.colores:
            proporcion[i] = color / mayor
            i += 1
        print(proporcion)
        if proporcion[1]==1:
            return "Espadas"
        if proporcion[2] == 1 and proporcion[0] < 0.5 and proporcion[3] < 0.85:
            return "Oros"
        if proporcion[0]==1 and proporcion[1]>0.4 and proporcion[3]<0.85:
            return "Copas"
        return "Bastos"
        
        