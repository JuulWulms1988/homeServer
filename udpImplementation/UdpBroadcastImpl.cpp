#include "UdpBroadcast.hpp"

namespace udpImplementation {

	class udpImplCls : public udpBasCls {
	public:
		udpImplCls() {
			char printIp[16]{ '1', '9', '2', '.', '1', '6', '8', '.', '1', '7', '9', '.', '2', '5', '5', '\0' };
			setAddr(ClientAddr, 1235, printIp);
			{
				sockaddr_in x{ 0 };
				printIp[12] = '1', printIp[13] = '9', printIp[14] = '\0';
				setAddr(x, 1236, printIp);
				bind(serverSocket, (sockaddr*)&x, sizeof(x));
			}
			printIp[12] = '3', printIp[13] = '1', printIp[10] = '8';
			setAddr(ClientAddr2, 1235, printIp);
		}

		void send(char* buf, int len) {
			udpBasCls::send(buf, len, ClientAddr);
			udpBasCls::send(buf, len, ClientAddr2);
		}

		unsigned int receive(char* buffer, unsigned int length) {
			sockaddr_in x{ 0 }; int si = sizeof(x), r;
			while (r = recvfrom(serverSocket, buffer, length, 0, (SOCKADDR*)&x, &si) < 1);
			return (unsigned int)r;
		}

	private:
		struct sockaddr_in ClientAddr;
		struct sockaddr_in ClientAddr2;
	} static udp;

	void send(char* buf, int len) {
		udp.send(buf, len);
	}

	unsigned int receive(char* buffer, unsigned int length) {
		return udp.receive(buffer, length);
	}
}