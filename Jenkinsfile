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
        
        stage('Install Dependencies') {
            steps {
            	
            	sh 'apt install nodejs npm'
            
                sh 'npm install -g newman'
            }
        }
        
        stage('Test') {
            steps {
                sh 'echo "Running Tests"'
            }
        }
        
        stage('Run Postman Tests') {
            steps {
                sh '/home/yisrael/git_hub/REST_api_with_crud_operation_and_sql/postman_collection.json'
            }
        }
    }
}


