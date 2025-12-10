```bash
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer/
mkdir build-static && cd build-static
cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local
make 
sudo make install
```
