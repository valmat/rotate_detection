# Angle rotation detection on scanned documents

Detects the rotation of scanned documents.

Uses libleptonica

Designed for embedding in systems using tesseract OCR

[See usage examples](examples)

---

The detection algorithm based on [Rényi entropy](https://en.wikipedia.org/wiki/R%C3%A9nyi_entropy)


The proposed algorithm works quite well. However, it can be improved.

---

Original image            |  Rotated automatically
:------------------------:|:-------------------------:
![](demo/small/1-in.jpg)  | ![](demo/small/1-out.jpg)
![](demo/small/2-in.jpg)  | ![](demo/small/2-out.jpg)
![](demo/small/3-in.jpg)  | ![](demo/small/3-out.jpg)
![](demo/small/4-in.jpg)  | ![](demo/small/4-out.jpg)
![](demo/small/5-in.jpg)  | ![](demo/small/5-out.jpg)

---
[The MIT License](LICENSE)
