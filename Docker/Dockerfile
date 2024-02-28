# Use an official Python runtime as a parent image
FROM python:3.12.2-alpine3.18

# Set the working directory in the container to /app
WORKDIR /app

# Copy the current directory contents into the container working directory (originally COPY . /app when we didn't use WORKDIR /app)
COPY . .

# # Install any needed packages specified in requirements.txt
RUN pip install -r requirements.txt

# # run the python command to execute the docker_test.py file
# CMD ["python", "docker_test.py"]

# # RUN VS CMD
# # RUN is used to execute a command during the build process of the Docker image.
# # CMD is used to provide defaults for an executing container. These defaults can include an executable, or they can omit the executable, in which case the entrypoint instruction must be specified as well.

# to instantiate:
docker run -dit <image_name>