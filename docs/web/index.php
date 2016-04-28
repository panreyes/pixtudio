<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>PixTudio</title>
        <meta name="description" content="PixTudio game engine description page.">
        <meta name="author" content="Joseba García Etxebarria"/>
        <link rel="stylesheet" href="main.css">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.0/jquery.min.js"></script>
        <script>
            /* Google analytics */
            (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
             (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
             m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
             })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

             ga('create', 'UA-72167122-1', 'auto');
             ga('send', 'pageview');

            /* Link scroll */
            $(document).ready(function(){
                $('a[href^="#"]').on('click',function (e) {
                    e.preventDefault();

                    var target = this.hash,
                    $target = $(target);

                    $('html, body').stop().animate({
                        'scrollTop': $target.offset().top - 80
                    }, 300, 'swing');
                });
            });
        </script>
    </head>
    <body>
        <ul class="nav">
            <li><a href="#intro">Introduction</a></li>
            <li><a href="#showcase">Showcase</a></li>
            <li><a href="/docs">Docs</a></li>
            <li><a href="#project_page">Project page</a></li>
            <li><a href="#compiling">Compiling</a></li>
            <li><a href="#bugs">Bugs</a></li>
            <li><a href="#links">Links</a></li>
        </ul>
        <h1 id="intro">PixTudio</h1>
        <h2>Introduction</h2>
        <p>
            PixTudio is a 2D game engine for Windows, Linux, OS X, Android &amp; iOS.
        </p>
        <p>
            <a href="http://opensource.org/licenses/Zlib">
                <img src="img/osi_keyhole_100X100_90ppi.png" alt="Open Source software" class="logo" />
            </a>
            The game engine is licensed under the very permissive
            <a href="http://opensource.org/licenses/Zlib">zlib license</a>, which means that you're free to
            use it in both open-source and closed-source projects.
        </p>
        <p>
            It is also very easy to use. The main execution units in PixTudio are called processes.
            Processes are like functions with properties you can set freely.<br/>
            The following example shows the code for a simple process named "enemy" whose graphic
            is loaded from a PNG file and is positioned at coordinates (x, y) = (100, 200).
            <code style="white-space: pre;"><b>Process</b> enemy()
<b>Begin</b>
    graph = png_load("img/enemy.png");
    x = 100; y = 200;
    <b>LOOP</b>
        <b>FRAME;</b>
    <b>End</b>
<b>End</b></code>
        </p>

        <h2 id="showcase">Games showcase</h2>
<?php
    switch (mt_rand(0, 1)) {
        case 0:
?>
        <h3>Tiki Brawl</h3>
        <p>
            Created in two days, Tiki Brawl is Last Five's entry for the
            <a href="http://globalgamejam.org/">2016 Global Game Jam</a>.
        </p>
        <p>
            You can download a copy of the game from
            <a href="http://globalgamejam.org/2016/games/tiki-brawl">its GGJ entry page</a>.
        </p>
        <p style="text-align: center;">
            <iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/GbtDFRhlIhk" style="border: none;" allowfullscreen></iframe>
        </p>
        <p>
            You can also vote for the game in
            <a href="http://steamcommunity.com/sharedfiles/filedetails/?id=612666493">Steam Greelight</a>
            so that it gets included in Steam.
        </p>

        <h2 id="project_page">Project page</h2>
        <p>
            Check out the project page at
            <a href="https://bitbucket.org/josebagar/pixtudio">
                Bitbucket
            </a>.
        </p>
<?php
            break;

        case 1:
?>
        <h3>Spidey Technical Demo</h3>
        <p>
            Developed by Gabriel Garrote in 2011, the video shows the technical demo
            adapted for PixTudio running at a 1080p resolution and 60fps.<br/>
            You can find more info in Spanish
            <a href="http://forum.bennugd.org/index.php?topic=2708.0">here</a>.
        </p>
        <p style="text-align: center;">
            <iframe width="560" height="315" src="https://www.youtube-nocookie.com/embed/gOAtYSW-VU0" style="border: none;" allowfullscreen></iframe>
        </p>
<?php
            break;
    }
