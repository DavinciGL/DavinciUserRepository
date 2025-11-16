# CKookie
CKookie is a fast and simple HTTP file sharing Protocol written in C built for Speed and Small resource Usage.

# Usage

If you want to build from source just run the gmake binary included in the Package, ./gmake and it should just build everything lightning fast, to ping your server just do curl (server_ip):12345/(filename).(file-extension)

CKookie runs in Port 12345, so use that Port for curling the Server.

If your hosting it yourself, just do localhost:12345/(filename).(file-extension)

# Building Engine

It uses GMake, a Build Engine that i was helped out with by Davinci (The Developers of DavinciGL) that is ultra fast and minimal.

Just run the GMake binary in the project root directory and it will read the GMake file and build using the tasks.

If you want to use Makefile you will need to write your own, but GMake is minimal and lightweight and ultra fast so I prefer to use it.



