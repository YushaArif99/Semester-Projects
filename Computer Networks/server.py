from config import *
import json
from twisted.internet import reactor
from mss import mss
import io
import commands
import PIL
from protocol import RDC_Protocol


class RDC_Server_Protocol(RDC_Protocol):

    def __init__(self):
        RDC_Protocol.__init__(self)

        self.config = {}

        self.setVariable(VAR_SCALE, VAR_SCALE_DEFAULT, False)
        self.setVariable(VAR_MONITOR, VAR_MONITOR_DEFAULT, False)
        self.setVariable(VAR_SHOULD_UPDATE_COMMANDS, VAR_SHOULD_UPDATE_COMMANDS_DEFAULT, False)


        reactor.callLater(1, self.captureScreenAndSend)

        self.commands = commands.Commands(self.config)

        self.commands.start()

    def messageReceived(self, data: bytes):

        """ This function receives command as raw bytes. """

        command = data.decode('ascii')

        # Command to send a new snapshot of screen
        if command == COMMAND_SEND_SCREENSHOT:
            self.captureScreenAndSend()

        # Command to set var
        if command.startswith(COMMAND_SET_VAR):
            info = json.loads(command[len(COMMAND_SET_VAR):])
            self.setVariable(**info)

        if command.startswith(COMMAND_NEW_COMMAND):
            info = json.loads(command[len(COMMAND_NEW_COMMAND):])
            self.commands.addCommand(*info)

    def setVariable(self, variable, value, shouldPrint = True):
        self.config[variable] = value


    def captureScreenAndSend(self):

        with io.BytesIO() as output:

            with mss() as s:

                monitorRequest = self.config[VAR_MONITOR]
                monitorRequest = min(len(s.monitors) - 1, monitorRequest)
                screen = s.grab(s.monitors[monitorRequest])

                # Used PIL library to capture screen images and convert into bytes

                ss = PIL.Image.frombytes('RGB', screen.size, screen.bgra, 'raw', 'BGRX')
                if self.config[VAR_SCALE] < 1:
                    ss = ss.resize((int(ss.size[0] * self.config[VAR_SCALE]),
                                    int(ss.size[1] * self.config[VAR_SCALE])))

                ss.save(output, format="JPEG", quality=60)

                self.writeMessage(output.getvalue())
    
    def connectionLost(self, r="no"):
        self.commands.shouldRun = False