?>

        <h2 id="project_page">Project page</h2>
        <p>
            Check out the project page at
            <a href="https://bitbucket.org/josebagar/pixtudio">
                Bitbucket
            </a>.
        </p>

        <h2 id="compiling">Compiling PixTudio from source code</h2>

        <h3>Fedora 23 Workstation</h3>
        <p>
            These instructions might work in earlier versions of Fedora and in other Fedora
            spins, too, but have only been tested in a fully updated fresh installation of
            Fedora 23 Workstation.
        </p>
        <ul>
            <li>Open a terminal</li>
            <li>
                Install the required command line utilities.
                <code>sudo dnf group install "Development Tools"
                sudo dnf install cmake
                </code>
            </li>
            <li>
                Install the required dependencies.
                <code>sudo dnf install SDL2-devel.i686 SDL2_mixer-devel.i686 libpng-devel.i686 zlib-devel.i686 libogg-devel.i686 libvorbis-devel.i686 libtheora-devel.i686 tre.i686 tre-devel.i686 sqlite-devel.i686 libcurl-devel.i686 openal-soft-devel.i686 freetype-devel.i686 glibc-devel.i686
                </code>
            </li>
            <li>
                Clone the source code repository.
                <code>git clone https://bitbucket.org/josebagar/pixtudio.git
                </code>
            </li>
            <li>
                Compile the source code.
                <code>cd pixtudio/projects/cmake
                    ./build.sh
                </code>
            </li>
            <li>
                The binaries should be in bin/gnulinux32.
            </li>
        </ul>

        <h3>Ubuntu 15.10</h3>
        <p>
            These instructions might work in earlier versions of Ubuntu and in other Ubuntu
            flavours, too, but have only been tested in a fresh installation of Ubuntu 15.10.
        </p>
        <ul>
            <li>Open a terminal</li>
            <li>
                Install the required command line utilities.
                <code>sudo apt-get update
                    sudo apt-get install git cmake
                </code>
            </li>
            <li>
                Install the required dependencies.
                <code>sudo apt-get install libsdl2-dev:i386 libsdl2-mixer-dev:i386 libpng12-dev:i386 zlib1g-dev:i386 libogg-dev:i386 libvorbis-dev:i386 libtheora-dev:i386 libtre-dev:i386 libsqlite3-dev:i386 libcurl4-gnutls-dev:i386 libopenal-dev:i386 libfreetype6-dev:i386 libc6-dev:i386
                </code>
            </li>
            <li>
                Clone the source code repository.
                <code>git clone https://bitbucket.org/josebagar/pixtudio.git
                </code>
            </li>
            <li>
                Compile the source code.
                <code>cd pixtudio/projects/cmake
                    ./build.sh
                </code>
            </li>
            <li>
                The binaries should be in bin/gnulinux32.
            </li>
        </ul>

        <h3>OS X</h3>
        <p>
            These instructions should work in earlier versions of OS X (as long as they're supported by Apple), but have only been tested in a fresh install of OS X El Capitan.
        </p>
        <ul>
            <li>
                Open a Terminal and execute the following command to check for the Xcode command line
                tools:
                <code>clang</code>
                If the output reads like the following the developer tools are already installed in
                your computer and you can skip to the next step:
                <code>clang: error: no input files</code>
                Otherwise, the following message will be displayed and a dialog will be opened
                offering to install either Xcode or the command line tools. Both should work.
                <code>xcode-select: note: no developer tools were found at '/Applications/Xcode.app', requesting install. Choose and option in the dialog to download the command line developer tools.</code>
                Close that terminal.
            </li>
            <li>
                Install <a href="https://www.macports.org/install.php">MacPorts</a>.
                <a href="http://brew.sh/">Homebrew</a> will probably work, too, but you'll have to
                adapt the instructions below.
            </li>
            <li>
                Open a new terminal and install the required MacPorts dependencies.
                <code>sudo port install libsdl2 +universal libsdl2_mixer +universal libpng +universal zlib +universal libogg +universal libvorbis +universal libtheora +universal libmikmod +universal tre +universal smpeg2 +universal curl +universal chipmunk +universal freetype +universal ninja cmake
                </code>
            </li>
            <li>
                Clone the source code repository.
                <code>git clone https://bitbucket.org/josebagar/pixtudio.git
                </code>
            </li>
            <li>
                Compile the source code.
                <code>cd pixtudio/projects/cmake
                    ./build.sh
                </code>
            </li>
            <li>
                The binaries should be in bin/osx32.
            </li>
        </ul>

        <h3>Windows 10</h3>
        <p>
            These instructions should work in earlier versions of Windows (as long as they're supported by Microsoft), but have only been tested in Windows 10.
        </p>
        <ul>
            <li>Install <a href="http://msys2.github.io/">MSYS2</a> (don't forget
                to update it as described in the project page).</li>
            <li>Open <b>MinGW-w64 Win32 Shell</b> (not MSYS2 Shell!)</li>
            <li>
                Install the required command line and development tools.
                <code>pacman -S msys/git mingw32/mingw-w64-i686-gcc mingw32/mingw-w64-i686-pkg-config mingw32/mingw-w64-i686-cmake mingw32/mingw-w64-i686-ninja
                </code>
            </li>
            <li>
                Install the required dependencies.
                <code>pacman -S mingw32/mingw-w64-i686-SDL2 mingw32/mingw-w64-i686-SDL2_mixer mingw32/mingw-w64-i686-libpng mingw32/mingw-w64-i686-zlib mingw32/mingw-w64-i686-libogg mingw32/mingw-w64-i686-libvorbis mingw32/mingw-w64-i686-libtheora mingw32/mingw-w64-i686-libmodplug mingw32/mingw-w64-i686-libmikmod mingw32/mingw-w64-i686-libtre-git mingw32/mingw-w64-i686-flac mingw32/mingw-w64-i686-sqlite3 mingw32/mingw-w64-i686-curl mingw32/mingw-w64-i686-chipmunk mingw32/mingw-w64-i686-openal mingw32/mingw-w64-i686-freetype
                </code>
            </li>
            <li>
                Clone the source code repository.
                <code>git clone https://bitbucket.org/josebagar/pixtudio.git
                </code>
            </li>
            <li>
                Compile the source code.
                <code>cd pixtudio/projects/cmake
                    ./build.sh
                </code>
            </li>
            <li>
                The binaries should be in bin/win32.
            </li>
        </ul>

        <h3>Android</h3>
        <p>
            Install both the <a href="http://developer.android.com/sdk/index.html">Android SDK</a>
            &amp; the <a href="http://developer.android.com/tools/sdk/ndk/index.html">NDK</a>.
        </p>

        <p>
            Please note that in order to compile PixTudio for Android yourself you don't need really need
            Android Studio, only its SDK parts, but you might want to install the full Android Studio if
            you're planning to develop other Android apps.
        </p>
        <p>
            Install the Android 4.4.2 (API 19) SDK platform and -optionally- an emulator image from the
            Android SDK manager.
        </p>
        <p>
            Download the PixTudio source code, either with Git (see instructions in the native compilation
            section) or from <a href="https://bitbucket.org/josebagar/pixtudio/downloads">here</a>.
        </p>
        <p>
            Edit projects/android/local.properties and change the sdk.dir property to point to your
            Android SDK installation dir.
        </p>
        <p>
            If you want to install your game into a real Android device, be sure to
            <a href="http://developer.android.com/tools/device.html">enable
            USB debugging</a> during your development session and connect your device
            to your computer with a USB cable.
        </p>
        <p>
            If you're going to develop in an emulator image,
            <a href="http://developer.android.com/tools/devices/index.html">create one</a>
            and start it now.
        </p>
        <p>
            Open a command line in the main PixTudio source code folder. Then do:
        </p>
        <ul>
            <li>
                Go to the Android project folder:
                <code>cd projects/android</code>
            </li>
            <li>
                If you're using the Windows cmd.exe console, compile the C source code with:
                <code>ndk-build.cmd</code>
                Otherwise, compile it with:
                <code>ndk-build</code>
            </li>
            <li>
                Copy your game's resources into the "assets" folder and make sure to name
                the main DCB file (compiled with a desktop version of PixTudio) "main.dcb".<br/>
                Typically, PixTudio resource files (FPG, MAP &amp; FNT files) will actually be
                compressed in gzip format. PixTudio for Android cannot read compressed files
                from within APK files, so make sure that they are uncompressed.
            </li>
            <li>
                Compile the libraries, assets &amp; Java code into an APK.
                <code>ant debug</code>
                Or compile the libraries, assets &amp; Java code into an APK and install it in
                an attached Android device or emulator.
                <code>ant debug install</code>
            </li>
        </ul>

        <h3>iOS</h3>
        <p>
            Install the latest version of
            <a href="https://itunes.apple.com/es/app/xcode/id497799835?mt=12#">Xcode</a> from Apple.
        </p>

        <p>
            Please note that PixTudio for iOS is still a work in progress project.
        </p>

        <h2 id="bugs">Bugs</h2>
        <p>
            Do you believe you found a bug? Report it at the
            <a href="https://bitbucket.org/josebagar/pixtudio/issues?status=new&status=open">
                Bitbucket bugtrack
            </a>.
        </p>

        <h2 id="links">Some links</h2>
        <ul>
            <li><a href="http://forum.bennugd.org/index.php?board=97.0">PixTudio forum</a></li>
        </ul>

    </body>
</html>
