import numpy as np
import matplotlib.pyplot as plt

def read_ppm(filename):
    with open(filename, 'r') as file:
        # Read the header
        header = file.readline().strip()
        if header != 'P3':
            raise ValueError(f"Unsupported PPM format: {header}")

        # Skip comments
        while True:
            line = file.readline().strip()
            if not line.startswith('#'):
                break

        # Image dimensions
        width, height = map(int, line.split())

        # Maximum color value
        max_color = int(file.readline().strip())

        # Read pixel data
        pixel_values = []
        for line in file:
            pixel_values.extend(map(int, line.split()))

        # Reshape pixel data into a numpy array
        image = np.array(pixel_values, dtype=np.uint8).reshape((height, width, 3))
        return image

image = read_ppm("output.ppm")
plt.imshow(image)
plt.axis('off')
plt.title("PPM Image")
plt.show()
