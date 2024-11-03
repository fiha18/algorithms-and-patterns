# Complete Guide to Building and Pushing Docker Images using Jenkins Pipeline

In this guide, we walk through an end-to-end DevOps workflow that demonstrates how to:
1. **Build a Docker Image** from a simple Java application.
2. **Push the Docker Image to Docker Hub** for public access.
3. **Set up and Configure Jenkins Pipeline** to automate the process.
4. **Integrate DockerHub** and Jenkins for seamless deployment.

## Prerequisites
- Basic knowledge of **Docker** and **Jenkins**.
- Docker Desktop and Jenkins installed.
- A **GitHub** account and repository for storing code.
- A **DockerHub** account for pushing images.

---

## 1. Build Docker Image
The goal here is to containerize the Java application by creating a Docker image.

### Step-by-Step Process:
1. **Create Dockerfile** in your project’s root:
    ```dockerfile
    FROM openjdk:11-jre
    COPY target/devoops_integration.jar app.jar
    ENTRYPOINT ["java", "-jar", "/app.jar"]
    ```
    - `FROM openjdk:11-jre`: Sets the base image.
    - `COPY target/devoops_integration.jar app.jar`: Copies the jar file from the target directory.
    - `ENTRYPOINT ["java", "-jar", "/app.jar"]`: Runs the application on container startup.

2. **Build the Docker Image** using Jenkins Pipeline:
    - Define a stage in the Jenkins file for Docker image creation:
      ```groovy
      stage('Build Docker Image') {
          steps {
              script {
                  docker.build("javatechy/devoops_integration")
              }
          }
      }
      ```
    - Jenkins will read this stage and run the commands to build the Docker image.

## 2. Push Docker Image to DockerHub
Once the Docker image is built, the next step is to push it to DockerHub.

### Steps to Push the Image:
1. **Login to DockerHub** via Jenkins:
    - Use Jenkins credentials manager to securely store DockerHub credentials.
    - Define a stage to log in:
      ```groovy
      withCredentials([usernamePassword(credentialsId: 'dockerhub', passwordVariable: 'DOCKER_PASS', usernameVariable: 'DOCKER_USER')]) {
          sh "docker login -u $DOCKER_USER -p $DOCKER_PASS"
      }
      ```

2. **Push the Docker Image**:
    - Define a stage to push the image:
      ```groovy
      stage('Push to DockerHub') {
          steps {
              sh 'docker push javatechy/devoops_integration'
          }
      }
      ```

## 3. DockerHub Explanation
DockerHub serves as a repository for Docker images. Key points:
- **Public Repository**: Allows users to pull images without authentication.
- **Access Control**: Private repositories are accessible only by selected users.
- **Version Control**: Docker images are tagged, allowing version control.

## 4. Jenkins Pipeline Setup and Configurations
Jenkins Pipeline automates the CI/CD workflow from build to deployment.

### Steps to Set Up Pipeline:
1. **Configure Jenkins**:
    - Install necessary plugins (Git, Docker Pipeline).
    - Set up Docker in Jenkins' Global Tool Configuration.

2. **Create Jenkins Pipeline**:
    - In Jenkins, go to **New Item** > **Pipeline**.
    - Name it and select **Pipeline** as the project type.

3. **Add the Jenkinsfile**:
    - Add stages to the Jenkinsfile with all steps (build, push) defined above.
    - Save and trigger a build to test the complete process.

This setup achieves a complete automated DevOps integration using Docker and Jenkins.
