import matplotlib.pyplot as plt
import numpy as np

# Load the image
image = plt.imread("cat.jpg").mean(axis=2)
image_size_in_bytes = image.nbytes

U, S, V = np.linalg.svd(image)

print("=== SVD COMPRESSION ANALYSIS ===")
print(f"Original image shape: {image.shape}")
print(f"Original image size: {image_size_in_bytes} bytes")

# The problem with your original calculation:
print(f"\n=== YOUR ORIGINAL CALCULATION (i=200) ===")
i = 200
compressed_size = U[:, :i].nbytes + S[:i].nbytes + V[:i, :].nbytes
compression_ratio = compressed_size / image_size_in_bytes * 100
print(f"Compressed size: {compressed_size} bytes")
print(f"Compression ratio: {compression_ratio:.2f}%")
print(f"Problem: You're storing MORE data than the original!")

# Correct approach - use fewer singular values
print(f"\n=== CORRECTED CALCULATION ===")
m, n = image.shape
max_singular_values = min(m, n)
print(f"Maximum singular values for compression: {max_singular_values}")

# Try different values of i
for i in [10, 50, 100, 150]:
    if i <= max_singular_values:
        compressed_size = U[:, :i].nbytes + S[:i].nbytes + V[:i, :].nbytes
        compression_ratio = compressed_size / image_size_in_bytes * 100
        print(f"\ni = {i}:")
        print(f"  Compressed size: {compressed_size} bytes")
        print(f"  Compression ratio: {compression_ratio:.2f}%")
        print(f"  Storage: U({U.shape[0]}×{i}) + S({i}) + V({i}×{V.shape[1]}) = {U.shape[0]*i + i + i*V.shape[1]} elements")

print(f"\n=== SUMMARY ===")
print("The issue was that you used i=200 singular values, but your image")
print("has dimensions 333×500, so min(333,500) = 333 is the maximum")
print("number of singular values you can use before you start storing")
print("more data than the original image.") 