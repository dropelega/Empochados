import cv2
class detectorNumeros:
    def __init__(self,path):
        self.image=cv2.imread(path)
    def deteccionNumero(self):
        image2 = self.image[40:120, 40:120]
        image3 = cv2.cvtColor(image2, cv2.COLOR_BGR2GRAY)
        mini = image3.copy()
        mini2 = cv2.resize(mini, (250, 250))
        mser = cv2.MSER_create(_delta=8)
        regions = mser.detectRegions(mini2, None)
        rect = [cv2.boundingRect(p) for p in regions]
        rectbuenos = []
        for r in rect:
            if ((r[2]) < 0.66 * (r[3])):
                if (r[2] < 1.4 * image2.shape[0] and r[2] > 0.5 * image2.shape[0]):
                    if (r[3] < 1.4 * image2.shape[1] and r[3] > 0.5 * image2.shape[1]):
                        rectbuenos.append(r)
        rectbuenos.sort()
        rectOptimos = []
        rectOptimos.append(rectbuenos[0])

        for rb in rectbuenos:
            changed = False
            posicionOptimos = 0
            for rt in rectOptimos:
                if (rb[1] >= rt[1] + (rt[3] / 5)):
                    changed = True
                    break
                if ((rt[0] <= rb[0] <= rt[2] + rt[0]) and (rt[1] <= rb[1] <= rt[3] + rt[1])):
                    rectOptimos[posicionOptimos] = rb
                    changed = True
                    break
                posicionOptimos += 1
            if (not changed):
                rectOptimos.append(rb)
        for r in rectOptimos:
            cv2.rectangle(mini2, (r[0], r[1]), (r[0] + r[2], r[1] + r[3]), (0, 255, 0))
        return (len(rectOptimos), r[2]/r[3])
