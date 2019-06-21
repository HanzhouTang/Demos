'''
Convert pixel image to ascii image. 
Based on Spektre's solution on https://stackoverflow.com/questions/32987103/image-to-ascii-art-conversion/32987834#32987834
'''
__author__ = 'Hanzhou Tang'
__email__ = 'hanzhoutang@gmail.com'
import cv2 as cv
import numpy as np
 
img = cv.imread("tmp.jpg",0)

def convert_to_ascii_compress(img,row_step = 3, column_step = 3):
    chars = " .,:;ox%#@"
    m = len(img)
    n = len(img[0])
    ret = ''
    i = 0 
    while i < m:
        j = 0 
        while j < n:
            v = np.mean(img[i:i + row_step, j:j + column_step])
            v = int(v)
            ret += chars[(255 - v)*10//256]
            j += column_step
        ret += '\n'
        i += row_step 
    return ret 

tmp = convert_to_ascii_compress(img)
with open('out.txt','w') as f:
    f.write(tmp)