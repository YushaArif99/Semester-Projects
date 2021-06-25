from twisted.internet import reactor
from twisted.internet.protocol import *
from twisted.internet.endpoints import *
from twisted.internet import reactor
from client import RDC_Client_Protocol, FactoryControllerBase
from server import RDC_Server_Protocol

# To dos:
    # Adding id / password authentication
    # Optimizing Screen sharing

class CFactory(ReconnectingClientFactory):

    maxDelay = 5
    factor = 1

    def buildProtocol(self, addr):
        self.resetDelay()
        return ReconnectingClientFactory.buildProtocol(self, addr)

class RDC_Client_Factory(FactoryControllerBase, Factory):
    pass


class RDC_Server_Factory(CFactory):
    protocol = RDC_Server_Protocol


def get_transport(ip: str, port: int):

    if len(ip) == 0 or ip is None or ip == "":

        factory = RDC_Client_Factory()
        reactor.listenTCP(port, factory)
        return factory
    else:

        factory = RDC_Server_Factory()
        reactor.connectTCP(ip, port, factory)
        return factory



if __name__ == '__main__':

    mode = input('client/server: ')
    host = ""

    if mode == 'client':
        host = input('host ip: ')

    port = int(input('port: '))

    factory = get_transport(host, port)

    print("initiated")

    reactor.run()

