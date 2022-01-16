Don't forget install libleptonica

```bash
sudo apt update
sudo apt install libleptonica-dev
```

Why leptonica? Because tesseract uses it.

## API

```c++
int get_pix_rotation(const Pix *pix, const GetPixRotOts& opts = {}) noexcept;
```
Returns the angle in degrees


```c++
std::pair<int, int> get_pix_rotation_wh(const Pix *pix, int angle) noexcept;
```
Returns pair `[width, height]` to set in call of leptonica function `pixRotate`


You can specify how to search the angle with `PixRotOts`
```c++
struct PixRotOts
{
    float contrast_factor = 1.0;
    int   threshold       = 170;   // Threshold for creating black-white representation
    int   angle_first     = -45;   // Starts searching angle from angle_first
    int   angle_last      = 45;    // Completes search the angle on angle_last
    int   angle_step      = 1;     // Step withs searching angle
    bool  fast            = false; // true -- fast, false -- slow, but more accurate (scans vertical lines)
    uint  threads         = 0;     // 0 -- Use all (Multithreading)
};
```
