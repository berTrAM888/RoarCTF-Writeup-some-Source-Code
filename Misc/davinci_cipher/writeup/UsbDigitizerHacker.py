# coding:utf-8

import sys
import os
import numpy as np
import matplotlib.pyplot as plt

mousePositionX = 0
mousePositionY = 0

X = []
Y = []

DataFileName = "test.txt"
data = []

def main():
    global mousePositionX
    global mousePositionY
    # check argv
    if len(sys.argv) == 1:
        print "Usage : "
        print "        python UsbDigitizerHacker.py data.pcap [Conditions used to sort]"
        print "Tips : "
        print "        To use this python2 script , you must install the numpy,matplotlib first."
        print "        You can use `sudo pip install matplotlib numpy` to install it"
        exit(1)

    # get argv
    pcapFilePath = sys.argv[1]
    print pcapFilePath
    # get data of pcap
    if len(sys.argv)==2:
        command = "tshark -r '%s' -T fields -e usb.capdata > %s" % (
            pcapFilePath, DataFileName)
        print command
        os.system(command)
    if len(sys.argv)==3:
        Conditions=sys.argv[2]
        command = "tshark -r '%s' -T fields -e usb.capdata -Y '%s' > %s" % (
            pcapFilePath,Conditions, DataFileName)
        print command
        os.system(command)


    with open(DataFileName, "rb") as f:
        flag=1
        for line in f:
            if line[24:26] != "00":  #根据压力值筛选，使画图结果更精准
                print line
                data.append(line[0:-1])  

    #x,y坐标 小端序
    for line in data: 
        x0=int(line[6:8],16)
        x1=int(line[9:11],16)
        x=x0+x1*256  
        y0=int(line[15:17],16)
        y1=int(line[18:20],16)
        y=y0+y1*256
        X.append(x)
        Y.append(-y)
    
    #draw
    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    ax1.set_title('[%s]' % (pcapFilePath))
    ax1.scatter(X, Y, c='r', marker='o')
    plt.savefig("out.png")
    plt.show()


    #clean temp data
    os.system("rm ./%s" % (DataFileName))

if __name__ == "__main__":
    main()
