#!#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# =============================================================================
# colorimeter.py
# description : see colors in at least one color
# depends: pyqt5, matplotlib, pyserial
# created by : Joakim Skjefstad
# =============================================================================

import sys

import matplotlib
matplotlib.use('Qt5Agg')

from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QToolBar, QAction, QStatusBar, QHBoxLayout, QVBoxLayout, QPushButton, QWidget, QCheckBox
from PyQt5.QtCore import Qt, QSize
from PyQt5.QtGui import QIcon

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from matplotlib.figure import Figure

import matplotlib.pyplot as plt


import numpy as np
import threading
import serial
import string

printable = set(string.printable)

connected = False
port = '/dev/tty.usbmodem141301'
baud = 9600
ser = serial.Serial(port, baud, timeout=None)

class MplCanvas(FigureCanvasQTAgg):

    def __init__(self, parent=None, width=5, height=4, dpi=100):
        plt.ion()
        self.fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = self.fig.add_subplot(111)
        super(MplCanvas, self).__init__(self.fig)

class MainWidget(QWidget):
    def __init__(self):
        super().__init__()

        # LED states
        self.boolRedOn = False
        self.boolGreenOn = False
        self.boolBlueOn = False

        # Plot data
        self.xPlot = [1, 2, 3, 3]
        self.yPlot = [1, 2, 3, 4]

        self.initUI()

    def initUI(self):

        btnReadLDR = QPushButton("Read LDR")
        cbRed = QCheckBox('Red', self)
        cbGreen = QCheckBox('Green', self)
        cbBlue = QCheckBox('Blue', self)
        self.lblLDR = QLabel('-1', self)


        btnReadLDR.clicked.connect(self.readLDR)
        cbRed.stateChanged.connect(self.toggleRed)
        cbGreen.stateChanged.connect(self.toggleGreen)
        cbBlue.stateChanged.connect(self.toggleBlue)

        hbox = QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(btnReadLDR)
        hbox.addWidget(self.lblLDR)
        hbox.addWidget(cbRed)
        hbox.addWidget(cbGreen)
        hbox.addWidget(cbBlue)
        

        vbox = QVBoxLayout()
        vbox.addStretch(1)

        self.sc = MplCanvas(self, width=5, height=4, dpi=100)
       # self.sc.axes.plot(self.xPlot, self.yPlot)
        

        vbox.addWidget(self.sc)
        vbox.addLayout(hbox)

        self.setLayout(vbox)

        self.setGeometry(300, 300, 300, 150)
        self.setWindowTitle('Buttons')
        self.show()


    def readLDR(self, state):
        print('reading ldr')
        ser.write(b'<r>')
        #time.sleep(1)
        serData = ser.readline()
        ldrValue = serData.decode().strip()
        print(ldrValue)
        self.lblLDR.setText(ldrValue)
   #     self.xPlot.append(int(ldrValue))
   #     self.yPlot.append(5)
    #    self.sc.fig.draw()

    def toggleRed(self, state):
        print('toggling red')
        if self.boolRedOn:
            ser.write(b'<s,r,0>')
            self.boolRedOn = False
        else:
            ser.write(b'<s,r,255>')
            self.boolRedOn = True

    def toggleGreen(self, state):
        print('toggling green')
        if self.boolGreenOn:
            ser.write(b'<s,g,0>')
            print('green set off')
            self.boolGreenOn = False
        else:
            ser.write(b'<s,g,255>')
            print('green set on')
            self.boolGreenOn = True

    def toggleBlue(self, state):
        print('toggling blue')
        if self.boolBlueOn:
            ser.write(b'<s,b,0>')
            self.boolBlueOn = False
        else:
            ser.write(b'<s,b,255>')
            self.boolBlueOn = True

class MainWindow(QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)

        self.setWindowTitle("Colorimeter")

        self.wid = MainWidget()
        self.setCentralWidget(self.wid)

        toolbar = QToolBar("My main toolbar")
        toolbar.setIconSize(QSize(16,16))
        self.addToolBar(toolbar)

        button_action = QAction(QIcon(), "Read LDR", self)
        button_action.setStatusTip("Check LDR values")
        button_action.triggered.connect(self.onMyToolBarButtonClick)
        button_action.setCheckable(True)
        toolbar.addAction(button_action)

        self.setStatusBar(QStatusBar(self))


    def onMyToolBarButtonClick(self, s):
        print("click")
        self.wid.readLDR(self.wid)

def main():
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    app.exec_()

# call main
if __name__ == '__main__':
    main()