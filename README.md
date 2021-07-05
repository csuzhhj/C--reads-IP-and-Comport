# C-reads-IP-addresses
Using Visual Studio C++ to read IP addresses on Windows platform

HOW TO USE:
```
#include"GetIp.h"

int main() {
	cout << getip() << endl;//Print IP Address
}
```

Possible errors:
Use getaddrinfo() or GetAddrInfoW() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings XXX

Solution:
Open the project properties, edit the preprocessor definition, and add:
_WINSOCK_DEPRECATED_NO_WARNINGS
