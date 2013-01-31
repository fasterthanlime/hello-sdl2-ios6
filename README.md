## hello-sdl2-ios6

Just testing out a pure C application using SDL 2.0 (still in dev),
OpenGL ES, running on iphonesimulator6.0, built using cmake + Xcode.

### How to build for the simulator

```
mkdir xcode && cd xcode
cmake -GXcode ..
open Hello.xcodeproj
```

Then hit 'Build and run' and you should see a red screen (exciting, right?)

### How to build for an actual device

I haven't tested this, but you should be able to do it.
Open `CMakeLists.txt`, replace `iphonesimulator` with `iphoneos`
in CMAKE_OSX_SYSROOT, and it should build + run splendidly.

Let me know if it works for you!

### Notes

The current project runs in iPhone 4 non-retina resolution.
If you want retina-resolution, you'll have to change it in
the code (`src/main.c`).

### Why!?

Partly because I'm investigating porting my ooc games to
iOS (and Android) - read [this post for example](https://amos.me/blog/2013/braindump),
and partly because I can't for the love of me find some
good example code of SDL 2 to be compiled for iOS, so there
we go, it's there, have fun.

### Credits

This repo is heavily inspired from [this 2011 tutorial by Amin Ronacher](http://immersedcode.org/2011/4/25/sdl-on-ios/), albeit my code works with more recent
versions of SDL and the iOS SDK - and it's pure C, not C++ :)

