# Chess Java Client

This is the root of you AI. Stay out of the `joueur/` folder, it does most of the heavy lifting to play on our game servers. Your AI, and the game objects it manipulates are all in `games/chess/`, with your very own AI living in `games/chess/AI.java` for you to make smarter.

## How to Run

This client has been tested and confirmed to work on the Campus rc##xcs213 Linux machines, but it can work on your own Windows/Linux/Mac machines if you desire.

### Linux

```
make
./testRun MyOwnGameSession
```

JRE8 and Maven 3 are the only required packages, and can be found in `openjdk-8-jdk-headless` or `java-common` and `maven` packages respectively.

In addition, after you `make` once, you can do `make core` instead to just rebuild, and not fetch the dependencies again.

### Windows

Just like in Linux, we can build this via the command line. Before you do so ensure that the [JDK 8][jdk8] and [Maven][maven] are installed and accessible from the PATH (Maven will require setting your JAVA_HOME environmental variable). If you can run `java`, `javac`, and `mvn` via the command line in Windows you should be good.

Once those are installed run Maven to grab the packages you need:

```
mvn clean compile assembly:single
```
After you've done this step you theoretically never need to run it again, unless you wish to use more packages.

where `<server>` is the game server to connect to, any other args can be found via the `-h` help flag.

#### Eclipse

Another option is to use [Eclipse][eclipse] and just create a new project from existing code, pointing to this repo. It should read the `.classfile` and `.project` file to setup the rest. Note you'll need the Maven plugin too.

## Other Notes

It is possible that on your Missouri S&T S-Drive this client will not run properly. This is not a fault with the client, but rather the school's S-Drive implementation changing some file permissions during run time. We cannot control this. Instead, we recommend cloning your repo outside the S-Drive and use an SCP program like [WinSCP][winscp] to edit the files in Windows using whatever IDE you want if you want to code in Windows, but compile in Linux.

The only file you should ever modify to create your AI is the `AI.java` file. All the other files are needed for the game to work. In addition, you should never be creating your own instances of the Game's classes, nor should you ever try to modify their variables. Instead, treat the Game and its members as a read only structure that represents the game state on the game server. You interact with it by calling the game functions.

[jdk8]: http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html
[maven]: https://maven.apache.org/install.html
[eclipse]: http://www.eclipse.org/downloads/packages/eclipse-ide-java-developers/mars1
[winscp]: https://winscp.net/eng/download.php
[vagrant]: https://www.vagrantup.com/downloads.html
[virtualbox]: https://www.virtualbox.org/wiki/Downloads
[vagrant-guide]: https://www.vagrantup.com/docs/getting-started/up.html
[virtualbox]: https://www.virtualbox.org/wiki/Downloads
[gitbash]: https://git-scm.com/downloads
