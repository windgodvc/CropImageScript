#coding:utf-8
# 2016 7.30 author:windgodvc
import os
import sys
from PIL import Image 

reslist = []
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
  image = Image.open(filepath)
  image = image.resize(qsize,Image.BILINEAR)
  image.save(filepath)


#递归遍历/root目录下所有文件
def main(dir,qsize):
  getDirFile(dir)
  for it in reslist:
    if it.find(".png") != -1 or it.find(".jpg") != -1 or it.find(".bmp") != -1:
      cropImage(it,qsize)
      print it

  
  print "裁剪完成"

#main()
if sys.argv[1] == '--help':
  print '/root 100 50'
elif len(sys.argv) < 4:
  print "ERROR INFO please view --help"
else:
  main(sys.argv[1],(int(sys.argv[2]),int(sys.argv[3])))
  
    
