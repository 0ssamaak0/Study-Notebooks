def love_docker():
    print("I love Docker!")


love_docker()
done = "FALSE"

try:
    import numpy as np

    print("Numpy is installed")
    done = "TRUE"
except ImportError:
    print("Numpy is not installed")


with open("output.txt", "w") as f:
    f.write(done)
