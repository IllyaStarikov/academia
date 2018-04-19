# Chess C# Client

This is the root of your AI. Stay out of the `Joueur/` folder, it does most of the heavy lifting to play on our game servers. Your AI, and the game objects it manipulates are all in `Games/Chess/`, with your very own AI living in `Games/Chess/ai.cs` for you to make smarter.

## How to Run

This client has been tested and confirmed to work on the Missouri S&T Windows machines loaded with Visual Studio 2013/2015, but it can work on your own Windows/Linux/Mac machines if you desire. It will **not** work on the campus rc##xcs213 Linux machines however, as their version of Mono is out of date.

### Windows

Simply [installing Visual Studio 2015 or newer](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx) should give you everything you need, namely C#. Just open up the sln file in this repo and build + run it.

*Note*: You'll need to add [command line args in visual studio](https://msdn.microsoft.com/en-us/library/cs8hbt1w(v=vs.90).aspx).

The args should be: `Chess -s r99acm.device.mst.edu -r MyOwnGameSession`

### Linux

Install [dotnet 2.0][dotnet]

After those dependencies install, to run the client:

```bash
make
./testRun MyOwnGameSession
```

## Other Notes

Try not to modify the `.csproj` file.

It is possible that on your Missouri S&T S-Drive this client will not run properly. This is not a fault with the client, but rather the school's S-Drive implementation changing some file permissions during run time. We cannot control this. Instead, we recommend cloning your repo outside the S-Drive and use an SCP program like [WinSCP](https://winscp.net/eng/download.php) to edit the files in Windows using whatever IDE you want if you want to code in Windows, but compile in Linux.

The only file you should ever modify to create your AI is the `AI.cs` file. All the other files are needed for the game to work. In addition, you should never be creating your own instances of the Game's classes, nor should you ever try to modify their variables. Instead, treat the Game and its members as a read only structure that represents the game state on the game server. You interact with it by calling the game functions.

[dotnet]: https://www.microsoft.com/net/learn/get-started/linux
[gitbash]: https://git-scm.com/downloads
