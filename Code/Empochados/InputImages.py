import os



class InputImages:
    def __init__(self, path):
        self.path = path

    def images(self):
        images = []
        for dirname, dirnames, filenames in os.walk(self.path):
            for file in filenames:
               images.append(file)
        return images