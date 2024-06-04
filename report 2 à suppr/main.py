"""

©Copyright Code :
Evahn LE GAL, ISIMA Clermont INP
Chloé BRICE, INSA Lyon

Code co-written with Evahn LE GAL, with the agreement of the professor, the report and the images will nevertheless be different for each student
Only the code was written and used as a team

Python 3.11.6

"""

import math
from PIL import Image
from matplotlib import pyplot as plt
import numpy as np

# Light sources
S_list = []

light_sources = [
    "0.403259 0.480808 0.778592",
    "0.0982272 0.163712 0.981606",
    "-0.0654826 0.180077 0.98147",
    "-0.127999 0.431998 0.892745",
    "-0.328606 0.485085 0.810377",
    "-0.110339 0.53593 0.837021",
    "0.239071 0.41439 0.878138",
    "0.0642302 0.417497 0.906406",
    "0.12931 0.339438 0.931698",
    "0.0323953 0.340151 0.939813",
    "0.0985318 0.0492659 0.993914",
    "-0.16119 0.354617 0.921013",
]

S_list.append([-0.0654826, 0.180077, 0.98147])
S_list.append([-0.328606, 0.485085, 0.810377])
S_list.append([0.0323953, 0.340151, 0.939813])

print("S_list:", S_list)


# Load Images
img_files = [
    "./img/photometric/cat.2.png",
    "./img/photometric/cat.4.png",
    "./img/photometric/cat.9.png",
]

imgs = [Image.open(img_file).convert("RGB") for img_file in img_files]

# Load mask
mask = Image.open("./img/photometric/cat.mask.png").convert("L")

# Check if images are loaded
for img in imgs:
    if img is None:
        print("Image loading has failed")
        exit()

if mask is None:
    print("Mask loading has failed")
    exit()

# Convert to gray scale and apply mask
gray_imgs = []
for img in imgs:
    gray_img = img.convert("L")
    masked = Image.fromarray(np.bitwise_and(np.array(gray_img), np.array(mask)))
    gray_imgs.append(masked)

# Print intensity values at a specific point for verification
for i, gray_img in enumerate(gray_imgs):
    print(
        f"Intensity value at (250, 100) in gray Image {i + 1}: {gray_img.getpixel((250, 100))}"
    )

# Use the light sources coordinates
S = np.array(S_list)
S_t = S.T

# Transform the gray images list into an array for the computation
gray_imgs = np.array(gray_imgs)

h, w = gray_imgs[0].shape[:2]

# Matrix of all the normal coordinates at each pixel
img_normal = np.zeros((h, w, 3))

# Value of luminance at each pixel of the grey images
I = np.zeros((len(S_list), 3))

# For each pixel
for x in range(w):
    for y in range(h):

        # And each of the 3 images
        for i in range(len(gray_imgs)):
            I[i] = gray_imgs[i][y][x]

        # Use the formula to compute N
        S_inv = np.linalg.inv(S_t)
        N = np.dot(S_inv, I).T
        N_norm = np.linalg.norm(N, axis=1)

        rho = N_norm * math.pi

        # Define a luminosity to display normals
        N_gray = N[0] * 0.30 + N[1] * 0.35 + N[2] * 0.35
        N_gray_norm = np.linalg.norm(N_gray)
        if N_gray_norm == 0:
            continue

        # Store the normals' values of the image
        img_normal[y][x] = N_gray / N_gray_norm

# Convert to rgb for colored representation
img_normal_rgb = ((img_normal * 0.5 + 0.5) * 255).astype(np.uint8)

# Display
plt.figure(figsize=(30,8))
plt.subplot(1, 2, 1)
plt.imshow(imgs[0])
plt.title("Example image with a specific light source")
plt.subplot(1, 2, 2)
plt.imshow(img_normal_rgb)
plt.title("Surface Normals of the object")
plt.show()
