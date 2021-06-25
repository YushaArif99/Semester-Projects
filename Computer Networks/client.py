
from protocol import RDC_Protocol
import tkinter
from twisted.internet import tksupport, reactor
import hashlib
from PIL import ImageTk, Image
from io import BytesIO
from config import *
import json
import time



class FactoryControllerBase:

    def __init__(self):
        self.tk = tkinter.Tk()
        self.tk.title("Remote Desktop Control ")
        tksupport.install(self.tk)

    def buildProtocol(self, addr):
        return RDC_Client_Protocol(self.tk)


class RDC_Client_Protocol(RDC_Protocol):

    """"
        Protocol class for the controller. This class implements functions
        to capture mouse, keyboard events of the controller and render shared snapshots 
        of controllee's screen.
          
    """

    def __init__(self, tk):
        RDC_Protocol.__init__(self)

        print("Controller init")
        self.root = tkinter.Toplevel(tk)
        self.root.state('zoomed')
        self.root.protocol("WM_DELETE_WINDOW", self.onCancel)
        self.lastReceivedTime = time.time()

        """
            ...... Tkinter gui form 
        """

        frame = tkinter.Frame(self.root)
        frame.pack()

        tkinter.Label(frame, text='Monitor:').pack(side=tkinter.LEFT)
        monScale = tkinter.Scale(frame, from_=0, to=4, orient=tkinter.HORIZONTAL, command=self.changeMonitor)
        monScale.pack(side=tkinter.LEFT)
        monScale.set(VAR_MONITOR_DEFAULT)

        tkinter.Label(frame, text='Scale:').pack(side=tkinter.LEFT)
        scaleScale = tkinter.Scale(frame, from_=0.1, to=1, orient=tkinter.HORIZONTAL, resolution=0.1, command=self.changeScale)
        scaleScale.pack(side=tkinter.LEFT)
        scaleScale.set(VAR_SCALE_DEFAULT)

        self.updateVar = tkinter.BooleanVar(self.root, VAR_SHOULD_UPDATE_COMMANDS_DEFAULT)
        updateCheck = tkinter.Checkbutton(frame, text='Update commands', command=self.changeUpdateCommands, variable=self.updateVar)
        updateCheck.pack(side=tkinter.LEFT)

        tkinter.Label(frame, text='FPS:').pack(side=tkinter.LEFT)
        self.fpsLabel = tkinter.Label(frame, text='?')
        self.fpsLabel.pack(side=tkinter.LEFT)

        self.label = tkinter.Label(self.root)
        self.label.pack(fill=tkinter.BOTH, expand=True)

        self.root.bind('<Key>', self.onKeyPressed)
        self.root.bind('<KeyRelease>', self.onKeyReleased)
        self.label.bind('<Button>', self.onMousePressed)
        self.label.bind('<ButtonRelease>', self.onMouseReleased)



    def getMousePosition(self, x, y):
        labelSize = self.getLabelSize()

        return (x / labelSize[0], y / labelSize[1])


    def onMousePressed(self, e):

        """
            Gets the mouse x, y coodinates and finds the actual local location.
        """

        pos = self.getMousePosition(e.x, e.y)

        self.sendCommand('MoveMouse', pos[0], pos[1])

        self.sendCommand('MouseInput', e.num == 1, True)

    def onMouseReleased(self, e):

        location = self.getMousePosition(e.x, e.y)
        self.sendCommand('MoveMouse', location[0], location[1])
        self.sendCommand('MouseInput', e.num == 1, False)

    
    def onKeyPressed(self, e):
        """
            Wrapper for key  event. True value for key pressed.
        """
        self.sendCommand('KeyboardInput', e.keycode, True)

    
    def onKeyReleased(self, e=None):
        """
            Wrapper for key down event . False value for key not pressed
        """
        self.sendCommand('KeyboardInput', e.keycode, False)


    def onCancel(self):
        """
            CLoses the TCP connection
        """

        self.transport.abortConnection()

        reactor.stop()

    def getLabelSize(self):
        return (self.label.winfo_width(), self.label.winfo_height())

    def changeScale(self, newScale: str):
        self.setValue(VAR_SCALE, float(newScale))

    def changeMonitor(self, newMonitor: str):
        self.setValue(VAR_MONITOR, int(newMonitor))

    def changeUpdateCommands(self):
        self.setValue(VAR_SHOULD_UPDATE_COMMANDS, self.updateVar.get())

    def setValue(self, variable, value):
        toSend = COMMAND_SET_VAR.encode('ascii')
        toSend += json.dumps({
            'variable': variable,
            'value': value
        }).encode('ascii')
        self.writeMessage(toSend)

    def sendCommand(self, commandName, *args):
        toSend = COMMAND_NEW_COMMAND.encode('ascii')
        toSend += json.dumps([commandName, *args]).encode('ascii')
        self.writeMessage(toSend)

    def messageReceived(self, data: bytes):

        size = self.getLabelSize()

        img = Image.open(BytesIO(data))
        img = img.resize(size)

        self.currentImage = ImageTk.PhotoImage(img)
        self.label.configure(image=self.currentImage)
        self.fpsLabel['text'] = '%.1f' % (1/(time.time() - self.lastReceivedTime))
        self.lastReceivedTime = time.time()

        self.writeMessage(COMMAND_SEND_SCREENSHOT.encode('ascii'))

    def connectionLost(self, reason):
        print('Connection lost', reason)
        RDC_Protocol.connectionLost(self)
        if self.root is not None:
            self.root.destroy()
            self.root = None