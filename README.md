Chess Game with C and SDL2

it's setup with cmake and so it should just work, you might have to copie the dlls in vendor/SDL2/bin folder to the executable's folder.
compilation : (need to have cmake installed)
execute the following command in the project's root directory:
1- mkdir build
2- cd build
3- cmake ..
4- make
5- ./Chess
if you get missing dll error it means cmake for some reason couldn't copy the dlls and you have to do it manually
