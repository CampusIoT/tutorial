# Wio Terminal :: Display photos from a SDCard

This example is a crossover of [Display Images](https://wiki.seeedstudio.com/Wio-Terminal-Displaying-Photos/) and `Examples > Seedstudio Arduino FS > listfiles` example




## Convert JPEG images in BMP

You can convert your JPEG photos with [imagemagick CLI](https://imagemagick.org/script/convert.php)

Install imagemagick on MacOS
```bash
brew install imagemagick
```

Run the convertion
```bash
for im in *.jpg; do
bas=$(basename -s .jpg $im)
echo Converting $im ... 
magick $bas.jpg -resize 320x240 $bas.bmp
done
```

Copy the BMP files on the SDCard

Insert the SDCard into the Wio Terminal

## Build and load the sketch `PhotosAlbum.ino`

> You can configure the constantes

```c
...
#define ROOTDIR "/photos"
#define DELAY   2000
...
```