pipeline {
    agent any

    triggers {
        githubPush()
    }

    stages {
        stage('Checkout Code') {
            steps {
                checkout scm
            }
        }
        
        
        stage('Test') {
            steps {
                sh 'echo "Running Tests"'
            }
        }
        
        
        stage('run docker') {
            steps {
                sh 'sudo docker-compose up -d'
            }
        }
        
        stage('Run Postman Tests') {
            steps {
                sh 'sudo /usr/bin/python3 /home/yisrael/git_hub/REST_api_with_crud_operation_and_sql/test.py'
            }
        }
    }
}


