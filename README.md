# README #

This project is a [BennuGD](http://www.bennugd.org) fork with an emphasis on mobile gaming, although the code should be perfectly usable on normal computers, too.
The main differences of this projects with the regular BennuGD version are:
* The code is mainly aimed at being compiled into a single binary (but you still have to "import" modules from your code).
* My code is based on SDL2 instead of SDL1.2
* Some of the blitting work is now done by the GPU (even on mobile platforms).
* Support for graphics with a bit depth below 16bpp does not work and will be removed, at some point

Most of these changes were performed in order to improve the engine for use with the (unsuccessful) Kickstarter for [Explosive Dinosaurs](https://www.kickstarter.com/projects/rawrlab/explosive-dinosaurs-minigames-dinosaurs-and-explos)

