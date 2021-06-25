from config import *
from mss import mss
import time
from typing import List
from pynput import mouse, keyboard
import threading
from utility import *

class CommandBase():

    def __init__(self, config: dict):
        self.isDone = False
        self.config = config
        self.frame = -1

    def start(self):
        self.timeStart = time.time()

    def update(self):
        self.frame += 1
    
    def time(self):
        return time.time() - self.timeStart

    def finish(self):
        self.isDone = True
        print("Command finished", self)
    
    def __str__(self):
        return self.__class__.__name__

mouseController = mouse.Controller()

class CommandMoveMouse(CommandBase):
    speed = 10

    def __init__(self, config: dict, x: float, y: float):
        with mss() as sct:
            m = sct.monitors[config[VAR_MONITOR]]
            self.target = (round(m['width'] * x + m['left']),
                           round(m['height'] * y + m['top']))
        CommandBase.__init__(self, config)

    def start(self):
        global mouseController
        CommandBase.start(self)
        self.controller = mouseController

    def update(self):
        CommandBase.update(self)
        
        vecToTarget = vector_subract(self.target, self.controller.position)
        l = vector_length(vecToTarget)
        if l < self.speed:
            self.controller.position = self.target
            self.finish()
        else:
            rel = vector_normalize(vecToTarget, l)
            rel = vector_multiply(rel, self.speed)
            rel = vector_round(rel)
            self.controller.move(rel[0], rel[1])
    
    def __str__(self):
        ret = 'Move mouse ' + str(self.target[0]) + 'x' + str(self.target[1])
        return ret

class CommandMouseInput(CommandBase):

    def __init__(self, config: dict, isLeft: bool, isDown: bool):
        self.isLeft = isLeft
        self.isDown = isDown
        CommandBase.__init__(self, config)


    def update(self):
        CommandBase.update(self)
        if self.frame == 0:
            controller = mouse.Controller()
            btn = mouse.Button.left if self.isLeft else mouse.Button.right
            if self.isDown:
                controller.press(btn)
            else:
                controller.release(btn)
        self.finish()

    def __str__(self):
        return ('Left' if self.isLeft else 'Right') + ' mouse ' + \
                ('Down' if self.isDown else 'Up')

class CommandKeyboardInput(CommandBase):

    def __init__(self, config: dict, keycode: int, isDown: bool):
        self.keycode = keycode
        self.isDown = isDown
        CommandBase.__init__(self, config)
    
    def update(self):
        CommandBase.update(self)

        if self.frame == 0:
            controller = keyboard.Controller()
            kc = keyboard.KeyCode(self.keycode)
            if self.isDown:
                controller.press(kc)
            else:
                controller.release(kc)

        self.finish()

    def __str__(self):
        return ('Press ' if self.isDown else 'Release ') + str(self.keycode)

class Commands(threading.Thread):

    command_mappings = {
        'MoveMouse': CommandMoveMouse,
        'MouseInput': CommandMouseInput,
        'KeyboardInput': CommandKeyboardInput
    }

    def __init__(self, config, *args, **kwargs):
        threading.Thread.__init__(self, *args, **kwargs)
        self.currentCommands = [] # type: List[CommandBase]
        self.shouldRun = True
        self.config = config
    
    def addCommand(self, commandName: str, *args):
        instance = self.command_mappings[commandName](self.config, *args)
        self.addCommandInstance(instance)
    
    def addCommandInstance(self, commandInstance):
        self.currentCommands.append(commandInstance)
        if len(self.currentCommands) == 1:
            self.currentCommands[0].start()
    
    def finishCurrentCommand(self):
        if len(self.currentCommands) > 0:
            self.currentCommands = self.currentCommands[1:]
            if len(self.currentCommands) > 0:
                self.currentCommands[0].start()

    def updateCommand(self):
        if len(self.currentCommands) > 0:
            self.currentCommands[0].update()
            if self.currentCommands[0].isDone:
                self.finishCurrentCommand()
    
    def run(self):
        while self.shouldRun:
            if self.config[VAR_SHOULD_UPDATE_COMMANDS]:
                try:
                    self.updateCommand()
                except Exception as e:
                    print("Error happened")
                    print(e)
            time.sleep(0.01)