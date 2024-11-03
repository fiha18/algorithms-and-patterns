DevOps End-to-End Integration Tutorial Summary
In this tutorial, we walk through the process of building, pushing, and deploying a Docker image to a Kubernetes cluster using a Jenkins Pipeline. Below are the main steps covered:

Overview
The tutorial covers:

Building a Docker image with Jenkins.
Pushing the image to Docker Hub.
Deploying the image to a Kubernetes cluster.
The session assumes knowledge of Docker, Jenkins, and Kubernetes basics.

Step-by-Step Guide
Prerequisites
Docker Desktop: Start Docker on your machine.
Jenkins: Start Jenkins using the command brew services start jenkins on Mac.
Access Jenkins Dashboard: Open localhost:8080, and log in.
Setting Up Jenkins for Kubernetes Deployment
MiniKube: Start Kubernetes with minikube start.
Jenkins Plugin: Install the Kubernetes Continuous Deploy plugin in Jenkins.
Note: Downgrade the plugin if issues arise with the latest version.
Configuring Kubernetes in Jenkins Pipeline
Define Deployment and Service Files: Create a deployment-service.yaml file to specify Kubernetes deployment and service details.
Sync Docker with Kubernetes:
Bash
eval $(minikube docker-env)
Use code with caution.

Jenkins Configuration: Add kubeconfig credentials in Jenkins under Manage Jenkins > Manage Credentials.
Configure the Jenkins pipeline to include the new deployment stage with the Kubernetes config.
Jenkins Pipeline Stages
Build and Push Docker Image:
Jenkins builds a Maven project and creates a Docker image.
The image is pushed to Docker Hub.
Deploy to Kubernetes:
Jenkins deploys the image to Kubernetes using the configuration in deployment-service.yaml.
Verifying the Deployment
Check Kubernetes Nodes:
Bash
kubectl get nodes
Use code with caution.

Verify Deployment Status:
Bash
kubectl get deployments
kubectl get pods
Use code with caution.

Access Application: Use minikube service <service-name> --url to get the application URL.
Additional Commands
Start Jenkins: brew services start jenkins
Check Docker Images: docker images
Get Pod Logs: kubectl logs <pod-name>
Get Services: kubectl get services
Conclusion
This tutorial provides a complete end-to-end CI/CD pipeline using Jenkins, Docker, and Kubernetes. The setup demonstrates best practices for deploying applications to Kubernetes clusters using automated Jenkins pipelines.