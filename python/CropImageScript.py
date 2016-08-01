#coding:utf-8
# 2016 7.30 author:windgodvc
import os
import sys
#from PIL import Image 
sys.path.append('/usr/local/Cellar/pyqt/4.11.4/lib/python2.7/site-packages')

from PyQt4.QtCore import *
from PyQt4.QtGui import *

reslist = []
maskfile = ""
def getDirFile(filepath):
    #遍历filepath下所有文件，包括子目录
    files = os.listdir(filepath)
    for fi in files:
      fi_d = os.path.join(filepath,fi)
      if os.path.isdir(fi_d):
        getDirFile(fi_d)
      else:
        reslist.append(os.path.join(filepath,fi_d))


def cropImage(filepath,qsize):
  #image = Image.open(filepath)
  #image = image.resize(qsize,Image.BILINEAR)
  #image.save(filepath)
  image = QImage(filepath)
  image = image.scaled(qsize[0],qsize[1],Qt.IgnoreAspectRatio,Qt.SmoothTransformation);
  image.save(filepath);


def main(dir,qsize,type):
  getDirFile(dir)
  if type == 0:
    for it in reslist:
      if it.find(".png") != -1 or it.find(".jpg") != -1 or it.find(".bmp") != -1:
        cropImage(it,qsize)
        print (it)
    print "裁剪完成"
  elif type == 1:
    for it in reslist:
      if it.find(".png") != -1 or it.find(".jpg") != -1 or it.find(".bmp") != -1:
        CircleRectImage(it,maskfile)
    print "添加圆四角完成"

def CircleRectImage(file,Mask):
    image = QImage()
    image.load(file)
    resultImage = QImage(head.rect().size(),QImage.Format_ARGB32)
    maskImage = QImage(Mask)
    painter = QPainter(resultImage);
    painter.setCompositionMode(QPainter.CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt.transparent);
    painter.setCompositionMode(QPainter.CompositionMode_SourceOver);
    painter.drawImage(0, 0, maskImage);
    painter.setCompositionMode(QPainter.CompositionMode_SourceIn);
    painter.drawImage(0, 0, image);
    painter.setCompositionMode(QPainter.CompositionMode_DestinationOver);
    painter.end();
    resultImage.save(file);
    print ("succed ",file)

#main()
if len(sys.argv) < 3 or len(sys.argv) < 1:
  print ('resizeImage /root 100 50 --demo')
  print ('CircleRectImage /root maskfile --demo')
elif sys.argv[1] == '--help':
  print ("ERROR INFO please view --help")
elif sys.argv[1] == 'resizeImage':
  main(sys.argv[2],(int(sys.argv[3]),int(sys.argv[4])),0)
elif sys.argv[1] == 'CircleRectImage':
  maskfile = sys.argv[3]
  main(sys.argv[2],(0,0),1)
  
  
    