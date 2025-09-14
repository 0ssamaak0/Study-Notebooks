import matplotlib.pyplot as plt
import numpy as np

# Load the image
image = plt.imread("cat.jpg").mean(axis=2)
image_size_in_bytes = image.nbytes

U, S, V = np.linalg.svd(image)

print("=== SVD COMPRESSION THRESHOLD CALCULATION ===")
print(f"Original image shape: {image.shape}")
print(f"Original image size: {image_size_in_bytes} bytes")

# Formula for the threshold
m, n = image.shape
print(f"\nImage dimensions: m = {m}, n = {n}")

# The threshold is when compressed size = original size
# Original size = m * n elements
# Compressed size = m*i + i + i*n = i*(m + n + 1) elements
# Set them equal: m*n = i*(m + n + 1)
# Solve for i: i = (m*n) / (m + n + 1)

threshold = (m * n) / (m + n + 1)
print(f"\n=== THRESHOLD CALCULATION ===")
print(f"Formula: i = (m × n) / (m + n + 1)")
print(f"Threshold i = ({m} × {n}) / ({m} + {n} + 1) = {threshold:.2f}")

# For your image: (333 × 500) / (333 + 500 + 1) = 166,500 / 834 ≈ 199.64
print(f"\nThis means:")
print(f"- If i < {threshold:.0f}: You get compression (ratio < 100%)")
print(f"- If i = {threshold:.0f}: You store exactly the same amount of data")
print(f"- If i > {threshold:.0f}: You store more data than the original")

# Verify with actual calculations
print(f"\n=== VERIFICATION ===")
for i in [int(threshold)-10, int(threshold), int(threshold)+10]:
    compressed_size = U[:, :i].nbytes + S[:i].nbytes + V[:i, :].nbytes
    compression_ratio = compressed_size / image_size_in_bytes * 100
    print(f"i = {i}: Compression ratio = {compression_ratio:.2f}%")

# Alternative formula (simpler approximation)
print(f"\n=== SIMPLER APPROXIMATION ===")
# For large matrices, the +1 becomes negligible
simple_threshold = (m * n) / (m + n)
print(f"Simplified formula: i = (m × n) / (m + n) = {simple_threshold:.2f}")
print(f"This is very close to the exact threshold!")

# General rule of thumb
print(f"\n=== GENERAL RULE ===")
print(f"For any m×n matrix, the compression threshold is approximately:")
print(f"i_threshold ≈ (m × n) / (m + n)")
print(f"This gives you the maximum number of singular values you can use")
print(f"before you start storing more data than the original matrix.") 