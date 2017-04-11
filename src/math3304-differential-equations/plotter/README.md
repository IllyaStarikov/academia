# Differential Equations Plotter
Differential Equations at [Missouri S&T](http://www.mst.edu) require homework turned in on paper. Often, what will be required is a plot of graph such as `δ_2pi(t) cosh t^2` or something of that nature. This are incredibly hard to do by hand, and screenshots of [WolframAlpha](https://www.wolframalpha.com/) got tedious. So, I wrote something to do it for me.

The equations are plotted courtesy of [matplotlib](https://matplotlib.org). They're nothing fancy, just standard graphs with labels. After plotting them, they are exported to a LaTeX file, where they are subsequently compiled and opened by the defaults pdf reader.

![A Sample Plot](/images/sample-image.png "Sample Plot")

Note that the plots are opened, and the script will not terminated until they are closed. This is to ensure a double check that all graphs are correct. Also the images are in eps, for best quality.
