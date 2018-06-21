# Wolf3d

**Description:**

Simple daemon with Cli(Command line interface)

**Requirements:**

* gcc,
* make,
* lpcap library

**Installation and daemon launch:**
* `git clone https://github.com/vvinogra/packtoring`
* `cd packtoring`
* `make`
* `sudo ./daemon or sudo ./packtoring start`

**Cli Commands:**
* `./packtoring start - start sniffing packets from now on from default iface(eth0)`
* `./packtoring --help - show usage information`
* `./packtoring show [ip] count - show how many packets were received from [ip]`
* `./packtoring stop - stop sniffing packets`
* `./packtoring select iface [iface] - select interface for sniffing eth0, wlan0, ethN...`
* `./packtoring stat [iface] - show all collected statistics for particular interface, if [iface] omitted - for all interfaces.`
* `./packtoring reset [ip,iface] - reset ip or iface statistics, if [ip,iface] omitted - reset all statistics.`
* `./packtoring uninstall - uninstalling all files for daemon and resetting to default settings`
* `./packtoring show current iface - show current interface for sniffing`
